#ifndef PIRACYLOCATIONS_H
#define PIRACYLOCATIONS_H
#include "../lib/components/gocfamily_location.h"
#include "../lib/parser/parser.h"

class PiracyLocation: public GOCFamily_Location
{
  public:
    bool parseLocation(Mappable * mappable)
    {
      if (!mappable)
        return false;

      m_x = mappable->x;
      m_y = mappable->y;
      return true;
    }

    const GOC_IDType componentID() const {return GOC_IDType("Location");}
    ~PiracyLocation(){}

};
#endif                           // PIRACYLOCATIONS_H
