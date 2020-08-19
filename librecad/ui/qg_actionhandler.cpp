#include "qg_actionhandler.h"
#include <math.h>
#include "rs_graphicview.h"
#include "rs_document.h"
#include "rs_debug.h"
#include "rs_actionzoomin.h"
#include "rs_actionzoompan.h"
#include "rs_actionzoomauto.h"
#include "rs_actionzoomprevious.h"
#include "rs_actionzoomwindow.h"
#include "rs_actionzoomredraw.h"
#include "rs_actiondrawline.h"
#include "rs_actiondrawpoint.h"
#include "rs_actiondrawlineangle.h"
#include "rs_actiondrawlinehorvert.h"
#include "rs_actiondrawlinefree.h"
#include "rs_actiondrawlineparallel.h"
#include "rs_actiondrawlineangle.h"
#include "rs_actiondrawlinefree.h"
#include "rs_actiondrawlineparallelthrough.h"
#include "rs_actiondrawlinerectangle.h"

#include "rs_actionselect.h"
#include "rs_actionselectall.h"
#include "rs_actioneditcopy.h"
#include "rs_actioneditpaste.h"
#include "rs_actioneditundo.h"

QG_ActionHandler::QG_ActionHandler(QObject *parent) : QObject(parent)
{

}

void QG_ActionHandler::setView(RS_GraphicView *graphicView) {
  view_ = graphicView;
}

void QG_ActionHandler::setDocument(RS_Document *document) {
  document_ = document;
}

void QG_ActionHandler::killSelectActions() {
  if (view_) {
    view_->killSelectActions();
  }
}

void QG_ActionHandler::killAllActions() {
  if (view_) {
    view_->killAllActions();
  }
}

RS_ActionInterface* QG_ActionHandler::getCurrentAction() {
  if (view_) {
    return view_->getCurrentAction();
  } else {
    return NULL;
  }
}

