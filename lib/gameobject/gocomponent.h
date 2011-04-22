#ifndef GOCOMPONENT_H
#define GOCOMPONENT_H

#include <string>
#include "gameobject.h"
//to make changing the id type easy

class GameObject;
typedef std::string GOC_IDType ;

class GOComponent
{
	public:
		/** Default constructor */
		GOComponent();
    GOComponent( GameObject* owner );
#if 0
		/** Default destructor */
		virtual ~GOComponent() = 0;
#endif

		virtual const GOC_IDType componentID() const = 0;
		virtual const GOC_IDType familyID() const = 0;

		virtual void update() = 0;

		void setOwner( GameObject * owner);
		GameObject * getOwner();

	protected:
	private:
		GameObject * m_owner;
};

#endif // GOCOMPONENT_H
