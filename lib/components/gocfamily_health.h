#ifndef GOCFAMILY_HEALTH_H
#define GOCFAMILY_HEALTH_H
#include "../gameobject/gocomponent.h"

class GOCFamily_Health : public GOComponent
{
    public:
    GOCFamily_Health(){m_currentHealth = 0;}
    GOCFamily_Health(GameObject * parent){setOwner(parent);m_currentHealth = 0;}
    GOCFamily_Health(GameObject * parent, const int & currentHealth,const int & maxHealth){setOwner(parent);m_currentHealth = currentHealth;m_maxHealth = maxHealth;}

    unsigned int maxHealth()
    {
      return m_maxHealth;
    }

    unsigned int currentHealth()
    {
      return m_currentHealth;
    }

    const GOC_IDType familyID() const { return GOC_IDType("HealthFamily"); }
    void update(){}

    float healthPercent()
    {
	return (m_maxHealth?((float)m_currentHealth)/((float)m_maxHealth):1);
    }

protected:
    unsigned int m_currentHealth;
    unsigned int m_maxHealth;
};

#endif // GOCFAMILY_HEALTH_H
