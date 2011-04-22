#ifndef GOCTEMPLATE_H
#define GOCTEMPLATE_H
#include "gocomponent.h"

class GOCTemplate
{
	public:
		/** Default constructor */
		GOCTemplate();
		/** Default destructor */
		virtual ~GOCTemplate() = 0;

		virtual GOC_IDType & componentType() = 0;
		virtual GOC_IDType & familyType() = 0;

		virtual GOComponent * makeComponent() = 0;
	protected:
	private:
};

#endif // GOCTEMPLATE_H
