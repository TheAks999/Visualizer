#ifndef GOC_OWNER_H
#define GOC_OWNER_H
#include "../gameobject/gocomponent.h"

class GOC_Owner :public GOComponent
{
public:
    GOC_Owner(){}
    GOC_Owner(GameObject * parent){setOwner(parent);}
    GOC_Owner(GameObject * parent, const int & o){setOwner(parent); owner(o);}
    ~GOC_Owner(){}
    int owner() {return m_owner;}
    void owner(const int & o) {m_owner = o;}
    void update(){}
    const GOC_IDType componentID() const {return GOC_IDType("Owner");}
    const GOC_IDType familyID() const {return GOC_IDType("Owner");}

protected:
    int m_owner;
};

#endif // GOC_OWNER_H

