#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
#include <map>
#include <vector>

#include "gocomponent.h"

class Transform{};
class GOComponent;
typedef std::string GOC_IDType ;


class GameObject
{
	public:
		/** Default constructor */
		GameObject(const unsigned int & id);

		unsigned int id();
    void id(const unsigned int & ID);

		bool hasComponentFam(const GOC_IDType & familyID);

		GOComponent * getGOC(const GOC_IDType & familyID);
		void setGOC(GOComponent * newComp);
		void clearGOCs();

		std::vector<GOC_IDType> listComponents();
		std::vector<GOC_IDType> listComponentFamilies();

		/** Default destructor */
		virtual ~GameObject();
	protected:
		/** @todo make timeline object for quicker accessing*/
		//for easy access
		typedef std::map < GOC_IDType /*id*/,GOComponent* /*value*/>
				ComponentTable_t;

		unsigned int m_id;
		ComponentTable_t m_components;
		Transform m_transform;

	private:
};

#endif // GAMEOBJECT_H
