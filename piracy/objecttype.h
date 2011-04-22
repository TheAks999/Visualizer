#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H
#include "../lib/gameobject/gocomponent.h"

enum PiracyObjectType
{
  POT_NONE, POT_PIRATE, POT_PORT, POT_SHIP, POT_TREAS
};

class ObjectType : public GOComponent
{
  public:
    ObjectType(){m_type = POT_NONE;}
    ObjectType(GameObject* parent, const PiracyObjectType & type){setOwner(parent); m_type = type;}
    ~ObjectType(){}

    const GOC_IDType componentID() const {return GOC_IDType("ObjectType");}
    const GOC_IDType familyID() const {return GOC_IDType("ObjectType");}

    void update(){}

    PiracyObjectType type(){return m_type;}
    void type(PiracyObjectType type){m_type = type;}

  protected:
    PiracyObjectType m_type;
};
#endif                           // OBJECTTYPE_H
