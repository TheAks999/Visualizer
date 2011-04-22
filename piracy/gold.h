#ifndef GOLD_H
#define GOLD_H
#include "../lib/gameobject/gocomponent.h"

class Gold : public GOComponent
{
  public:
    Gold(){}
    ~Gold(){}

    Gold(GameObject * parent, const unsigned int & g){m_gold=g; setOwner(parent);}

    const GOC_IDType componentID() const {return GOC_IDType("Gold");}
    const GOC_IDType familyID() const {return GOC_IDType("Gold");}
    void update(){}

    unsigned int gold(){return m_gold;}
    void gold(const unsigned int & g){m_gold = g;}

  protected:
    unsigned int m_gold;

};
#endif                           // GOLD_H
