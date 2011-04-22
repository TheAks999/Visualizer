#include "gameboardWidget.h"

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

Gameboard::Gameboard( QWidget *prt )
: QGLWidget( QGLFormat(QGL::SampleBuffers),prt)
{
	/** @todo update code
	// This timer tells us when to repaint the gameboard.
	// 20 milliseconds or microseconds, I'm not sure

	// This makes it about 50 Frames Per Second
	timerId = startTimer(20);
	parent = ((VisualizerWindow*)prt);
	time.start();
	buttonTimes.start();

	hasMapGrid = getAttr( MapGrid );

	hasDefaultBG = true;
	drawFont = NULL;

	leftButtonDown =
		leftDoubleClick =
		leftButtonDrag =
		rightButtonDown =
		midButtonDown = false;
	*/
}


Gameboard::~Gameboard()
{
	if (drawFont != NULL)
	{
		delete drawFont;
	}

}


void Gameboard::initializeGL()
{
	/** @todo Move this to the renderer
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable( GL_TEXTURE_2D );

	QString errString;

	if (!loadAllTextures(errString))
	{
		QMessageBox::critical(
			this,
			"Error",
			tr("Default textures failed to load: ") + errString
			);
	}
	*/
}


void Gameboard::resizeGL( int w, int h )
{
	/** @todo Move this to the renderer

	*/
}


void Gameboard::mousePressEvent( QMouseEvent *e )
{
/** @todo update code
	if( e->button() == Qt::LeftButton )
	{
		clickX = e->x();
		clickY = e->y()-getAttr(boardOffsetY);
		if( buttonTimes.elapsed() - leftButtonTime < getAttr( doubleClickTime ) )
		{
			// Do Double click event

		}
		else
		{

			leftButtonTime = buttonTimes.elapsed();
		}

		leftButtonDown = true;
		dragX = clickX;
		dragY = clickY;

	} else if ( e->button() == Qt::RightButton )
	{
		rightButtonTime = buttonTimes.elapsed();
		rightButtonDown = true;
	} else if( e->button() == Qt::MidButton )
	{
		midButtonTime = buttonTimes.elapsed();
		midButtonDown = true;
	}
	*/
}


bool touchingBox( int selectX, int selectY, int selectWidth, int selectHeight, int x, int y, int size )
{
	if(
		selectX <= x+(size-1) &&
		selectWidth >= x &&
		selectY <=y+(size-1) &&
		selectHeight >= y )
	{
		return true;
	}
	//if( x >= selectX && x <= selectWidth && y >=selectY && y <= selectHeight )
	//	return true;
	return false;
}


template <class T>
void addSelection(std::map<int, T > & objects, std::map<int,string> & selectedIDs, const int & selectX, const int & selectY, const int & selectWidth, const int & selectHeight)
{
	/** @todo update code
	typename std::map < int, T > :: iterator it;

	for(
		it = objects.begin();
		it != objects.end();
		it++ )
	{
		stringstream ss;
		if( touchingBox( selectX, selectY, selectWidth, selectHeight, it->second.file, it->second.rank, 1 )  )
		{
			ss << it->second;
			selectedIDs[it->second.id] = ss.str() ;
		}
	}
	*/
}


void Gameboard::mouseReleaseEvent( QMouseEvent *e )
{
	/** @todo update code
	curX = e->x()+1;
	curY = e->y()+1-getAttr(boardOffsetY);
	int selectWidth, selectHeight;
	int selectX = selectWidth = curX/getAttr(unitSize);
	int selectY = selectHeight = curY/getAttr(unitSize);

	if( e->button() == Qt::LeftButton )
	{
		if( leftButtonDrag )
		{
			selectX = (curX<dragX ? curX:dragX)/getAttr(unitSize);
			selectWidth = (curX<dragX ? dragX:curX)/getAttr(unitSize);
			selectY = (curY<dragY ? curY:dragY)/getAttr(unitSize);
			selectHeight = (curY<dragY ? dragY:curY)/getAttr(unitSize);
		}

		if( leftDoubleClick )
		{
			leftDoubleClick = false;
			return;
		}

		Game *game = parent->gamelog;
		int frame = getAttr( frameNumber );
		if( game )
		{
			if( !(QApplication::keyboardModifiers() & Qt::ShiftModifier) )
				selectedIDs.clear();

			addSelection(game->states[frame].pieces, selectedIDs, selectX, selectY, selectWidth, selectHeight);
			std::map<int,Piece> tBots;
			for( std::map<int,Piece>::iterator i = game->states[frame].pieces.begin(); i != game->states[frame].pieces.end(); i++ )
			{
				tBots[i->second.id] = i->second;
			}

			addSelection(tBots, selectedIDs, selectX, selectY, selectWidth, selectHeight);

			stringstream ss;
			ss << "Selected Units: " << selectedIDs.size() << ", X: " << selectX << ", Y: " << selectY << '\n';

			for (map<int,string>::iterator it = selectedIDs.begin(); it != selectedIDs.end(); it++)
			{
				ss << it->second << '\n';
			}

			//parent->console->setText( ss.str().c_str() );
		}

		leftButtonDown = false;
		leftButtonDrag = false;
	} else if ( e->button() == Qt::RightButton )
	{
		rightButtonDown = false;
	} else if( e->button() == Qt::MidButton )
	{
		rightButtonDown = false;
	}

	// Invalidate last frame so we get the latest talkers.
	setAttr( lastFrame, -1 );
	*/
}


