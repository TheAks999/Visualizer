

#ifndef GOCFAMILY_GUITOOLSET_H
#define GOCFAMILY_GUITOOLSET_H

#include "../gameobject/gocomponent.h"
#include <QWidget>

class GOCFamily_GUIToolSet : public GOComponent, public QWidget
{
	public:
		/** Default constructor */
		GOCFamily_GUIToolSet();
		/** Default destructor */
		virtual ~GOCFamily_GUIToolSet() = 0;

		virtual const GOC_IDType familyID() const {return GOC_IDType("GUIToolSetFamily");}

	protected:
	private:
};

#endif // GOCFAMILY_GUITOOLSET_H
