#ifndef GOCFAMILY_GUI_H
#define GOCFAMILY_GUI_H

#include "../gameobject/gocomponent.h"

class GOCFamily_GUI: public GOComponent
{
public:
  GOCFamily_GUI();

  virtual ~GOCFamily_GUI() = 0;

  virtual const GOC_IDType familyID() const
  {
    return GOC_IDType( "GUIFamily" );
  }

  virtual void renderAt( const unsigned int& turn, const unsigned int& frame ) = 0;


};

#endif
