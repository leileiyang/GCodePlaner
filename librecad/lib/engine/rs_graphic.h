#ifndef RS_GRAPHIC_H
#define RS_GRAPHIC_H

#include "rs_variabledict.h"

class RS_Graphic {
 public:
  RS_Graphic();

  double getPagerScale();
  RS_Vector getPaperInsertionBase();
  RS_Vector getPrintAreaSize(bool total=true);
  RS_Vector getPaperSize();
  void setPaperSize(const RS_Vector& s);

  void setUnit(RS2::Unit u);
  RS2::Unit getUnit();

  void addVariable(const QString& key, const RS_Vector& value, int code) {
    variableDict_.add(key, value, code);
  }
  void addVariable(const QString& key, const QString& value, int code) {
    variableDict_.add(key, value, code);
  }
  void addVariable(const QString& key, int value, int code) {
    variableDict_.add(key, value, code);
  }
  void addVariable(const QString& key, double value, int code) {
    variableDict_.add(key, value, code);
  }

  RS_Vector getVariableVector(const QString& key, const RS_Vector& def) {
      return variableDict_.getVector(key, def);
  }
  QString getVariableString(const QString& key, const QString& def) {
      return variableDict_.getString(key, def);
  }
  int getVariableInt(const QString& key, int def) {
      return variableDict_.getInt(key, def);
  }
  double getVariableDouble(const QString& key, double def) {
      return variableDict_.getDouble(key, def);
  }

 private:
  RS_VariableDict variableDict_;

  // Paper margins in millimeters
  double marginLeft_;
  double marginTop_;
  double marginRight_;
  double marginBottom_;

  // Number of pages drawing occupies
  int pagesNumH;
  int pagesNumV;

};

#endif // RS_GRAPHIC_H
