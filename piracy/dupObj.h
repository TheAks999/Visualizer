#ifndef DUPOBJ_H
#define DUPOBJ_H
#include "gold.h"
#include "objecttype.h"
#include "piracylocations.h"
#include "../lib/components/goc_owner.h"
#include <GL/gl.h>
#include "../lib/resourcemanager/resourceman.h"
#include "../lib/resourcemanager/texture.h"
#include "piratehealth.h"
#include "../lib/renderer/textRenderer/drawGLFont.h"
#include <list>

struct DupObj
{
  unsigned int objType;
  unsigned int gold;
  unsigned int pirates;
  unsigned int owner;
  unsigned int time;
  unsigned int index;
  unsigned int x, y;
  unsigned int health;
  unsigned int maxHealth;
  bool selected;


  DupObj & operator+=(const DupObj & obj)
  {
    if (obj.time == time)
    {
      gold += obj.gold;
      pirates += obj.pirates;
      if( obj.selected )
        selected = true;

      return *this;
    }

    objType = obj.objType;
    selected = obj.selected;
    gold = obj.gold;
    pirates = obj.pirates;
    owner = obj.owner;
    time = obj.time;
    x = obj.x;
    y = obj.y;
    health = obj.health;
    maxHealth = obj.maxHealth;

    //! @todo object type precedences: ex ship over pirate, pirate over treasure
    if (objType == POT_PORT || obj.objType == POT_PORT)
    {
      objType = POT_PORT;
    }
    else if (objType == POT_SHIP || obj.objType == POT_SHIP)
    {
      objType = POT_SHIP;
    }
    else if (objType == POT_PIRATE || obj.objType == POT_PIRATE)
    {
      objType = POT_PIRATE;
    }
    else
    {
      objType = POT_TREAS;
    }
    return *this;
  }

  void render()
  {

    glPushMatrix();
    #if 0
    glTranslatef(x-.1,y-.1,0);
    glScalef(1.2,1.2,1);
    #else
    glTranslatef(x,y,0);
    #endif
    bool flag = false;
    if (ResourceMan::isInit())
    {                            //! @todo: textures here
      glEnable(GL_TEXTURE_2D);
      Resource * res;
      std::string textureName;
      switch (objType)
      {
        case POT_PIRATE:
          switch (owner)
          {
            case 0:
              textureName = "pirateRed";
              break;
            case 1:
              textureName = "pirateGreen";
              break;
            default:
              textureName = "pirateNPC";
          }
          break;
        case POT_SHIP:
          switch (owner)
          {
            case 0:
              textureName = "shipRed";
              break;
            case 1:
              textureName = "shipGreen";
              break;
            default:
              textureName = "shipNPC";
          }
          break;
        case POT_PORT:
          switch (owner)
          {
            case 0:
              textureName = "portRed";
              break;
            case 1:
              textureName = "portGreen";
              break;
            default:
              textureName = "portNPC";
          }
          break;
        case POT_TREAS:
          textureName = "treasure";
          break;
        default:
          break;
          //fuckoff
          // TODO: UNCOMMENT FIX
          //std::cout << "B Bad Object Type\n";
      }

      res = ResourceMan::reference(textureName,"dupObject");
      if (res)
      {

        glEnable(GL_BLEND);
        glColor4f(1,1,1,1);
        glBindTexture(GL_TEXTURE_2D,((ResTexture*)res)->getTexture());
        glBegin(GL_QUADS);

        glVertex3f(0,0,-1); glTexCoord2f(1,1);
        glVertex3f(1,0,-1); glTexCoord2f(1,0);
        glVertex3f(1,1,-1); glTexCoord2f(0,0);
        glVertex3f(0,1,-1); glTexCoord2f(0,1);

        glEnd();

        ResourceMan::release(textureName,"dupObject");

      }
      else
      {
        flag = true;
      }

      glDisable(GL_TEXTURE_2D);
    }
    else
    {
      flag = true;
    }

    if (flag)
    {
      //std::cout << "Render: l(" << x << "," << y << ") \n";
      glDisable(GL_BLEND);
      switch (objType)
      {
        case POT_PIRATE:
          switch (owner)
          {
            case 0:
              glColor4f(1,0,0,1);
              break;
            case 1:
              glColor4f(0,1,0,1);
              break;
            default:
              glColor4f(.1,.1,.1,1);
          }
          break;
        case POT_SHIP:

          switch (owner)
          {
            case 0:
              glColor4f(1,0.5,0.5,1);
              break;
            case 1:
              glColor4f(0.5,1,0.5,1);
              break;
            default:
              glColor4f(0.5,.5,.5,1);
          }

          break;
        case POT_PORT:
          switch (owner)
          {
            case 0:
              glColor4f(.5,0,0,1);
              break;
            case 1:
              glColor4f(0,.5,0,1);
              break;
            default:
              glColor4f(0,.5,.5,1);
          }
          break;
        case POT_TREAS:
          glColor4f(1,1,0,1);
          break;
        default:
          break;
          //TODO: UNCOMMENT FIX
          //std::cout << "A Bad Object Type\n";
      }

      glBegin(GL_QUADS);

      glVertex3d(0,0,1);
      glVertex3d(1,0,1);
      glVertex3d(1,1,1);
      glVertex3d(0,1,1);

      glEnd();

      glEnable(GL_BLEND);
    }

    //draw pirate count

    //draw gold count

    if (maxHealth > 0)
    {
      //draw health
      glDisable(GL_BLEND);
      glBegin(GL_QUADS);
      glColor4f(1,0,0,1);
      glVertex3d(1,1,-2);
      glVertex3d(0,1,-2);
      glVertex3d(0,.9,-2);
      glVertex3d(1,.9,-2);

      unsigned int width = health/maxHealth;
      glColor4f(0,1,0,1);
      glVertex3d(0,1,-1.9);
      glVertex3d(0,.85,-1.9);
      glVertex3d(width,.85,-1.9);
      glVertex3d(width,1,-1.9);
      glEnd();

      glEnable(GL_BLEND);
    }

    if (selected)
    {
      switch( owner )
      {
        case 0:
          glColor3f( 1, 0, 0 );
          break;
        case 1:
          glColor3f( 0, 1, 0 );
          break;
        case 2:
          glColor3f( 0, 0, 0 );
          break;
        case 3:
          glColor3f( 1, 1, 1 );
          break;
      }
      glDisable(GL_BLEND);
      glBegin(GL_LINE_LOOP);
      glLineWidth(3);
      glVertex3d(1,1,-2);
      glVertex3d(0,1,-2);
      glVertex3d(0,0,-2);
      glVertex3d(1,0,-2);
      glLineWidth(1);
      glEnd();
      glEnable(GL_BLEND);
    }

    glPopMatrix();
  }

};

