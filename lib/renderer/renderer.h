#ifndef RENDERER_H
#define RENDERER_H

// TODO: Add more includes.  Not nearly enough
#include "../singleton.h"
#include <map>
#include <list>
#include <set>
#include <QTableWidget>
#include <GL/gl.h>
#include "textRenderer/drawGLFont.h"
#include "../optionsmanager/optionsman.h"
#include "../objectmanager/objectmanager.h"
#include "../components/gocfamily_render.h"
#include "../components/gocfamily_location.h"
#include "../gui/gui.h"
#include "../gui/renderwidget.h"
#include "../timemanager/timeManager.h"
#include "../gameobjectmap.h"
#include "../manager/manager.h"
#include <QGLWidget>

//this is a place holder
typedef GOCFamily_Render renderObj;

#define renderHeightName "renderHeight"
#define renderWidthName "renderWidth"
#define renderDepthName "renderDepth"
#define renderDirsName  "renderDirections"

//class RenderWidget;

struct Stats
{
  Stats()
  {
    gold = 0;
    pirates = 0;
    avgPirateHealth = 0;
    avgPirateGold = 0;
    ports = 0;
    ships = 0;
    avgShipHealth = 0;
    avgShipGold = 0;
    treasures = 0;
    portGold = 0;
  }

  Stats& operator += ( const Stats& rhs )
  {
    gold += rhs.gold;
    pirates += rhs.pirates;
    avgPirateHealth += rhs.avgPirateHealth;
    avgPirateGold += rhs.avgPirateGold;
    ships += rhs.ships;
    avgShipHealth += rhs.avgShipHealth;
    avgShipGold += rhs.avgShipGold;
    treasures += rhs.treasures;
    ports += rhs.ports;
    return *this;
  }

  int portGold;
  int ports;
  int gold;
  int pirates;
  int avgPirateHealth;
  int avgPirateGold;
  int ships;
  int avgShipHealth;
  int avgShipGold;
  int treasures;

  void final()
  {
    if( pirates )
    {
      avgPirateGold = pirates;
      avgPirateHealth = pirates;
    }

    if( ships )
    {
      avgShipGold /= ships;
      avgShipHealth /= ships;
    }
  }

};

class Renderer : public Singleton <Renderer>, QGLWidget
{
  public:
    //static bool reg(const unsigned int & id, renderObj * obj);
    //static bool del(const unsigned int & id);

    static bool registerConstantObj( const unsigned int& id, renderObj* obj );
    static bool deleteConstantObj( const unsigned int& id );

    static bool setup(/**@todo make options*/);
    static bool setupResize();
    static bool setupOGL();
    //static void setSetup();


    static bool clear();

    //static renderObj * getRenderObject(const unsigned int id);

    static bool create();
    static bool destroy();

    static void setParent( QWidget *parent );

    static bool refresh();
    static bool resize(const unsigned int & width, const unsigned int & height, const unsigned int & depth = 1);

    //static unsigned int numObjects();

    static bool isSetup();

    static unsigned int height();
    static unsigned int width();
    static unsigned int depth();

    static bool update(const unsigned int & turn, const unsigned int & frame);

    //static bool setupDuplicateList();

    Renderer();

    void initializeGL();

    void resizeEvent( QResizeEvent *evt );

  protected:
  private:
    unsigned int m_height;
    unsigned int m_width;
    unsigned int m_depth;

    bool m_glInit;
    bool m_resizeSetup;

    static bool flushGlErrors();


    typedef std::vector< GameObjectMap <GOCFamily_Render*>* > ObjectMapList;

    ObjectMapList m_objectMap;

    std::map<int, renderObj*> m_renderConstant;

    void multipleUnitStatColumnPopulate( Stats multi, int column );
    void printGlobalSelected( int c, int r, QString str );
    void printIndividuals( int c, int r, QString str );
    void printToTable( QTableWidget *w, int c, int r, QString str );

    typedef Singleton< Renderer > Single;


    set<int> selectedUnitIds;



    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );

    bool leftButtonDown;
    bool leftButtonDrag;

    int currentX;
    int currentY;

    int initialX;
    int initialY;

    static const int m_DRAG_DISTANCE;

    //static void multipleUnitStatColumnPopulate (Stats multi, int column);
};


#endif                           // RENDERER_H
