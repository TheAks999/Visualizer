#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include "../optionsmanager/optionsman.h"

class ControlBar : public QWidget 
{
  friend class GUI;
  friend class TimeManager;
  Q_OBJECT
public:
  ControlBar( QWidget *parent = 0 );

  void update();

private slots:
  void sliderDrag();
  void sliderRelease();
  void sliderChanged(int value);
  void rewind();
  void play();
  void fastForward();

private:
  QLabel* turnLabel;
  QSlider* m_slider;
  QPushButton* rewindButton;
  QPushButton* playButton;
  QPushButton* fastForwardButton;
  float originalTimeManagerSpeed;
};

#endif