void Gameboard::mouseMoveEvent( QMouseEvent *e )
{
	/** @todo update code
	// If manhatten distance is 6 or greater, we're draggin
	if( e->buttons() & Qt::LeftButton && abs(curX-dragX)+abs(curY-dragY) > 6 )
		leftButtonDrag = true;

	curX = e->x();
	curY = e->y()-getAttr(boardOffsetY);
	*/

}


void Gameboard::talkRobotsGodDamnitTalk( Game *game )
{
	/** @todo update code
#if 0
	stringstream ss;
	int startFrame = getAttr( frameNumber )-1;
	if( getAttr( persistantTalking ) )
		startFrame = 0;
	if( startFrame < 0 )
		startFrame = 0;
	for( int i = startFrame; i <= getAttr(frameNumber); i++ )
	{
		for(
			std::vector<Animation*>::iterator j = game->states[i].animations.begin();
			j != game->states[i].animations.end();
			j++ )
		{

			// Not talking, continue
			if( (*j)->type != TALK )
				continue;

			Talk *t = (Talk*)*j;

			// If not selected, continue
			if( selectedIDs.find( t->speaker ) == selectedIDs.end() )
				continue;

			// Ok, selected and talking... whew
			// Let's see if the unit is in this frame:
			if( game->states[i].bots.find( t->speaker ) == game->states[i].bots.end() )
				continue;

			// Yes, he's in the frame!!!
			// GETTING CLOSER!!
			// Correct team!?!?!?!?!
			if( (game->states[i].bots[t->speaker].owner+1)&(getAttr(team1Talk)|((getAttr(team2Talk))<<1) ) )
			{
				// CORRECT TEAM!!!!
				ss << t->message << endl;
			}

		}
	}

	parent->console->setText( ss.str().c_str() );
#endif
*/
}


void Gameboard::paintGL()
{
	/** @todo Move this to renderer
	// We only want to update output if our frame has changed.
	// Other wise we're wasting our time.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable( GL_TEXTURE_2D );

	Game *game = parent->gamelog;
	int frame = getAttr( frameNumber );

	if( game )
	{
#if 0
		if( time.elapsed() < getAttr(initTime) && getAttr(showInitScreen) )
		{
			drawIntroScreen( game, time.elapsed() );


		}	else
#endif

		if( time.elapsed() > getAttr(playSpeed) && !getAttr(dragging)
			&& getAttr(currentMode) != paused &&
			(!getAttr(arenaMode) || (getAttr(frameNumber) > 0) || time.elapsed() > getAttr(initTime))
			)
		{
			setAttr(showInitScreen, false );
			time.restart();

			// This is where we advance to the next frame
			if( frame < (int)game->states.size()-1 && frame >= 0 )
			{
				if(getAttr(currentMode) == rewinding &&
					frame>0)
				{
					setAttr( frameNumber, --frame );
					if( frame <=0 )
						setAttr( currentMode, paused );
				}
				else
					setAttr( frameNumber, ++frame );
			}

			if( (unsigned)frame == game->states.size()-1 )
				setAttr( currentMode, paused );

			parent->controlSlider->blockSignals(true);
			parent->controlSlider->setSliderPosition( frame );
			parent->controlSlider->blockSignals(false);
		}

		float falloff;

		// falloff assignment while rewinding
		if(getAttr(currentMode) == rewinding)
			falloff = 1-((float)time.elapsed()/getAttr(playSpeed));

		// This allows the visualizer to finish the animation it is
		// currently on and then stop while paused/dragging the slider
		else if(getAttr(currentMode) == paused||getAttr(dragging))
		{
			if((float)time.elapsed()/getAttr(playSpeed) <1)
				falloff =
					(float)time.elapsed()/getAttr(playSpeed);
			else
				// This needs to be 0, other wise, when paused, player sees future
				falloff = 0;
		}

		// The normal falloff assignment, when game is moving forwards
		else
			falloff = (float)time.elapsed()/getAttr(playSpeed);

		if( 1 )
		{

			glLoadIdentity();
			glPushMatrix();

			glColor3f( 1, 1, 1 );

			drawBackground();
			drawBots( game, falloff );
			drawAnimations( game, falloff );
			drawProgressbar( game );

			glPopMatrix();
		}

		if( getAttr(frameNumber) != getAttr(lastFrame) )
		{
			setAttr( lastFrame, getAttr( frameNumber ) );
			talkRobotsGodDamnitTalk(game);

			stringstream text;
			text << getAttr(frameNumber)+1 << "/" << game->states.size();

			parent->turnLabel->setText( text.str().c_str() );

			switch( getAttr( currentMode ) )
			{
				case stop:
				case paused:
					parent->playButton->setText( "Play" );
					break;
				case rewinding:
				case fastForward:
				case play:
				default:
					parent->playButton->setText( "Pause" );
					break;
			}
		}
		//parent->console

		if(  frame == (int)game->states.size()-1 )
		{
			if( time.elapsed() > getAttr(winnerScreenTime) )
			{
				if( getAttr(arenaMode) )
					QApplication::quit();
			}
			else
			{
				if( time.elapsed() > getAttr(winnerScreenTime)*.3 )
					drawWinnerScreen( game, time.elapsed() );
			}

		}
	}

	drawMouse();
	*/
}


void Gameboard::timerEvent( QTimerEvent *)
{
	update();
}


void Gameboard::toggleMapGrid()
{
	hasMapGrid = !hasMapGrid;
}


bool Gameboard::loadBackground( QString filename )
{
	/** @todo update code
	if ( textures[T_BG].loadImage( filename ) )
	{
		hasDefaultBG = false;
		return true;
	}

	return false;
	*/
}


void Gameboard::clearBackground()
{
	hasDefaultBG = true;
}
