#ifndef QG_ACTIONHANDLER_H
#define QG_ACTIONHANDLER_H

#include "rs_actioninterface.h"

#include <QObject>

class QG_ActionHandler : public QObject {
    Q_OBJECT
 public:
  explicit QG_ActionHandler(QObject *parent = 0);
  virtual ~QG_ActionHandler() = default;

  RS_ActionInterface* getCurrentAction();
  RS_ActionInterface* setCurrentAction(RS2::ActionType id);

  void killSelectActions();
  void killAllActions();

  void setView(RS_GraphicView *graphicView);
  void setDocument(RS_Document *document);

 signals:

 public slots:
  void slotZoomIn();
  void slotZoomOut();
  void slotZoomAuto();
  void slotZoomWindow();
  void slotZoomPreivous();
  void slotZoomRedraw();

  void slotEditKillAllActions();
  void slotEditUndo();
  void slotEditRedo();
  void slotEditCut();
  void slotEditCopy();
  void slotEditPaste();

 private:
  RS2::ActionType orderType{RS2::ActionNone};
  RS_GraphicView *view_{nullptr};
  RS_Document *document_{nullptr};

};

#endif // QG_ACTIONHANDLER_H
