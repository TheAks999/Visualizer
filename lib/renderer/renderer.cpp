#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "renderer.h"
#include "../selectionrender/selectionrender.h"
#include "../components/goc_owner.h"
#include <sstream>
using namespace std;


/** @brief resize
 * resize and refresh the projection  and modelview matricies
 * @param width the x size of the render area.
 * @param height the y size of the render area.
 * @param depth the z depth of the render area. default 10
 * @return true if successful resize
 */
bool Renderer::resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth)
{
  if (!Single::isInit())
    return false;

  unsigned int _height = height?height:1;

  glViewport( 0, 0, (GLint)width, (GLint)_height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho( 0, width,_height,0, -depth, depth );

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  Single::get()->m_height = _height;
  Single::get()->m_width = width;
  Single::get()->m_depth = depth;
  refresh();
  return true;
}


Renderer::Renderer():QGLWidget( QGLFormat( QGL::SampleBuffers ), NULL )
{
}


/** @brief refresh
 *	draw objects on screen
 * @return true if successful
 */
bool Renderer::refresh()
{


  if (!isSetup())
    return false;

#if 0
  if(SelectionRender::get()->getUpdated())
  {
    update( TimeManager::getTurn(), 0 );
  }
#endif

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  std::map<int, renderObj*>::iterator it = Single::get()->m_renderConstant.begin();

  for( ; it != Single::get()->m_renderConstant.end(); it++ )
  {
    GOCFamily_Render *r = it->second;
    if( r )
    {
      r->renderAt( TimeManager::getTurn(), 0 );
    }
  }

  glPushMatrix();
  float mapSize = (float)OptionsMan::getInt("mapSize");
  glScalef( height()/mapSize, height()/mapSize, 1 );

#if 0
  typename std::vector<DupObject*>::iterator renderIt = Single::get()->m_renderList.begin();
  for (; renderIt != Single::get()->m_renderList.end(); renderIt++)
  {
    glPushMatrix();
    (*renderIt)->render();
    glPopMatrix();
  }
#endif
  std::cout << "rendering\n";

  glPopMatrix();



   if (!flushGlErrors())
  {
       std::cout << "Error: ending render\n";
       return false;
   }
   else
   {
       char ini;
       std::cout << "Render isValid() " << get()->isValid() << '\n';
       //std::cin >> ini;
   }

  Single::get()->swapBuffers();

  //SelectionRender::get()->setUpdated(false);

  return true;
}


bool Renderer::flushGlErrors()
{
    GLenum errCode;
    const GLubyte *errString;

    if ((errCode = glGetError()) != GL_NO_ERROR)
    {
            errString = gluErrorString(errCode);
            fprintf (stderr, "OpenGL Error: %s\n", errString);
            return false;
    }
    return true;
}

void Renderer::setParent( QWidget *parent )
{
  if (!Single::isInit())
    return;                      //! @todo throw error

  Single::get()->QGLWidget::setParent(parent);
}


/** @brief destroy
 * destroy the singleton
 * @return true on success
 */
bool Renderer::destroy()
{
  if(!Single::isInit())
    return false;

  if (!clear())
    return false;

  return Single::destroy();
}


/** @brief create
 * create the singleton and setup the render area
 * @return true on success
 */
bool Renderer::create()
{
  //if (!Single::create())
  //return false;
    if (isInit())
	return false;

    m_base = new Renderer();
    Single::m_isInit = true;

  Single::get()->m_height = 0;
  Single::get()->m_width  = 0;
  Single::get()->m_depth  = 10;
  get()->m_glInit = false;
  get()->m_resizeSetup = false;
  //Single::get()->m_dupListDirs = 0;
  //Single::get()-> m_duplicateList = NULL;

  return true;
}


bool Renderer::setupResize()
{
    if ( Single::get()->m_width && Single::get()->m_height && Single::get()->m_depth )
    {
      resize( Single::get()->m_width, Single::get()->m_height, Single::get()->m_depth );
    }
    else if ( Single::get()->m_width && Single::get()->m_height )
    {
      resize( Single::get()->m_width, Single::get()->m_height );
    }
    else if ( OptionsMan::isInit() )
    {
      if ( OptionsMan::exists(renderHeightName) && OptionsMan::optionType(renderDepthName) == OT_INT &&
	OptionsMan::exists(renderWidthName) && OptionsMan::optionType(renderWidthName) == OT_INT )
      {
	if ( OptionsMan::exists(renderDepthName) && OptionsMan::optionType(renderDepthName) == OT_INT)
	{
	  resize( OptionsMan::getInt(renderWidthName),
	    OptionsMan::getInt(renderHeightName),
	    OptionsMan::getInt(renderDepthName) );
	}
	else
	{
	  resize( OptionsMan::getInt(renderWidthName),
	    OptionsMan::getInt(renderHeightName) );
	}
      }
    }

    get()->m_resizeSetup = true;
    return true;
}

bool Renderer::setupOGL()
{
    if (isSetup())
	return false;

    bool flag = true;

    get()->initializeGL();

    std::cout << "test1\n";
    glShadeModel( GL_SMOOTH );
    flag &= flushGlErrors();
    std::cout << "test2\n";
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    flag &= flushGlErrors();
    std::cout << "test3\n";
    glClearDepth( 1.0f );
    flag &= flushGlErrors();

    std::cout << "test4\n";
    glEnable( GL_DEPTH_TEST );
    flag &= flushGlErrors();
    std::cout << "test5\n";
    glDepthFunc( GL_LEQUAL );
    flag &= flushGlErrors();


    std::cout << "test6\n";
    glDisable( GL_TEXTURE_2D );
    flag &=flushGlErrors();
    std::cout << "test7\n";
    glEnable( GL_BLEND );
    std::cout << "test8\n";
    flag &= flushGlErrors();
    std::cout << "test9\n";
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    if (!flushGlErrors() || !flag)
        return false;


    flushGlErrors();
    get()->m_glInit = true;
    return true;
}



/** @brief setup
 * setup the rendering for the render, size the screen according to
 *	the width and height given
 * @return true if successful
 * @todo add more to the render setup
 */
bool Renderer::setup()
{
  if (!Single::isInit())
  {
    std::cout << "Renderer Error: Trying to set up an uninitialized Renderer\n";
    return false;
  }

  if (isSetup())
  {
      std::cout << "Renderer Error: Trying to setup an already setup Renderer\n";
      return false;
  }

  if (!setupResize())
      return false;


  if (!setupOGL())
      return false;


  refresh();

  return true;
}


/** @brief isSetup
 * access if the module has been set up
 * @return true if set up
 */
bool Renderer::isSetup()
{
  if (!Single::isInit())
    return false;

  return get()->m_glInit && get()->m_resizeSetup;
}


/** @brief clear
 * clear all references to render objects
 * @return true on success
 */
bool Renderer::clear()
{
  if (!Single::isInit())
    return false;

  #if 0
  if (Single::get()->m_duplicateList)
  {
    for (unsigned int x = 0; x < width(); x++)
    {
      for (unsigned int y = 0; y < height(); y++)
      {
        for (unsigned int z = 0; z < depth(); z++)
        {
          delete Single::get()->m_duplicateList[x][y][z];
        }
        delete [] Single::get()->m_duplicateList[x][y];
      }
      delete [] Single::get()->m_duplicateList[x];
    }
    delete [] Single::get()->m_duplicateList;
  }
  #endif

  //Single::get()->m_duplicateList = NULL;

  std::map<int, renderObj*>::iterator it = Single::get()->m_renderConstant.begin();
  for(; it!=Single::get()->m_renderConstant.end(); it++ )
  {
    delete (it->second);
  }

  Single::get()->m_renderConstant.clear();

  return true;
}



bool Renderer::registerConstantObj( const unsigned int& id, renderObj* obj )
{
  if (!Single::isInit())
  {
    return false;
  }

  if( Single::get()->m_renderConstant.find( id ) != Single::get()->m_renderConstant.end() )
  {
    return false;
    delete Single::get()->m_renderConstant[id];
  }

  Single::get()->m_renderConstant[id] = obj;

  return true;
}



bool Renderer::deleteConstantObj( const unsigned int& id )
{
    std::map<int,renderObj*>::iterator it = Single::get()->m_renderConstant.find( id );

  if( it != Single::get()->m_renderConstant.end() )
  {
    delete Single::get()->m_renderConstant[id];
    Single::get()->m_renderConstant.erase( it );
    return true;
  } else
  {
    return false;
  }

}


/**
 * @todo doxyment
 */
unsigned int Renderer::width()
{
  if (isSetup())
    return Single::get()->m_width;

  return 0;
}


/**
 * @todo doxyment
 */
unsigned int Renderer::height()
{
  if (isSetup())
    return Single::get()->m_height;

  return 0;
}


/**
 * @todo doxyment
 */
unsigned int Renderer::depth()
{
  if (isSetup())
    return Single::get()->m_depth;

  return 0;
}


/**
 * @todo doxyment
 */
bool Renderer::update(const unsigned int & turn, const unsigned int & frame)
{
#if 0

Stats global, p0, p1, p2, p3, selected;
  int health;

  if (!Single::isInit())
  {
    std::cout << "Update Failed: Renderer is not inititalized or setup\n";
    return false;
  }                              //! @todo fuck off

  typedef std::map<ObjIdType,LookupNode<GameObject*,ObjIdType>* > Bucket;
  Bucket * bucket = ObjectManager::getBucket(turn,frame);

  if (!bucket)
  {
    std::cout << "Bucket Requested at (" << turn <<","<<frame << ") does not exist\n";
    return false;
  }

  //Single::get()->m_renderList.clear();
  int time = TimeManager::timeHash();

  bool selectUpdate = SelectionRender::get()->getUpdated();
  float mapSize = (float)OptionsMan::getInt("mapSize");
  float unitSize  = height()/mapSize;

  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

  if( selectUpdate )
  {

    x1 = SelectionRender::get()->getX1()/unitSize;
    x2 = SelectionRender::get()->getX2()/unitSize;
    if( x2 < x1 )
    {
      int temp;
      temp = x2;
      x2 = x1;
      x1 = temp;
    }

    y1 = SelectionRender::get()->getY1()/unitSize;
    y2 = SelectionRender::get()->getY2()/unitSize;

    if( y2 < y1 )
    {
      int temp;
      temp = y1;
      y1 = y2;
      y2 = temp;
    }
  
    stringstream ss;
    ss << "(" << x1 << ", " << y1 << ") -> (" 
      << x2 << ", " << y2 << ")" << endl; 

    GUI::clearConsole();
    GUI::appendConsole( ss.str() );
    Single::get()->selectedUnitIds.clear();
  }

  Bucket::iterator it = bucket->begin();
  for (;it != bucket->end(); it++)
  {
    int owner = 0;
    if (it->second)
    {
      DupObject temp;
      setDupObj(it->second->data,temp);
      GOComponent * goc = it->second->data->getGOC( "Owner" );
      if( goc )
      {
        owner = ((GOC_Owner*)goc)->owner();
      }
      goc = it->second->data->getGOC("LocationFamily");
      if (goc)
      {
        GOCFamily_Location * loc = (GOCFamily_Location *)(goc);

        if( selectUpdate )
        {
          if( loc->x() >= x1 &&
            loc->x() <= x2 &&
            loc->y() >= y1 &&
            loc->y() <= y2 )
          {
            temp.selected = true;
            #if 1
            int id = it->first;
            Single::get()->selectedUnitIds.insert( id );

            stringstream ss;
            #endif
          } else 
          {
            temp.selected = false;
          }
        } 

        goc = it->second->data->getGOC( "HealthFamily" );
        if( goc )
        {
          health = ((GOCFamily_Health*)goc)->currentHealth();
        }

        Stats tStats;
        goc = it->second->data->getGOC( "ObjectType" );
        bool treasure = false;
        if( goc )
        {
          switch( ((ObjectType*)goc)->type() )
          {
            case POT_PIRATE:
              tStats.avgPirateHealth = health;

              tStats.pirates = 1;
              goc = it->second->data->getGOC( "Gold" );
              tStats.gold = ((Gold*)goc)->gold();
              break;
            case POT_SHIP:
              tStats.avgShipHealth = health;
              tStats.ships = 1;
              goc = it->second->data->getGOC( "Gold" );
              tStats.gold = ((Gold*)goc)->gold();
              break;
            case POT_PORT:
              tStats.ports = 1;
              break;
            case POT_TREAS:
              treasure = true;
              tStats.treasures = 1;
              goc = it->second->data->getGOC( "Gold" );
              tStats.gold = ((Gold*)goc)->gold();
              break;
            default:
              break;
          }
        }


        if( Single::get()->selectedUnitIds.find( it->first ) != Single::get()->selectedUnitIds.end() )
        {
          temp.selected = true;
        }
        else
        {
          temp.selected = false;
        }

        if( temp.selected )
        {
          if( !treasure )
          {
            switch( owner )
            {
              case 0:
                p0 += tStats;
                break;
              case 1:
                p1 += tStats;
                break;
              case 2:
                p2 += tStats;
                break;
              case 3:
                p3 += tStats;
                break;
            }
          } else {
            selected += tStats;
          }
        } else
        {
          global += tStats;
        }


        updateLocation(loc->x(),loc->y(),loc->z(),loc->dir(),time,temp);

      }
      else
      {
        std::cout << "no location for obj type: " << temp.objType << '\n';
      }

    }

  }

  selected += p0;
  selected += p1;
  selected += p2;
  selected += p3;

  global += selected;

  p0.final();
  p1.final();
  p2.final();
  p3.final();
  selected.final();
  global.final();

  Single::get()->multipleUnitStatColumnPopulate (global, 0);
  Single::get()->multipleUnitStatColumnPopulate (p0, 1);
  Single::get()->multipleUnitStatColumnPopulate (p1, 2);
  Single::get()->multipleUnitStatColumnPopulate (selected, 3);
  Single::get()->multipleUnitStatColumnPopulate (p2, 4);
  Single::get()->multipleUnitStatColumnPopulate (p3, 5);
#endif
  return true;

}


void Renderer::printToTable( QTableWidget *w, int c, int r, QString str )
{
  if( w->itemAt( c, r ) )
  {
    w->itemAt( c, r )->setText( str );
  } else {
    w->setItem( c, r, new QTableWidgetItem( str ) );
  }

}


void Renderer::printIndividuals( int c, int r, QString str )
{
  printToTable( GUI::getIndividualStats(), c, r, str );
}


void Renderer::printGlobalSelected( int r, int c, QString str )
{
  printToTable( GUI::getMultipleStats(), c, r, str );
}


void Renderer::multipleUnitStatColumnPopulate (Stats multi, int column)
{
    if  (!Single::isInit())
	return;

  Single::get()->printGlobalSelected( column, 1, QString::number(multi.pirates));
  Single::get()->printGlobalSelected( column, 2, QString::number(multi.avgPirateHealth));
  Single::get()->printGlobalSelected( column, 3, QString::number(multi.avgPirateGold));
  Single::get()->printGlobalSelected( column, 4, QString::number(multi.gold));
  Single::get()->printGlobalSelected( column, 5, QString::number(multi.ships));
  Single::get()->printGlobalSelected( column, 6, QString::number(multi.avgShipHealth));
  Single::get()->printGlobalSelected( column, 7, QString::number(multi.avgShipGold));
  Single::get()->printGlobalSelected( column, 8, QString::number(multi.treasures));
  //Single::get()->printGlobalSelected( column, 0, QString::number(0));
}




void Renderer::initializeGL()
{
    if (!isInit())
	return;

    if (!get()->m_glInit )
    {
	QGLWidget::initializeGL();
         cout << "VALID: " << isValid() << endl;
     }
}


void Renderer::resizeEvent( QResizeEvent *evt )
{
  if (isSetup())
  Renderer::resize( evt->size().width(), evt->size().height() );
}


void Renderer::mousePressEvent( QMouseEvent *e )
{
    if( e->button() == Qt::LeftButton )
    {
      //QString line;

	Single::get()->initialX = e->x();
      Single::get()->initialY = e->y();

	SelectionRender::get()->setSelectionBox(Single::get()->initialX, Single::get()->initialY, Single::get()->initialX+1, Single::get()->initialY+1);
	    //+1 guarantees we create a box, rather than a point.

      //line.clear();
      //line.append("Left click: ( ");
      //line.append(QString::number(initialX));
      //line.append(", ");
      //line.append(QString::number(initialY));
      //line.append(")");


      Single::get()->leftButtonDown = true;


      /* Thus, dragX and dragY become our starting point,
       * and curX and curY will be contiuously updated, eventually becoming
       * our ending point if dragging.
       */
    }


}


void Renderer::mouseReleaseEvent( QMouseEvent *e )
{

    Single::get()->currentX = e->x()+1;
    Single::get()->currentY = e->y()+1;
    //+1 guarantees we create a box, rather than a point.

		SelectionRender::get()->setUpdated(true);
		SelectionRender::get()->setDragging(false);

    update( TimeManager::getTurn(), 0 );

}

void Renderer::mouseMoveEvent( QMouseEvent *e )
{
  Single::get()->currentX = e->x();
  Single::get()->currentY = e->y();

  // If Manhattan distance is m_DRAG_DISTANCE or greater, we're draggin
  if( e->buttons() & Qt::LeftButton &&
    abs(Single::get()->currentX-Single::get()->initialX)+abs(Single::get()->currentY-Single::get()->initialY) > Single::get()->m_DRAG_DISTANCE )
  {
    Single::get()->leftButtonDrag = true;
    SelectionRender::get()->setDragging(true);
	SelectionRender::get()->setSelectionBox(Single::get()->initialX, Single::get()->initialY, Single::get()->currentX, Single::get()->currentY);
  }
}


const int Renderer::m_DRAG_DISTANCE = 6;

#endif
