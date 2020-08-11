/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/


#include<cmath>
#include<QMouseEvent>
#include "rs_snapper.h"

#include "rs_graphicview.h"
#include "rs_grid.h"
#include "rs_settings.h"
#include "rs_coordinateevent.h"
#include "rs_entitycontainer.h"
#include "rs_pen.h"
#include "rs_debug.h"

/**
  * Disable all snapping.
  *
  * This effectively puts the object into free snap mode.
  *
  * @returns A reference to itself.
  */
RS_SnapMode const & RS_SnapMode::clear()
{
    snapIntersection    = false;
    snapOnEntity        = false;
    snapCenter          = false;
    snapDistance        = false;
    snapMiddle          = false;
    snapEndpoint        = false;
    snapGrid            = false;
    snapFree            = false;
    snapAngle           = false;

    restriction = RS2::RestrictNothing;

    return *this;
}

bool RS_SnapMode::operator ==(RS_SnapMode const& rhs) const
{
    return snapIntersection == rhs.snapIntersection
            && snapOnEntity == rhs.snapOnEntity
            && snapCenter   == rhs.snapCenter
            && snapDistance == rhs.snapDistance
            && snapMiddle   == rhs.snapMiddle
            && snapEndpoint == rhs.snapEndpoint
            && snapGrid     == rhs.snapGrid
            && snapFree     == rhs.snapFree
            && restriction  == rhs.restriction
            && snapAngle    == rhs.snapAngle;
}


/**
  * snap mode to a flag integer
  */
uint RS_SnapMode::toInt(const RS_SnapMode& s)
{
    uint ret {0};

    if (s.snapIntersection) ret |= RS_SnapMode::SnapIntersection;
    if (s.snapOnEntity)     ret |= RS_SnapMode::SnapOnEntity;
    if (s.snapCenter)       ret |= RS_SnapMode::SnapCenter;
    if (s.snapDistance)     ret |= RS_SnapMode::SnapDistance;
    if (s.snapMiddle)       ret |= RS_SnapMode::SnapMiddle;
    if (s.snapEndpoint)     ret |= RS_SnapMode::SnapEndpoint;
    if (s.snapGrid)         ret |= RS_SnapMode::SnapGrid;
    if (s.snapFree)         ret |= RS_SnapMode::SnapFree;
    if (s.snapAngle)        ret |= RS_SnapMode::SnapAngle;

    switch (s.restriction) {
    case RS2::RestrictHorizontal:
        ret |= RS_SnapMode::RestrictHorizontal;
        break;
    case RS2::RestrictVertical:
        ret |= RS_SnapMode::RestrictVertical;
        break;
    case RS2::RestrictOrthogonal:
        ret |= RS_SnapMode::RestrictOrthogonal;
        break;
    default:
        break;
    }

    return ret;
}

/**
  * integer flag to snapMode
  */
RS_SnapMode RS_SnapMode::fromInt(unsigned int ret)
{
    RS_SnapMode s;

    if (RS_SnapMode::SnapIntersection   & ret) s.snapIntersection = true;
    if (RS_SnapMode::SnapOnEntity       & ret) s.snapOnEntity = true;
    if (RS_SnapMode::SnapCenter         & ret) s.snapCenter = true;
    if (RS_SnapMode::SnapDistance       & ret) s.snapDistance = true;
    if (RS_SnapMode::SnapMiddle         & ret) s.snapMiddle = true;
    if (RS_SnapMode::SnapEndpoint       & ret) s.snapEndpoint = true;
    if (RS_SnapMode::SnapGrid           & ret) s.snapGrid = true;
    if (RS_SnapMode::SnapFree           & ret) s.snapFree = true;
    if (RS_SnapMode::SnapAngle          & ret) s.snapAngle = true;

    switch (RS_SnapMode::RestrictOrthogonal & ret) {
    case RS_SnapMode::RestrictHorizontal:
        s.restriction = RS2::RestrictHorizontal;
        break;
    case RS_SnapMode::RestrictVertical:
        s.restriction = RS2::RestrictVertical;
        break;
    case RS_SnapMode::RestrictOrthogonal:
        s.restriction = RS2::RestrictOrthogonal;
        break;
    default:
        s.restriction = RS2::RestrictNothing;
        break;
    }

    return s;
}

/**
  * Methods and structs for class RS_Snapper
  */
struct RS_Snapper::Indicator
{
    bool lines_state;
    QString lines_type;
    RS_Pen lines_pen;

    bool shape_state;
    QString shape_type;
    RS_Pen shape_pen;
};

struct RS_Snapper::ImpData {
RS_Vector snapCoord;
RS_Vector snapSpot;
};

/**
 * Constructor.
 */
RS_Snapper::RS_Snapper(RS_EntityContainer& container, RS_GraphicView& graphicView)
    :container(&container)
    ,graphicView(&graphicView)
	,pImpData(new ImpData{})
    ,snap_indicator(new Indicator{})
{}

RS_Snapper::~RS_Snapper()
{
    delete snap_indicator;
}

/**
 * Initialize (called by all constructors)
 */
