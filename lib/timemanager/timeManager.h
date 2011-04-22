#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QTimer>
#include <time.h>
#include "../singleton.h"
#include "../gui/controlbar.h"

class TimeManager : public QObject, public Singleton<TimeManager>
{
  Q_OBJECT
  public:
 
    TimeManager()
    {
      m_sleepTime = -1;
    }

    enum mode
    {
      Play = 0,
      Pause = 1,
      Stop = 1, // Don't feel the need to differentiate at this point
      Rewind = 2
    };   
    

    static const int& getTurn();
    static const int& getFrame();
    static void setTurn( const int& turn );

    static const int& getNumTurns();
    static void setNumTurns( const int& numTurns );

    static const float& getSpeed();
    static bool setSpeed( const float& speed );

    static int timeHash();
    static mode getMode();

    static bool create();
    static bool destroy();

    static bool setup();
    static bool isSetup();

    void updateFrames();
    static bool timerStart();

  private slots:
    void timerUpdate();

  private:
    int m_turn;
    int m_numTurns;
    int m_frame;
    int m_framesPerTurn;
    mode m_mode;

    QTimer *timer;

    float m_speed;
    int m_lastTime;
    int m_hash;
    int m_sleepTime;
    int m_time;
    bool m_isSetup;

    static QObject * getSelf();
    QObject * _getSelf();

};


#endif
