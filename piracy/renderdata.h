#ifndef RENDERDATA_H
#define RENDERDATA_H

#include "../lib/timemanager/timeManager.h"

class RenderDataInfo
{
  public:

    void update()
    {
      if( m_updateHash != TimeManager::timeHash() )
      {
        m_updateHash = TimeManager::timeHash();
        clear();
      }
    }

    virtual void clear() = 0;

  private:
    int m_updateHash;

};

template<class T>
class RenderData
{
  public:
    RenderData( const int& x, const int& y, const int& z );

  private:
    int m_x;
    int m_y;
    int m_z;
    RenderDataInfo ***m_dupList;

};

#include "renderdata.hpp"
#endif
