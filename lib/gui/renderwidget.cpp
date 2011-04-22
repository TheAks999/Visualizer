#include "renderwidget.h"
#include "../../piracy/dupObj.h"
#include "../renderer/renderer.h"
#include "gui.h"

#include <iostream>
using namespace std;

#if 0

RenderWidget::RenderWidget( QWidget *parent )
: QGLWidget( QGLFormat( QGL::SampleBuffers ), parent )
{
  glInit();
  initializeGL();

}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{
  Renderer::setParent( this );
  QGLWidget::initializeGL();
  cout << "VALID: " << isValid() << endl;
}

void RenderWidget::resizeEvent( QResizeEvent *evt )
{
  Renderer::resize( evt->size().width(), evt->size().height() );
}

void RenderWidget::mousePressEvent( QMouseEvent *e )
{
    if( e->button() == Qt::LeftButton )
    {
      //QString line;
      
      initialX = e->x();
      initialY = e->y();
       
     	SelectionRender::get()->setSelectionBox(initialX, initialY, initialX+1, initialY+1);
 	    //+1 guarantees we create a box, rather than a point.
       
      //line.clear();
      //line.append("Left click: ( ");
      //line.append(QString::number(initialX));
      //line.append(", ");
      //line.append(QString::number(initialY));
      //line.append(")");


      leftButtonDown = true;
      

      /* Thus, dragX and dragY become our starting point, 
       * and curX and curY will be contiuously updated, eventually becoming 
       * our ending point if dragging.
       */
    }


}

void RenderWidget::mouseReleaseEvent( QMouseEvent *e )
{

    currentX = e->x()+1;
    currentY = e->y()+1;
    //+1 guarantees we create a box, rather than a point.
    
		SelectionRender::get()->setUpdated(true); 
		SelectionRender::get()->setDragging(false); 		   

    Renderer<DupObj>::update( TimeManager::getTurn(), 0 );

}


void RenderWidget::mouseMoveEvent( QMouseEvent *e )
{
  currentX = e->x();
  currentY = e->y();

  // If Manhattan distance is m_DRAG_DISTANCE or greater, we're draggin
  if( e->buttons() & Qt::LeftButton && 
    abs(currentX-initialX)+abs(currentY-initialY) > m_DRAG_DISTANCE )
  {
    leftButtonDrag = true;
    SelectionRender::get()->setDragging(true);
   	SelectionRender::get()->setSelectionBox(initialX, initialY, currentX, currentY);        
  }
}
#endif
