#include "gocfamily_data.h"

#if 0
template<class T>
const GOC_IDType& GOCFamily_Data<T>::familyID() const
{
  return GOC_IDType( "DataFamily" );
}


#if 0
template<class T>
const GOC_IDType& GOCFamily_Data<T>::familyID() const
{
  return GOC_IDType( "DataFamily" );
}
#endif

#if 1
template<class T>
T* GOCFamily_Data<T>::getDataAt( const unsigned int& turn, const unsigned int& frame )
{
  return m_timeline( turn, frame );
}
#endif
#endif
