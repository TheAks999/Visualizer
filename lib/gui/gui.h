#ifndef GUI_H
#define GUI_H

#include "centralwidget.h"
#include "controlbar.h"
#include "../timemanager/timeManager.h"
#include "../singleton.h"
#include "../components/gocfamily_gui.h"
#include "../objectmanager/objectloader.h"


#include <QtGui>
#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QStringList>
#include <QString>
#include <map>
#include <string>
using namespace std;

typedef GOCFamily_GUI guiObj;

////////////////////////////////////////////////////////////////
/// @class    GUI
/// @brief    GUI object for drawing debugging info along with
///           the QOpenGL Widget
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       reg( const std::string& id, guiObj *obj )
/// @brief    Registers the desired object with the gui.  Must
///           do for controlBar, debugWindow, etc.
/// @param    id Unique identifier for this object.
/// @param    obj The object we're registering
/// @pre      id must be unique and obj must be a valid object
/// @post     The object will be registered with the GUI
/// @return   bool True if successfully registered. False,
///           if otherwise.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       del( const std::string& id )
/// @brief    Unregisters the desired object from the gui.
/// @param    id Unique identifier to delete an object.
/// @pre      id must refer to an object within GUI
/// @post     The object will be unregistered with the GUI
/// @return   bool True if successfully unregistered.
///           False, if otherwise.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       setup()
/// @brief    Sets up the GUI along with the singleton
/// @pre      Object must have been created beforehand
/// @post     The GUI will be all setup
/// @return   bool True if successfully setup.
///           False, if otherwise.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       clear()
/// @brief    Destroys the instance to the GUI.
/// @pre      GUI must exist for it to be destroyed.
/// @post     The GUI instance will be destroyed.
/// @return   bool True if successfully destroyed.
///           False, if otherwise
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       getGUIObject( const std::string& id )
/// @brief    Get the desired object by name
/// @param    id Unique identifier to get an object
/// @pre      Object must be registered with id
/// @post     The pointer to the object of id will be returned
/// @return   guiObj* The desired object if found, zero if otherwise.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       create()
/// @brief    Set's up the GUI along with the singleton
/// @pre      Object must have been created before hand
/// @post     The GUI will be all setup
/// @return   bool True if successfully setup.
///           False, if otherwise.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       destroy()
/// @brief    Destroys the instance to the GUI.
/// @pre      GUI must exist for it to be destroyed.
/// @post     The GUI instance will be destroyed.
/// @return   bool True if successfully destroyed.
///           False, if otherwise
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       numObjects()
/// @brief    Get the number of registered objects in GUI
/// @pre      None
/// @post     Number of registered objects will be returned.
/// @return   unsigned int representing the number of objects
///           in the GUI
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       isSetup()
/// @brief    Is the GUI object setup properly?
/// @pre      None
/// @post     Returns whether GUI is setup or not
/// @return   bool True if setup.  False, if otherwise.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       resizeEvents( QResizeEvent* evt )
/// @brief    Deal with a resize action
/// @param    evt Contains various data related to the event.
/// @pre      None
/// @post     Appropriately deals with the window getting resized.
/// @return   None
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       helpContents()
/// @brief    Respond to Help->Contents
/// @pre      None
/// @post     Opens up a URL to the help page.
/// @return   None
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       doSetup()
/// @brief    Setup the window
/// @pre      None
/// @post     Sets up the Window with the QOpenGL object, menus, etc.
/// @return   bool True if everything went alright.
///           False, if otherwise.
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       createActions()
/// @brief    Build the actions needed for this GUI
/// @pre      None
/// @post     Action set will be built
/// @return   None
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
/// @fn       createMenus()
/// @brief    Build the menus for this window
/// @pre      None
/// @post     Menus will be built
/// @return   None
////////////////////////////////////////////////////////////////

class GUI : public QMainWindow, public Singleton<GUI>
{
  Q_OBJECT
  
  friend class RenderWidget;
  
public:
  GUI() : m_isSetup(false) {};
  ~GUI();
  static bool reg( const std::string& id, guiObj *obj );
  static bool del( const std::string& id );

  static bool setup();
  static bool clear();

  static guiObj *getGUIObject( const std::string& id );

  static bool create();
  static bool destroy();

  static unsigned int numObjects();

  static bool isSetup();
  static QMainWindow * getGUI();

  /// EVENTS
  void dragEnterEvent( QDragEnterEvent *evt );
  void dropEvent( QDropEvent* evt );
  void resizeEvent( QResizeEvent* evt );

  /// GAME SPECIFIC.  NEED TO BE MOVED ELSEWHERE>
  static void loadGamelog( std::string gamelog );

  static void update();
  static void closeGUI();
  
  static ControlBar * getControlBar();

  static void appendConsole( string line );
  static void appendConsole( QString line );
  static void clearConsole();
  
  bool getFullScreen();
  void setFullScreen(bool);
  
private slots:
  void helpContents();
  void fileOpen();
  void toggleFullScreen();
  void togglePlayPause();
  void fastForwardShortcut();
  void rewindShortcut();
  void stepTurnForwardShortcut();
  void stepTurnBackShortcut();

  void catchEscapeKey();
  
  void turnPercentageShortcut1();
  void turnPercentageShortcut2();
  void turnPercentageShortcut3();
  void turnPercentageShortcut4();
  void turnPercentageShortcut5();
  void turnPercentageShortcut6();
  void turnPercentageShortcut7();
  void turnPercentageShortcut8();
  void turnPercentageShortcut9();
  void turnPercentageShortcut0();

public:

  static QTableWidget* getMultipleStats();
  static QTableWidget* getIndividualStats();

private:
  
  QTableWidget * m_multipleStats;
  QTableWidget * m_individualStats;
  inline QMainWindow * _getGUI();

  /// Container for the objects in the GUI
  std::map<std::string, guiObj*> m_objects;
  /// Setup?
  bool m_isSetup;

  //In full screen mode or not?
  bool fullScreen;

  /// Main widget for this window
  CentralWidget *m_centralWidget;

  /// Dock Widget For Debugging Info
  QDockWidget *m_dockWidget;

  /// Frame used to hold layout for widgets in dock
  QFrame *m_dockLayoutFrame;

  /// Layout For the Dock Widget
  QVBoxLayout *m_dockLayout;

  /// Console Area
  QTextEdit *m_consoleArea;

  /// Unit Stats Area
  QTabWidget * m_unitStatsArea;
  QStringList m_multipleStatsVerticalLabels;
  QStringList m_multipleStatsHorizontalLabels;

  QStringList m_individualStatsVerticalLabels;
  QStringList m_individualStatsHorizontalLabels;

  /// Status Bar
  QStatusBar *m_statusBar;

  /// Control Bar
  ControlBar *m_controlBar;

  /// Debugging Toolset Widget Within the Dock
  GOCFamily_GUIToolSet *m_toolSetWidget;

  bool doSetup();
  void buildControlBar();
  void createActions();
  void createMenus();
  void buildToolSet();
  void initUnitStats();

  void turnPercentageCalc(int);


  // Actions
  QAction *m_helpContents; /// Help->Contents

  QAction *m_fileOpen; /// File->Open
  QAction *m_fileExit; /// File->Exit

  QAction *toggleFullScreenAct; /// View -> Toggle Full Screen
  
  QString m_previousDirectory;
	QRect m_normalWindowGeometry;

};

#endif
