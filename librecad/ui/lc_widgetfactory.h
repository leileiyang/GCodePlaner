#ifndef LC_WIDGETFACTORY_H
#define LC_WIDGETFACTORY_H

#include <QObject>
#include <QMap>
#include <QString>

#include "gcodeplaner.h"

class QAction;

class LC_ActionGroupManager;

class LC_WidgetFactory : public QObject {
    Q_OBJECT
 public:
  explicit LC_WidgetFactory(GCodePlaner *main_win,
                            QMap<QString, QAction*> &action_map,
                            LC_ActionGroupManager *agm);

  void createStandardToolbars(QG_ActionHandler *action_handler);

 signals:

 public slots:

 private:
  GCodePlaner *main_window_;
  QMap<QString, QAction*> &a_map_;
  LC_ActionGroupManager *ag_manager_;
};

#endif // LC_WIDGETFACTORY_H
