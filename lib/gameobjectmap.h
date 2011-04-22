#ifndef GAMEOBJECTMAP_H
#define GAMEOBJECTMAP_H
#include "../components/gocfamily_location.h"

typedef std::string GOM_IDType;

class GameObjectMapBoundary
{
    virtual bool isWithinBoundary(GOCFamily_Location * loc) = 0;
};

template <typename Object>
class GameObjectMap
{
public:
    virtual GOM_IDType getMapID() = 0;
    virtual Object * getObjectAt(GOCFamily_Location * loc) = 0;
    virtual bool setObjectAt(GOCFamily_Location * loc, Object * object) = 0;
    virtual GameObjectMapBoundary * getBoundary() = 0;
    virtual bool setBoundary(GameObjectMapBoundary * boundary) = 0;
    virtual bool isWithinBoundary(GOCFamily_Location * loc) = 0;
    virtual bool hasObjectAt(GOCFamily_Location * loc) = 0;
    bool boundarySet(){return m_boundary;}
    GameObjectMap(){m_boundary = NULL;}
private:
    GameObjectMapBoundary * m_boundary;
};


#endif // GAMEOBJECTMAP_H
