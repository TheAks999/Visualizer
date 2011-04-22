
template<class T>
RenderData<T>::RenderData( const int& x, const int& y, const int& z )
: m_x(x), m_y(y), m_z(z)
{
  m_dupList = new T**[x];
  for( int x = 0; x < m_x; x++ )
  {
    m_dupList = new T*[y];
    for( int y = 0; y < m_y; y++ )
    {
      m_dupList = new T[z];
    }
  }
}
