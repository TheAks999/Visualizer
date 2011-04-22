#include "gameobject.h"

unsigned int GameObject::id()
{
  return m_id;
}

void GameObject::id( const unsigned int& ID ) 
{
  m_id = ID;
}



/** @brief ~GameObject
  *
  * @todo: document this function
  */
 GameObject::~GameObject()
{
	ComponentTable_t::iterator it = m_components.begin();
	for (; it != m_components.end(); it++)
	{
		if (it->second)
		{
			delete it->second;
		}
	}
}

/** @brief clearGOCs
  *
  * @todo: document this function
  */
void GameObject::clearGOCs()
{
	ComponentTable_t::iterator it = m_components.begin();
	for (; it != m_components.end(); it++)
	{
		if (it->second)
		{
			delete it->second;
		}
	}
	m_components.clear();
}

#include <iostream>
using namespace std;

/** @brief setGOC
  *
  * @todo: document this function
  */
void GameObject::setGOC(GOComponent * newComp)
{
	if (newComp)
	{
		ComponentTable_t::iterator it = m_components.find(newComp->familyID());
		if( it != m_components.end())
		{
			delete it->second;
		}
		m_components[newComp->familyID()] = newComp;
	}
}

/** @brief getGOC
  *
  * @todo: document this function
  */
GOComponent* GameObject::getGOC(const GOC_IDType & familyID)
{

  ComponentTable_t::iterator it = m_components.find( familyID );
  if( it != m_components.end() )
  {
    // This is returning junk for some reason.
    return it->second;
  }
	return NULL;
}

/** @brief GameObject
  *
  * @todo: document this function
  */
 GameObject::GameObject(const unsigned int & id):m_id(id)
{

}

/** @brief listComponentFamilies
  *
  * @todo: document this function
  */
std::vector<GOC_IDType> GameObject::listComponentFamilies()
{
	ComponentTable_t::iterator it = m_components.begin();
	std::vector<GOC_IDType> vect;
	for (; it != m_components.end(); it++)
	{
		vect.push_back(it->first);
	}
	return vect;
}

/** @brief listComponents
  *
  * @todo: document this function
  */
std::vector<GOC_IDType> GameObject::listComponents()
{
	ComponentTable_t::iterator it = m_components.begin();
	std::vector<GOC_IDType> vect;
	for (; it != m_components.end(); it++)
	{
		vect.push_back(it->second->componentID());
	}
	return vect;
}

/** @brief hasComponentFam
  *
  * @todo: document this function
  */
bool GameObject::hasComponentFam(const GOC_IDType & familyID)
{
	if (m_components.find(familyID) != m_components.end())
	{
		return true;
	}
	return false;
}

