#ifndef PIRATEHEALTH_H
#define PIRATEHEALTH_H
#include "../lib/components/gocfamily_health.h"

class PirateHealth : public GOCFamily_Health
{
  public:
    PirateHealth(GameObject*parent, const int & currentHealth, const int & maxHealth):GOCFamily_Health(parent,currentHealth,maxHealth){}
    ~PirateHealth(){}
    const GOC_IDType componentID() const {return GOC_IDType("PirateHealth");}
  private:
};
#endif                           // PIRATEHEALTH_H
