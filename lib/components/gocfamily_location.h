#ifndef GOCFAMILY_LOCATION_H
#define GOCFAMILY_LOCATION_H

#include "../gameobject/gocomponent.h"

class GOCFamily_Location :public GOComponent
{
public:
    GOCFamily_Location()
    {
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_dir = 0;
    }

    const GOC_IDType familyID() const
    {
    return GOC_IDType( "LocationFamily" );
    };

    int x(){return m_x;}
    int y(){return m_y;}
    int z(){return m_z;}
    int dir(){return m_dir;}

    void update(){}

    protected:
    int m_x, m_y, m_z, m_dir;

};



#endif // GOCFAMILY_LOCATION_H
