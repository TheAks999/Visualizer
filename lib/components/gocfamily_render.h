#ifndef GOCFAMILY_RENDER_H
#define GOCFAMILY_RENDER_H

#include "../gameobject/gocomponent.h"

class GOCFamily_Render : public GOComponent
{
	public:
#if 0
		/** Default constructor */
		GOCFamily_Render();
		/** Default destructor */
		virtual ~GOCFamily_Render() = 0;
#endif

		virtual const GOC_IDType familyID() const {return GOC_IDType("RenderFamily");}
		/** renderAt
		  * this is the main render function for the component */
		virtual void renderAt(const unsigned int & turn, const unsigned int & frame) = 0;
	protected:
	private:
};

#endif // GOCFAMILY_RENDER_H
