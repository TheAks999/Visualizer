

#ifndef GOC_CONTROLBAR_H
#define GOC_CONTROLBAR_H

#include "gocfamily_controlbar.h"

class GOC_ControlBar : public GOCFamily_ControlBar
{
	public:
		/** Default constructor */
		GOC_ControlBar();
		/** Default destructor 
		 * @todo needs to be written */
		virtual ~GOC_ControlBar() = 0;

		virtual const GOC_IDType & componentID() const {return GOC_IDType("ControlBar");}
		/** switches the label on the play/pause button when it is pushed
		 * @todo needs to be written */
		virtual void playPause() = 0;
		/**
		 * retrieves the number of turns that were played in the game
		 * @return the number of turns that were played in the game
		 * @todo needs to be written */
		virtual int numTurns() = 0;
		/**
		 * retrieves the turn that playback is currently on
		 * @return the turn that playback is currently on
		 * @todo needs to be written */
		virtual int currentTurn() = 0;
	protected:
	private:
};

#endif // GOC_CONTROLBAR_H
