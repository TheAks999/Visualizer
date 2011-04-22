
#ifndef GOCFAMILY_CONTROLBAR_H
#define GOCFAMILY_CONTROLBAR_H

#include "../gameobject/gocomponent.h"
#include <QWidget>

class GOCFamily_ControlBar : public GOComponent, public QWidget
{
	public:
		/** Default constructor */
		GOCFamily_ControlBar();
		/** Default destructor */
		virtual ~GOCFamily_ControlBar() = 0;

		virtual const GOC_IDType familyID() const {return GOC_IDType("ControlBarFamily");}
		/** switches the label on the play/pause button when it is pushed */
		virtual void playPause() = 0;
		/**
		 * retrieves the number of turns that were played in the game
		 * @return the number of turns that were played in the game */
		virtual int numTurns() = 0;
		/**
		 * retrieves the turn that playback is currently on
		 * @return the turn that playback is currently on */
		virtual int currentTurn() = 0;
	protected:
	private:
};

#endif // GOCFAMILY_CONTROLBAR_H