template<typename DupObject>
void setDupObj(GameObject * object, DupObject & dup)
{
  if (!object)
    return;                      //! @todo fuck off

  bool flag = false;

  GOComponent * goc = object->getGOC("ObjectType");
  PiracyObjectType ot;
  if (goc)
    ot = ((ObjectType*)(object->getGOC("ObjectType")))->type();
  else
  {
    ot = POT_NONE;
    std::cout << "object has no Type\n";
    flag = true;
  }

  goc = object->getGOC("Gold");
  if (goc)
    dup.gold = ((Gold*)(goc))->gold();
  else
  {
    dup.gold = 0;

    flag = ot != POT_PORT;
    if(flag)
      std::cout << "object has no gold\n";
  }

  goc = object->getGOC("Owner");
  if (goc)
    dup.owner = ((GOC_Owner*)(goc))->owner();
  else
  {
    dup.owner = -1;

    flag = ot != POT_TREAS;
    if(flag)
      std::cout << "object has no Owner\n";
  }

  goc = object->getGOC("HealthFamily");
  if (goc)
  {
    dup.health = ((GOCFamily_Health*)(goc))->currentHealth();
    dup.maxHealth = ((GOCFamily_Health*)(goc))->maxHealth();

  }
  else
  {
    dup.health = 0;
    dup.maxHealth = 0;
  }

  switch (ot)
  {
    case POT_PIRATE:
      dup.objType = POT_PIRATE;
      dup.pirates = 1;
      break;
    case POT_SHIP:
      dup.objType = POT_SHIP;
      dup.pirates = 0;
      break;
    case POT_PORT:
      dup.objType = POT_PORT;
      dup.pirates = 0;
      break;
    case POT_TREAS:
      dup.objType = POT_TREAS;
      dup.pirates = 0;
      break;
    default:
      //fuckoff
      std::cout << "AAAHHH!!! NO OBJECT TYPE!!\n";
  }

  if (flag)
  {
    std::cout << "Component List:\n";
    std::vector<GOC_IDType> components = object->listComponentFamilies();
    for (unsigned int i = 0; i < components.size(); i++)
    {
      std::cout << "comp " << i << ": " << components[i] << '\n';
    }
  }
}
#endif