RS_ActionInterface* QG_ActionHandler::setCurrentAction(RS2::ActionType id) {
    RS_DEBUG->print("QG_ActionHandler::setCurrentAction()");
    RS_ActionInterface* a = NULL;
//    view_->killAllActions();

    RS_DEBUG->print("QC_ActionHandler::setCurrentAction: "
            "view = %p, document = %p", view_, document_);

    // only global options are allowed without a document_:
    if (view_ == NULL || document_ == NULL) {
        RS_DEBUG->print(RS_Debug::D_WARNING,
                "QG_ActionHandler::setCurrentAction: graphic view or "
                "document is NULL");
        return NULL;
    }

    auto a_layer = document_->getLayerList()->getActive();

    switch (id) {
        //case RS2::ActionFileNew:
        //    a = new RS_ActionFileNew(*document_, *view_);
        //	break;
    case RS2::ActionFileNewTemplate:
        //a = new RS_ActionFileNewTemplate(*document_, *view_);
        break;
        //case RS2::ActionFileSave:
        //    a = new RS_ActionFileSave(*document_, *view_);
        //	break;
        //case RS2::ActionFileClose:
        //    //a = new RS_ActionFileClose(*document_, *view_);
        //	break;
        //case RS2::ActionFileQuit:
        //    //a = new RS_ActionFileQuit(*document_, *view_);
        //	break;
    case RS2::ActionFileOpen:
        //a = new RS_ActionFileOpen(*document_, *view_);
        break;
    case RS2::ActionFileSaveAs:
        //a = new RS_ActionFileSaveAs(*document_, *view_);
        break;
    case RS2::ActionFileExportMakerCam:
        //a = new LC_ActionFileExportMakerCam(*document_, *view_);
        break;

        // Editing actions:
        //
    case RS2::ActionEditKillAllActions:
        //if (view_) {
            // DO we need to call some form of a 'clean' function?
        //    view_->killAllActions();

        //    RS_Selection s((RS_EntityContainer&)*document_, view_);
        //    s.selectAll(false);
        //    RS_DIALOGFACTORY->updateSelectionWidget(document_->countSelected(),document_->totalSelectedLength());
        //}
        break;
    case RS2::ActionEditUndo:
        a = new RS_ActionEditUndo(true, *document_, *view_);
        break;
    case RS2::ActionEditRedo:
        a = new RS_ActionEditUndo(false, *document_, *view_);
        break;
    case RS2::ActionEditCut:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionEditCutNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionEditCutNoSelect:
        a = new RS_ActionEditCopy(false, *document_, *view_);
        break;
    case RS2::ActionEditCopy:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionEditCopyNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionEditCopyNoSelect:
        a = new RS_ActionEditCopy(true, *document_, *view_);
        break;
    case RS2::ActionEditPaste:
        a = new RS_ActionEditPaste(*document_, *view_);
        break;
    case RS2::ActionOrderBottom:
        /*orderType = RS2::ActionOrderBottom;
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionOrderNoSelect);
        }
        else {
            a = new RS_ActionOrder(*document_, *view_, orderType);
        }*/
        break;
    case RS2::ActionOrderLower:
        //orderType = RS2::ActionOrderLower;
        //a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionOrderNoSelect);
        break;
    case RS2::ActionOrderRaise:
        //orderType = RS2::ActionOrderRaise;
        //a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionOrderNoSelect);
        break;
    case RS2::ActionOrderTop:
        /*orderType = RS2::ActionOrderTop;
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionOrderNoSelect);
        }
        else {
            a = new RS_ActionOrder(*document_, *view_, orderType);
        }*/
        break;
    case RS2::ActionOrderNoSelect:
        //a = new RS_ActionOrder(*document_, *view_, orderType);
        break;

        // Selecting actions:
        //
    case RS2::ActionSelectSingle:
//        view_->killSelectActions();
        /*if(getCurrentAction()->rtti() != RS2::ActionSelectSingle) {
            a = new RS_ActionSelectSingle(*document_, *view_,getCurrentAction());
        }else{
            a=NULL;
        }*/
        break;
    case RS2::ActionSelectContour:
        //view_->killSelectActions();
        //a = new RS_ActionSelectContour(*document_, *view_);
        break;
    case RS2::ActionSelectAll:
        //a = new RS_ActionSelectAll(*document_, *view_, true);
        break;
    case RS2::ActionDeselectAll:
        //a = new RS_ActionSelectAll(*document_, *view_, false);
        break;
    case RS2::ActionSelectWindow:
        //view_->killSelectActions();
        //a = new RS_ActionSelectWindow(*document_, *view_, true);
        break;
    case RS2::ActionDeselectWindow:
        //view_->killSelectActions();
        //a = new RS_ActionSelectWindow(*document_, *view_, false);
        break;
    case RS2::ActionSelectInvert:
        //a = new RS_ActionSelectInvert(*document_, *view_);
        break;
    case RS2::ActionSelectIntersected:
        //view_->killSelectActions();
        //a = new RS_ActionSelectIntersected(*document_, *view_, true);
        break;
    case RS2::ActionDeselectIntersected:
        //view_->killSelectActions();
        //a = new RS_ActionSelectIntersected(*document_, *view_, false);
        break;
    case RS2::ActionSelectLayer:
        //view_->killSelectActions();
        //a = new RS_ActionSelectLayer(*document_, *view_);
        break;

        // Tool actions:
        //
    case RS2::ActionToolRegenerateDimensions:
        //a = new RS_ActionToolRegenerateDimensions(*document_, *view_);
        break;

        // Zooming actions:
        //
    case RS2::ActionZoomIn:
        a = new RS_ActionZoomIn(*document_, *view_, RS2::In, RS2::Both);
        break;
    case RS2::ActionZoomOut:
        a = new RS_ActionZoomIn(*document_, *view_, RS2::Out, RS2::Both);
        break;
    case RS2::ActionZoomAuto:
        a = new RS_ActionZoomAuto(*document_, *view_);
        break;
    case RS2::ActionZoomWindow:
        a = new RS_ActionZoomWindow(*document_, *view_);
        break;
    case RS2::ActionZoomPan:
        a = new RS_ActionZoomPan(*document_, *view_);
        break;
    case RS2::ActionZoomPrevious:
        a = new RS_ActionZoomPrevious(*document_, *view_);
        break;
    case RS2::ActionZoomRedraw:
        a = new RS_ActionZoomRedraw(*document_, *view_);
        break;

        // Drawing actions:
        //
    case RS2::ActionDrawPoint:
        a = new RS_ActionDrawPoint(*document_, *view_);
        break;
    case RS2::ActionDrawLine:
        a = new RS_ActionDrawLine(*document_, *view_);
        break;
    case RS2::ActionDrawLineAngle:
        a = new RS_ActionDrawLineAngle(*document_, *view_, 0.0, false);
        break;
    case RS2::ActionDrawLineHorizontal:
        a = new RS_ActionDrawLineAngle(*document_, *view_, 0.0, true,
                                       RS2::ActionDrawLineHorizontal);
        break;
    case RS2::ActionDrawLineHorVert:
        a = new RS_ActionDrawLineHorVert(*document_, *view_);
        break;
    case RS2::ActionDrawLineVertical:
        a = new RS_ActionDrawLineAngle(*document_, *view_, M_PI_2, true,
                                       RS2::ActionDrawLineVertical);
        break;
    case RS2::ActionDrawLineFree:
        a = new RS_ActionDrawLineFree(*document_, *view_);
        break;
    case RS2::ActionDrawLineParallel:
        a= new RS_ActionDrawLineParallel(*document_, *view_);
        a->setActionType(id);
        break;
    case RS2::ActionDrawLineParallelThrough:
        a = new RS_ActionDrawLineParallelThrough(*document_, *view_);
        break;
    case RS2::ActionDrawLineRectangle:
        a = new RS_ActionDrawLineRectangle(*document_, *view_);
        break;
    /*case RS2::ActionDrawLineBisector:
        a = new RS_ActionDrawLineBisector(*document_, *view_);
        break;
    case RS2::ActionDrawLineOrthTan:
        a = new RS_ActionDrawLineOrthTan(*document_, *view_);
        break;
    case RS2::ActionDrawLineTangent1:
        a = new RS_ActionDrawLineTangent1(*document_, *view_);
        break;
    case RS2::ActionDrawLineTangent2:
        a = new RS_ActionDrawLineTangent2(*document_, *view_);
        break;
    case RS2::ActionDrawLineOrthogonal:
        a = new RS_ActionDrawLineRelAngle(*document_, *view_, M_PI_2, true);
        break;
    case RS2::ActionDrawLineRelAngle:
        a = new RS_ActionDrawLineRelAngle(*document_, *view_, M_PI_2, false);
        break;
    case RS2::ActionDrawPolyline:
        a = new RS_ActionDrawPolyline(*document_, *view_);
        break;
    case RS2::ActionPolylineAdd:
        a = new RS_ActionPolylineAdd(*document_, *view_);
        break;
    case RS2::ActionPolylineAppend:
        a = new RS_ActionPolylineAppend(*document_, *view_);
        break;
    case RS2::ActionPolylineDel:
        a = new RS_ActionPolylineDel(*document_, *view_);
        break;
    case RS2::ActionPolylineDelBetween:
        a = new RS_ActionPolylineDelBetween(*document_, *view_);
        break;
    case RS2::ActionPolylineTrim:
        a = new RS_ActionPolylineTrim(*document_, *view_);
        break;
    case RS2::ActionPolylineEquidistant:
        a = new RS_ActionPolylineEquidistant(*document_, *view_);
        break;
    case RS2::ActionPolylineSegment:
        a = new RS_ActionPolylineSegment(*document_, *view_);
        break;
    case RS2::ActionDrawLinePolygonCenCor:
        a = new RS_ActionDrawLinePolygonCenCor(*document_, *view_);
        break;
    case RS2::ActionDrawLinePolygonCenTan:                      //20161223 added by txmy
        a = new LC_ActionDrawLinePolygonCenTan(*document_, *view_);
        break;
    case RS2::ActionDrawLinePolygonCorCor:
        a = new RS_ActionDrawLinePolygonCorCor(*document_, *view_);
        break;
    case RS2::ActionDrawCircle:
        a = new RS_ActionDrawCircle(*document_, *view_);
        break;
    case RS2::ActionDrawCircleCR:
        a = new RS_ActionDrawCircleCR(*document_, *view_);
        break;
    case RS2::ActionDrawCircle2P:
        a = new RS_ActionDrawCircle2P(*document_, *view_);
        break;
    case RS2::ActionDrawCircle2PR:
        a = new LC_ActionDrawCircle2PR(*document_, *view_);
        break;
    case RS2::ActionDrawCircle3P:
        a = new RS_ActionDrawCircle3P(*document_, *view_);
        break;
    case RS2::ActionDrawCircleTan1_2P:
        a = new RS_ActionDrawCircleTan1_2P(*document_, *view_);
        break;
    case RS2::ActionDrawCircleTan2_1P:
        a = new RS_ActionDrawCircleTan2_1P(*document_, *view_);
        break;
    case RS2::ActionDrawCircleParallel:
        a= new RS_ActionDrawLineParallel(*document_, *view_);
        a->setActionType(id);
        break;
    case RS2::ActionDrawCircleInscribe:
        a = new RS_ActionDrawCircleInscribe(*document_, *view_);
        break;
    case RS2::ActionDrawCircleTan2:
        a = new RS_ActionDrawCircleTan2(*document_, *view_);
        break;
    case RS2::ActionDrawCircleTan3:
        a = new RS_ActionDrawCircleTan3(*document_, *view_);
        break;
    case RS2::ActionDrawArc:
        a = new RS_ActionDrawArc(*document_, *view_);
        break;
    case RS2::ActionDrawArc3P:
        a = new RS_ActionDrawArc3P(*document_, *view_);
        break;
    case RS2::ActionDrawArcParallel:
        a= new RS_ActionDrawLineParallel(*document_, *view_);
        a->setActionType(id);
        break;
    case RS2::ActionDrawArcTangential:
        a = new RS_ActionDrawArcTangential(*document_, *view_);
        break;
    case RS2::ActionDrawEllipseAxis:
        a = new RS_ActionDrawEllipseAxis(*document_, *view_, false);
        a->setActionType(id);
        break;
    case RS2::ActionDrawEllipseArcAxis:
        a = new RS_ActionDrawEllipseAxis(*document_, *view_, true);
        a->setActionType(id);
        break;
    case RS2::ActionDrawEllipseFociPoint:
        a = new RS_ActionDrawEllipseFociPoint(*document_, *view_);
        break;
    case RS2::ActionDrawEllipse4Points:
        a = new RS_ActionDrawEllipse4Points(*document_, *view_);
        break;
    case RS2::ActionDrawEllipseCenter3Points:
        a = new RS_ActionDrawEllipseCenter3Points(*document_, *view_);
        break;
    case RS2::ActionDrawEllipseInscribe:
        a = new RS_ActionDrawEllipseInscribe(*document_, *view_);
        break;
    case RS2::ActionDrawSpline:
        a = new RS_ActionDrawSpline(*document_, *view_);
        break;
    case RS2::ActionDrawSplinePoints:
        a = new LC_ActionDrawSplinePoints(*document_, *view_);
        break;
    case RS2::ActionDrawMText:
        a = new RS_ActionDrawMText(*document_, *view_);
        break;
    case RS2::ActionDrawText:
        a = new RS_ActionDrawText(*document_, *view_);
        break;
    case RS2::ActionDrawHatch:
        if(!document_->countSelected())
        {
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionDrawHatchNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionDrawHatchNoSelect:
        a = new RS_ActionDrawHatch(*document_, *view_);
        break;
    case RS2::ActionDrawImage:
        a = new RS_ActionDrawImage(*document_, *view_);
        break;

        // Dimensioning actions:
        //
    case RS2::ActionDimAligned:
        a = new RS_ActionDimAligned(*document_, *view_);
        break;
    case RS2::ActionDimLinear:
        a = new RS_ActionDimLinear(*document_, *view_);
        break;
    case RS2::ActionDimLinearHor:
        a = new RS_ActionDimLinear(*document_, *view_, 0.0, true, RS2::ActionDimLinearHor);
        break;
    case RS2::ActionDimLinearVer:
        a = new RS_ActionDimLinear(*document_, *view_, M_PI_2, true, RS2::ActionDimLinearVer);
        break;
    case RS2::ActionDimRadial:
        a = new RS_ActionDimRadial(*document_, *view_);
        break;
    case RS2::ActionDimDiametric:
        a = new RS_ActionDimDiametric(*document_, *view_);
        break;
    case RS2::ActionDimAngular:
        a = new RS_ActionDimAngular(*document_, *view_);
        break;
    case RS2::ActionDimLeader:
        a = new RS_ActionDimLeader(*document_, *view_);
        break;

        // Modifying actions:
        //
    case RS2::ActionModifyAttributes:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyAttributesNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyAttributesNoSelect:
        a = new RS_ActionModifyAttributes(*document_, *view_);
        break;
    case RS2::ActionModifyDelete:
        a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyDeleteNoSelect);
        break;
    case RS2::ActionModifyDeleteNoSelect:
        a = new RS_ActionModifyDelete(*document_, *view_);
        break;
    case RS2::ActionModifyDeleteQuick:
        a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyDeleteQuick);
        break;
    case RS2::ActionModifyDeleteFree:
        a = new RS_ActionModifyDeleteFree(*document_, *view_);
        break;
    case RS2::ActionModifyMove:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyMoveNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyMoveNoSelect:
        a = new RS_ActionModifyMove(*document_, *view_);
        break;
    case RS2::ActionModifyRevertDirection:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyRevertDirectionNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyRevertDirectionNoSelect:
        a = new RS_ActionModifyRevertDirection(*document_, *view_);
        break;
    case RS2::ActionModifyRotate:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyRotateNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyRotateNoSelect:
        a = new RS_ActionModifyRotate(*document_, *view_);
        break;
    case RS2::ActionModifyScale:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyScaleNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyScaleNoSelect:
        a = new RS_ActionModifyScale(*document_, *view_);
        break;
    case RS2::ActionModifyMirror:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyMirrorNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyMirrorNoSelect:
        a = new RS_ActionModifyMirror(*document_, *view_);
        break;
    case RS2::ActionModifyMoveRotate:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyMoveRotateNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyMoveRotateNoSelect:
        a = new RS_ActionModifyMoveRotate(*document_, *view_);
        break;
    case RS2::ActionModifyRotate2:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyRotate2NoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyRotate2NoSelect:
        a = new RS_ActionModifyRotate2(*document_, *view_);
        break;
    case RS2::ActionModifyEntity:
        a = new RS_ActionModifyEntity(*document_, *view_);
        break;
    case RS2::ActionModifyTrim:
        a = new RS_ActionModifyTrim(*document_, *view_, false);
        a->setActionType(id);
        break;
    case RS2::ActionModifyTrim2:
        a = new RS_ActionModifyTrim(*document_, *view_, true);
        a->setActionType(id);
        break;
    case RS2::ActionModifyTrimAmount:
        a = new RS_ActionModifyTrimAmount(*document_, *view_);
        break;
    case RS2::ActionModifyCut:
        a = new RS_ActionModifyCut(*document_, *view_);
        break;
    case RS2::ActionModifyStretch:
        a = new RS_ActionModifyStretch(*document_, *view_);
        break;
    case RS2::ActionModifyBevel:
        a = new RS_ActionModifyBevel(*document_, *view_);
        break;
    case RS2::ActionModifyRound:
        a = new RS_ActionModifyRound(*document_, *view_);
        break;
    case RS2::ActionModifyOffset:
    {
        auto allowedOffsetTypes={RS2::EntityArc, RS2::EntityCircle, RS2::EntityLine, RS2::EntityPolyline};
        if(!document_->countSelected(true, allowedOffsetTypes)){
            a = new RS_ActionSelect(this, *document_, *view_,RS2::ActionModifyOffsetNoSelect, allowedOffsetTypes);
            break;
        }
    }
    // fall-through
    case RS2::ActionModifyOffsetNoSelect:
        a = new RS_ActionModifyOffset(*document_, *view_);
        break;
    case RS2::ActionModifyExplodeText:
        if(!document_->countSelected(false, {RS2::EntityText, RS2::EntityMText})){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionModifyExplodeTextNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionModifyExplodeTextNoSelect:
        a = new RS_ActionModifyExplodeText(*document_, *view_);
        break;

        // Snapping actions:
        //
    case RS2::ActionSnapFree:
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapFree);
        slotSnapFree();
        break;
    case RS2::ActionSnapCenter:
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapCenter);
        slotSnapCenter();
        break;
    case RS2::ActionSnapDist:
        slotSnapDist();
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapDist);
        break;
    case RS2::ActionSnapEndpoint:
        slotSnapEndpoint();
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapEndpoint);
        break;
    case RS2::ActionSnapGrid:
        slotSnapGrid();
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapGrid);
        break;
    case RS2::ActionSnapIntersection:
        slotSnapIntersection();
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapIntersection);
        break;
    case RS2::ActionSnapMiddle:
        slotSnapMiddle();
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapMiddle);
        break;
    case RS2::ActionSnapOnEntity:
        slotSnapOnEntity();
//        a = new RS_ActionSetSnapMode(*document_, *view_, RS2::SnapOnEntity);
        break;
//    case RS2::ActionSnapIntersectionManual:
//        a = new RS_ActionSnapIntersectionManual(*document_, *view_);
//        break;

        // Snap restriction actions:
        //
    case RS2::ActionRestrictNothing:
        slotRestrictNothing();
//        a = new RS_ActionSetSnapRestriction(*document_, *view_, RS2::RestrictNothing);
        break;
    case RS2::ActionRestrictOrthogonal:
        slotRestrictOrthogonal();
//        a = new RS_ActionSetSnapRestriction(*document_, *view_, RS2::RestrictOrthogonal);
        break;
    case RS2::ActionRestrictHorizontal:
        slotRestrictHorizontal();
//        a = new RS_ActionSetSnapRestriction(*document_, *view_, RS2::RestrictHorizontal);
        break;
    case RS2::ActionRestrictVertical:
        slotRestrictVertical();
//        a = new RS_ActionSetSnapRestriction(*document_, *view_, RS2::RestrictVertical);
        break;

        // Relative zero:
        //
    case RS2::ActionSetRelativeZero:
        a = new RS_ActionSetRelativeZero(*document_, *view_);
        break;
    case RS2::ActionLockRelativeZero:
        a = new RS_ActionLockRelativeZero(*document_, *view_, true);
        break;
    case RS2::ActionUnlockRelativeZero:
        a = new RS_ActionLockRelativeZero(*document_, *view_, false);
        break;

        // Info actions:
        //
    case RS2::ActionInfoInside:
        a = new RS_ActionInfoInside(*document_, *view_);
        break;
    case RS2::ActionInfoDist:
        a = new RS_ActionInfoDist(*documen, *view_);
        break;
    case RS2::ActionInfoDist2:
        a = new RS_ActionInfoDist2(*document_, *view_);
        break;
    case RS2::ActionInfoAngle:
        a = new RS_ActionInfoAngle(*document_, *view_);
        break;
    case RS2::ActionInfoTotalLength:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionInfoTotalLengthNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionInfoTotalLengthNoSelect:
        a = new RS_ActionInfoTotalLength(*document_, *view_);
        break;
    case RS2::ActionInfoArea:
        a = new RS_ActionInfoArea(*document_, *view_);
        break;

        // Layer actions:
        //
    case RS2::ActionLayersDefreezeAll:
        a = new RS_ActionLayersFreezeAll(false, *document_, *view_);
        break;
    case RS2::ActionLayersFreezeAll:
        a = new RS_ActionLayersFreezeAll(true, *document_, *view_);
        break;
    case RS2::ActionLayersUnlockAll:
        a = new RS_ActionLayersLockAll(false, *document_, *view_);
        break;
    case RS2::ActionLayersLockAll:
        a = new RS_ActionLayersLockAll(true, *document_, *view_);
        break;
    case RS2::ActionLayersAdd:
        a = new RS_ActionLayersAdd(*document_, *view_);
        break;
    case RS2::ActionLayersRemove:
        a = new RS_ActionLayersRemove(*document_, *view_);
        break;
    case RS2::ActionLayersEdit:
        a = new RS_ActionLayersEdit(*document_, *view_);
        break;
    case RS2::ActionLayersToggleView:
        a = new RS_ActionLayersToggleView(*document_, *view_, a_layer);
        break;
    case RS2::ActionLayersToggleLock:
        a = new RS_ActionLayersToggleLock(*document_, *view_, a_layer);
        break;
    case RS2::ActionLayersTogglePrint:
        a = new RS_ActionLayersTogglePrint(*document_, *view_, a_layer);
        break;
    case RS2::ActionLayersToggleConstruction:
        a = new LC_ActionLayersToggleConstruction(*document_, *view_, a_layer);
        break;
        // Block actions:
        //
    case RS2::ActionBlocksDefreezeAll:
        a = new RS_ActionBlocksFreezeAll(false, *document_, *view_);
        break;
    case RS2::ActionBlocksFreezeAll:
        a = new RS_ActionBlocksFreezeAll(true, *document_, *view_);
        break;
    case RS2::ActionBlocksAdd:
        a = new RS_ActionBlocksAdd(*document_, *view_);
        break;
    case RS2::ActionBlocksRemove:
        a = new RS_ActionBlocksRemove(*document_, *view_);
        break;
    case RS2::ActionBlocksAttributes:
        a = new RS_ActionBlocksAttributes(*document_, *view_);
        break;
    case RS2::ActionBlocksEdit:
        a = new RS_ActionBlocksEdit(*document_, *view_);
        break;
    case RS2::ActionBlocksSave:
        a = new RS_ActionBlocksSave(*document_, *view_);
        break;
    case RS2::ActionBlocksInsert:
        a = new RS_ActionBlocksInsert(*document_, *view_);
        break;
    case RS2::ActionBlocksToggleView:
        a = new RS_ActionBlocksToggleView(*document_, *view_);
        break;
    case RS2::ActionBlocksCreate:
        if(!document_->countSelected()){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionBlocksCreateNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionBlocksCreateNoSelect:
        a = new RS_ActionBlocksCreate(*document_, *view_);
        break;
    case RS2::ActionBlocksExplode:
        if(!document_->countSelected(true, {RS2::EntityBlock})){
            a = new RS_ActionSelect(this, *document_, *view_, RS2::ActionBlocksExplodeNoSelect);
            break;
        }
        // fall-through
    case RS2::ActionBlocksExplodeNoSelect:
        a = new RS_ActionBlocksExplode(*document_, *view_);
        break;


        // library browser:
        //
    case RS2::ActionLibraryInsert:
        a = new RS_ActionLibraryInsert(*document_, *view_);
        break;

        // options:
        //
        //case RS2::ActionOptionsGeneral:
        //    a = new RS_ActionOptionsGeneral(*document_, *view_);
        //	break;

    case RS2::ActionOptionsDrawing:
        a = new RS_ActionOptionsDrawing(*document_, *view_);
        break;*/
    default:
        RS_DEBUG->print(RS_Debug::D_WARNING,
                        "QG_ActionHandler::setCurrentAction():"
                        "No such action found.");
        break;
    }

    if (a) {
      view_->setCurrentAction(a);
    }

    RS_DEBUG->print("QG_ActionHandler::setCurrentAction(): OK");
    return a;
}

