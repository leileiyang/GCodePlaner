#include "lc_widgetfactory.h"

#include <QToolBar>

#include "lc_actiongroupmanager.h"

LC_WidgetFactory::LC_WidgetFactory(GCodePlaner *main_win,
                                   QMap<QString, QAction*> &action_map,
                                   LC_ActionGroupManager *agm):
    QObject(nullptr),
    main_window_(main_win),
    a_map_(action_map),
    ag_manager_(agm) {}


void LC_WidgetFactory::createStandardToolbars(QG_ActionHandler */*action_handler*/) {
  QSizePolicy tool_bar_policy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QToolBar *view_toolbar = new QToolBar(GCodePlaner::tr("View"), main_window_);
  view_toolbar->setObjectName("view_toolbar");
  view_toolbar->setSizePolicy(tool_bar_policy);
  view_toolbar->addAction(a_map_["ViewGrid"]);
  view_toolbar->addAction(a_map_["ViewDraft"]);
  view_toolbar->addSeparator();
  view_toolbar->addAction(a_map_["ZoomRedraw"]);
  view_toolbar->addAction(a_map_["ZoomIn"]);
  view_toolbar->addAction(a_map_["ZoomOut"]);
  view_toolbar->addAction(a_map_["ZoomAuto"]);
  view_toolbar->addAction(a_map_["ZoomPrevious"]);
  view_toolbar->addAction(a_map_["ZoomWindow"]);
  view_toolbar->addAction(a_map_["ZoomPan"]);

  main_window_->addToolBar(Qt::TopToolBarArea, view_toolbar);
}
