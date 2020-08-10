#include "rs_graphic.h"

#include "rs_units.h"
#include "rs_settings.h"

RS_Graphic::RS_Graphic()
{

}

void RS_Graphic::setPaperSize(const RS_Vector& s) {
  addVariable("$PLIMMIN", RS_Vector(0.0,0.0), 10);
  addVariable("$PLIMMAX", s, 10);
  //set default paper size
  RS_Vector def = RS_Units::convert(s, getUnit(), RS2::Millimeter);

  RS_SETTINGS->beginGroup("/Print");
  RS_SETTINGS->writeEntry("/PaperSizeX", def.x);
  RS_SETTINGS->writeEntry("/PaperSizeY", def.y);
  RS_SETTINGS->endGroup();
}

void RS_Graphic::setUnit(RS2::Unit u) {
  setPaperSize(RS_Units::convert(getPaperSize(), getUnit(), u));
  addVariable("$INSUNITS", (int)u, 70);
}

RS2::Unit RS_Graphic::getUnit() {
  return (RS2::Unit)getVariableInt("$INSUNITS", 0);
}

double RS_Graphic::getPagerScale() {
  return getVariableDouble("$PSVPSCALE", 1.0);
}

RS_Vector RS_Graphic::getPaperInsertionBase() {
    return getVariableVector("$PINSBASE", RS_Vector(0.0,0.0));
}


RS_Vector RS_Graphic::getPaperSize() {
  RS_SETTINGS->beginGroup("/Print");
  bool okX,okY;
  double sX = RS_SETTINGS->readEntry("/PaperSizeX", "0.0").toDouble(&okX);
  double sY = RS_SETTINGS->readEntry("/PaperSizeY", "0.0").toDouble(&okY);
  RS_SETTINGS->endGroup();

  RS_Vector def ;
  if(okX&&okY && sX>RS_TOLERANCE && sY>RS_TOLERANCE) {
    def=RS_Units::convert(RS_Vector(sX,sY),
                          RS2::Millimeter, getUnit());
  }else{
    def= RS_Units::convert(RS_Vector(210.0,297.0),
                           RS2::Millimeter, getUnit());
  }

  RS_Vector v1 = getVariableVector("$PLIMMIN", RS_Vector(0.0,0.0));
  RS_Vector v2 = getVariableVector("$PLIMMAX", def);

  return v2-v1;
}


RS_Vector RS_Graphic::getPrintAreaSize(bool total) {
  RS_Vector printArea = getPaperSize();
  printArea.x -= RS_Units::convert(marginLeft_ + marginRight_, RS2::Millimeter, getUnit());
  printArea.y -= RS_Units::convert(marginTop_ + marginBottom_, RS2::Millimeter, getUnit());

  if (total) {
    printArea.x *= pagesNumH;
    printArea.y *= pagesNumV;
  }
  return printArea;
}
