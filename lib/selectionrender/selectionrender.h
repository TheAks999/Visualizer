#ifndef SELECTIONRENDER_H
#define SELECTIONRENDER_H
#include "../components/gocfamily_render.h"
#include "../singleton.h"

class SelectionRender : public GOCFamily_Render, Singleton <SelectionRender>
{
	public:
		void setSelectionBox(int, int, int, int); //X1, Y1, X2, Y2 Screen Resolution
    int getX1() { return m_X1; }
    int getX2() { return m_X2; }
    int getY1() { return m_Y1; }
    int getY2() { return m_Y2; }
    

		bool getUpdated();
		void setUpdated(bool);
		
		bool getDragging();
		void setDragging(bool);
		
     static SelectionRender * get(){
      if( !Singleton<SelectionRender>::isInit() )
      {
        Singleton<SelectionRender>::create();
      }
      return Singleton <SelectionRender>::get();}

      const GOC_IDType componentID() const
      {
        return GOC_IDType( "SelectionRender" );
      }
      void update() {};
		
	private:
		void renderAt(const unsigned int & turn, const unsigned int & frame);
	
		bool m_updated;		//Finished dragging
		bool m_dragging;	//Currently dragging
	
	int m_X1, m_Y1, m_X2, m_Y2;
};

#endif
