#include "centralwidget.h"
#include "gui.h"
#include <QLabel>

CentralWidget::~CentralWidget()
{
  delete m_controlBarWidget;
  //delete m_renderWidget;
  delete m_widgetLayout;

}

CentralWidget::CentralWidget( QWidget* /*parent*/ )
{
  //!  @todo set this part in Renderer setup
  //m_renderWidget = new RenderWidget( this );
  m_widgetLayout = new QVBoxLayout( this );

  m_widgetLayout->setContentsMargins( 0, 0, 0, 0 );
  //m_widgetLayout->addWidget( m_renderWidget );
  buildControlBar();

  setLayout( m_widgetLayout );
}

void CentralWidget::buildControlBar()
{  
  m_controlBarWidget = 
    (GOCFamily_ControlBar*)GUI::getGUIObject( "ControlBar" );

  if( m_controlBarWidget && 
      (
       !OptionsMan::isInit() ||
       !OptionsMan::exists( "arenaMode" ) ||
       !OptionsMan::getBool( "arenaMode" )
      )
    )
  {
    if( 
	OptionsMan::isInit() &&
	OptionsMan::exists("maxControlHeight")
      )
    {
      m_controlBarWidget->setMaximumHeight( 
	  OptionsMan::getInt( "maxControlHeight" )
          );
    }
    m_widgetLayout->addWidget( m_controlBarWidget );
  }
}