void RS_Snapper::init() 
{
    snapMode = graphicView->getDefaultSnapMode();
	keyEntity = nullptr;
	pImpData->snapSpot = RS_Vector{false};
	pImpData->snapCoord = RS_Vector{false};
	m_SnapDistance = 1.0;

    RS_SETTINGS->beginGroup("/Appearance");
    snap_indicator->lines_state = RS_SETTINGS->readNumEntry("/indicator_lines_state", 1);
    snap_indicator->lines_type = RS_SETTINGS->readEntry("/indicator_lines_type", "Crosshair");
    snap_indicator->shape_state = RS_SETTINGS->readNumEntry("/indicator_shape_state", 1);
    snap_indicator->shape_type = RS_SETTINGS->readEntry("/indicator_shape_type", "Circle");
    RS_SETTINGS->endGroup();

    RS_SETTINGS->beginGroup("Colors");
    QString snap_color = RS_SETTINGS->readEntry("/snap_indicator", Colors::snap_indicator);
    RS_SETTINGS->endGroup();

	snap_indicator->lines_pen = RS_Pen(RS_Color(snap_color), RS2::Width00, RS2::DashLine2);
	snap_indicator->shape_pen = RS_Pen(RS_Color(snap_color), RS2::Width00, RS2::SolidLine);
	snap_indicator->shape_pen.setScreenWidth(1);

    snapRange=getSnapRange();
}


void RS_Snapper::finish() {
    finished = true;
    deleteSnapper();
}

void RS_Snapper::setSnapMode(const RS_SnapMode& snapMode) {
  this->snapMode = snapMode;
  //RS_DIALOGFACTORY->requestSnapDistOptions(m_SnapDistance, snapMode.snapDistance);
  //RS_DIALOGFACTORY->requestSnapMiddleOptions(middlePoints, snapMode.snapMiddle);
}

RS_SnapMode const* RS_Snapper::getSnapMode() const{
	return &(this->snapMode);
}

RS_SnapMode* RS_Snapper::getSnapMode() {
	return &(this->snapMode);
}

//get current mouse coordinates
RS_Vector RS_Snapper::snapFree(QMouseEvent* e) {
	if (!e) {
                RS_DEBUG->print(RS_Debug::D_WARNING,
						"RS_Snapper::snapFree: event is nullptr");
        return RS_Vector(false);
    }
	pImpData->snapSpot=graphicView->toGraph(e->x(), e->y());
	pImpData->snapCoord=pImpData->snapSpot;
    snap_indicator->lines_state=true;
	return pImpData->snapCoord;
}


double RS_Snapper::getSnapRange() const
{
    if (graphicView) {
        return (graphicView->getGrid()->getCellVector() * 0.5).magnitude();
    }

    return 20.;
}

/**
 * Snaps to a free coordinate.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapFree(const RS_Vector& coord) {
	keyEntity = nullptr;
    return coord;
}

/**
 * Snaps to a grid point.
 *
 * @param coord The mouse coordinate.
 * @return The coordinates of the point or an invalid vector.
 */
RS_Vector RS_Snapper::snapGrid(const RS_Vector& coord) {

//    RS_DEBUG->print("RS_Snapper::snapGrid begin");

//    std::cout<<__FILE__<<" : "<<__func__<<" : line "<<__LINE__<<std::endl;
//    std::cout<<" mouse: = "<<coord<<std::endl;
//    std::cout<<" snapGrid: = "<<graphicView->getGrid()->snapGrid(coord)<<std::endl;
    return  graphicView->getGrid()->snapGrid(coord);
}


/**
 * 'Corrects' the given coordinates to 0, 90, 180, 270 degrees relative to
 * the current relative zero point.
 *
 * @param coord The uncorrected coordinates.
 * @return The corrected coordinates.
 */
RS_Vector RS_Snapper::restrictOrthogonal(const RS_Vector& coord) {
    RS_Vector rz = graphicView->getRelativeZero();
    RS_Vector ret(coord);

    RS_Vector retx = RS_Vector(rz.x, ret.y);
    RS_Vector rety = RS_Vector(ret.x, rz.y);

    if (retx.distanceTo(ret) > rety.distanceTo(ret)) {
        ret = rety;
    } else {
        ret = retx;
    }

    return ret;
}

/**
 * 'Corrects' the given coordinates to 0, 180 degrees relative to
 * the current relative zero point.
 *
 * @param coord The uncorrected coordinates.
 * @return The corrected coordinates.
 */
RS_Vector RS_Snapper::restrictHorizontal(const RS_Vector& coord) {
    RS_Vector rz = graphicView->getRelativeZero();
    RS_Vector ret = RS_Vector(coord.x, rz.y);
    return ret;
}


/**
 * 'Corrects' the given coordinates to 90, 270 degrees relative to
 * the current relative zero point.
 *
 * @param coord The uncorrected coordinates.
 * @return The corrected coordinates.
 */
RS_Vector RS_Snapper::restrictVertical(const RS_Vector& coord) {
    RS_Vector rz = graphicView->getRelativeZero();
    RS_Vector ret = RS_Vector(rz.x, coord.y);
    return ret;
}

void RS_Snapper::suspend() {
			// RVT Don't delete the snapper here!
	// RVT_PORT (can be deleted)();
	pImpData->snapSpot = pImpData->snapCoord = RS_Vector{false};
}

/**
 * Hides the snapper options. Default implementation does nothing.
 */
void RS_Snapper::hideOptions() {
    //not used any more, will be removed
}

/**
 * Shows the snapper options. Default implementation does nothing.
 */
void RS_Snapper::showOptions() {
    //not used any more, will be removed
}

/**
 * Deletes the snapper from the screen.
 */
void RS_Snapper::deleteSnapper()
{
    graphicView->getOverlayContainer(RS2::Snapper)->clear();
    graphicView->redraw(RS2::RedrawOverlay); // redraw will happen in the mouse movement event
}