void QG_ActionHandler::slotZoomIn() {
  setCurrentAction(RS2::ActionZoomIn);
}

void QG_ActionHandler::slotZoomOut() {
  setCurrentAction(RS2::ActionZoomOut);
}

void QG_ActionHandler::slotZoomAuto() {
  setCurrentAction(RS2::ActionZoomAuto);
}

void QG_ActionHandler::slotZoomWindow() {
  setCurrentAction(RS2::ActionZoomWindow);
}

void QG_ActionHandler::slotZoomPreivous() {
  setCurrentAction(RS2::ActionZoomPrevious);
}

void QG_ActionHandler::slotZoomRedraw() {
  setCurrentAction(RS2::ActionZoomRedraw);
}

void QG_ActionHandler::slotEditKillAllActions() {
  setCurrentAction(RS2::ActionEditKillAllActions);
}

void QG_ActionHandler::slotEditUndo() {
  killAllActions();
  setCurrentAction(RS2::ActionEditUndo);
}

void QG_ActionHandler::slotEditRedo() {
  setCurrentAction(RS2::ActionEditRedo);
}

void QG_ActionHandler::slotEditCut() {
  setCurrentAction(RS2::ActionEditCut);
}

void QG_ActionHandler::slotEditCopy() {
  setCurrentAction(RS2::ActionEditCopy);
}

void QG_ActionHandler::slotEditPaste() {
  setCurrentAction(RS2::ActionEditPaste);
}
