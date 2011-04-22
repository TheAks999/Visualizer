#ifndef GOCFAMILY_DATA_H
#define GOCFAMILY_DATA_H

#include "../gameobject/gameobject.h"
#include "../gameobject/gocomponent.h"
#include "../timeline/timeline.h"

template <class T>
class GOCFamily_Data : public GOComponent
{
	public:
#if 0
		/** Default constructor */
		GOCFamily_Data();
		/** Default destructor */
		virtual ~GOCFamily_Data() = 0;
#endif

		const GOC_IDType familyID() const
    {
      return GOC_IDType( "DataFamily" );
    };		

    T * getData()
    {
      return &m_data;
    }

	protected:
	    T m_data;

	private:
};

#endif

