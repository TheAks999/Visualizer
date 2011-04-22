#ifndef GOC_XYZ_LOCATION_H
#define GOC_XYZ_LOCATION_H
#include "gocfamily_location.h"

template<typename T>
class GOC_XYZ_Locationt : public GOCFamily_Location
{
public:
    GOC_XYZ_Location(){}
    virtual void update() = 0;
    ~GOC_XYZ_Location(){}

    T & x(){return m_x;}
    T & y(){return m_y;}
    T & z(){return m_z;}
private:
    T m_x;
    T m_y;
    T m_z;
};


class GOC_XYZ_Locationf : public GOC_XYZ_Locationt<float>
{
public:
    void update(){}
};

class GOC_XYZ_Locationi : public GOC_XYZ_Locationt<int>
{
public:
    void update(){}

};

class GOC_XYZ_Locationui : public GOC_XYZ_Locationt<unsigned int>
{
public:
    void update(){}

};

class GOC_XYZ_Locationd : public GOC_XYZ_Locationt<double>
{
public:
    void update(){}

};

#endif // GOC_XYZ_LOCATION_H
