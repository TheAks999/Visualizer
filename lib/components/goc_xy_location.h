#ifndef GOC_XY_LOCATION_H
#define GOC_XY_LOCATION_H
#include "gocfamily_location.h"

template<typename T>
class GOC_XY_Locationt : public GOCFamily_Location
{
public:
    GOC_XY_Location(){}
    virtual void update() = 0;
    ~GOC_XY_Location(){}

    T & x(){return m_x;}
    T & y(){return m_y;}
private:
    T m_x;
    T m_y;
};


class GOC_XY_Locationf : public GOC_XY_Locationt<float>
{
public:
    void update(){}
};

class GOC_XY_Locationi : public GOC_XY_Locationt<int>
{
public:
    void update(){}

};

class GOC_XY_Locationui : public GOC_XY_Locationt<unsigned int>
{
public:
    void update(){}

};

class GOC_XY_Locationd : public GOC_XY_Locationt<double>
{
public:
    void update(){}

};

#endif // GOC_XY_LOCATION_H
