#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "renderwidget.h"
#include "../components/gocfamily_controlbar.h"
#include "../components/gocfamily_guitoolset.h"

class CentralWidget: public QWidget
{
public:
  CentralWidget( QWidget *parent = 0 );
  ~CentralWidget();

private:
  // Important Widgets
  GOCFamily_ControlBar *m_controlBarWidget;
  //RenderWidget *m_renderWidget;


  // Layout Widgets
  QVBoxLayout *m_widgetLayout;

  // Build the Control Bar Widget at the Bottom
  void buildControlBar();

};


#endif
