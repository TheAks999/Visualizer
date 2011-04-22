#include "timeManager.h"
#include "../renderer/renderer.h"
#include "../gui/gui.h"
#include "../../piracy/dupObj.h"

#include <ctime>

const int& TimeManager::getTurn()
{
  if( !isInit() )
    return 0;


  get()->updateFrames();
  return get()->m_turn;
}

const int& TimeManager::getFrame()
{
  if( !isInit() )
    return 0;
  get()->updateFrames();
  return get()->m_frame;
}

void TimeManager::setTurn( const int& turn )
{
  if( !isInit() )
    throw 0;

  get()->m_turn = turn;
  get()->m_frame = 0;

  //update renderer
  Renderer::update(turn,0);


  if( GUI::getControlBar() )
	GUI::getControlBar()->update();
}

const float& TimeManager::getSpeed()
{
  if( !isSetup() )
    return 0;
  float multi = OptionsMan::getFloat( "speed" );
  return get()->m_speed*multi;
}

bool TimeManager::setSpeed( const float& speed )
{
  if( !isSetup())
    return false;

  float multi = 1;
  if (OptionsMan::exists("speed"))
     multi = OptionsMan::getFloat( "speed" );

  get()->m_speed = speed/multi;

  return true;
}

int TimeManager::timeHash()
{
  if (!isInit())
    return 0;
  return get()->m_hash;
}

TimeManager::mode TimeManager::getMode()
{
  if( !isInit() )
    return mode();
  return get()->m_mode;
}

const int& TimeManager::getNumTurns()
{
  if( !isInit() )
    return 0;

  return get()->m_numTurns;
}

void TimeManager::setNumTurns( const int& numTurns )
{
  if( !isInit() )
    throw 0;
  get()->m_numTurns = numTurns;

  if(GUI::isSetup())
  {
    if( GUI::getControlBar() )
    {
      GUI::getControlBar()->update();//m_slider->setMaximum ( numTurns );
    }
  }
}

bool TimeManager::destroy()
{
    if (!isInit())
	return false;
    if (isSetup())
	delete get()->timer;

    return Singleton<TimeManager>::destroy();
}

bool TimeManager::create()
{
  if( !Singleton<TimeManager>::create() )
    return false;

  //Singleton<TimeManager>::get()->setup();
  get()->m_isSetup = false;
   return true;
}

bool TimeManager::setup()
{
  if (!isInit())
      return false;

  if (isSetup())
      return false;

  get()->m_lastTime = clock();

  if (OptionsMan::exists("framesPerTurn"))
    get()->m_framesPerTurn = OptionsMan::getInt("framesPerTurn");
  else
    get()->m_framesPerTurn = 100;

  get()->m_turn = 0;
  get()->m_frame = 0;

  get()->timer = new QTimer( getSelf() );
  connect( get()->timer, SIGNAL(timeout()), getSelf(), SLOT(timerUpdate()) );

  get()->m_isSetup = true;
  return true;
}



bool TimeManager::isSetup()
{
    if (!isInit())
	return false;

    return get()->m_isSetup;
}


bool TimeManager::timerStart()
{
    if (!isSetup())
    {
	std::cout << "Error: Time Manager timer start fail\n";
	return false;
    }

    get()->timer->start( 35 );
    return true;
}


#include <iostream>
using namespace std;

void TimeManager::updateFrames()
{
  m_turn += m_frame / m_framesPerTurn;
  m_frame %= m_framesPerTurn;

  //Idiot check low
  if (m_turn < 0)
  {
    m_turn = 0;
    m_frame = 0;
  }

  //Idiot check high
  if (m_turn >= m_numTurns)
  {
    m_turn = m_numTurns-1;
    m_frame = m_framesPerTurn-1;
  }

  //If in arena mode, show winner for a few secs at end
  if (OptionsMan::getBool("arenaMode") && m_turn == m_numTurns-1 && m_numTurns > 5)
  {
    if( m_sleepTime == -1 )
      m_sleepTime = clock();
    else
    {
      if( clock() - m_sleepTime > 1000000 )
      {
        GUI::closeGUI();
      }
    }
  } 

  if(GUI::isSetup())
  {

    GUI::getControlBar()->m_slider->setValue ( m_turn );
  }
}

void TimeManager::timerUpdate()
{

    m_time = ((clock() - m_lastTime) / CLOCKS_PER_SEC) * 1000;
    m_hash++;

    //! @todo acceleration here, fix it
    m_frame += m_time * m_speed;
    updateFrames();
    if (Renderer::isSetup() && ObjectManager::turns())
    {
	Renderer::refresh();
	Renderer::update(m_turn,0);
    }
}

QObject * TimeManager::getSelf()
{
    if (!isInit())
	return NULL;

    return get()->_getSelf();
}

QObject * TimeManager::_getSelf()
{
    return this;
}
