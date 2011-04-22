#ifndef GAMEBOARDWIDGET_H
#define GAMEBOARDWIDGET_H

#include <QtGui>
#include <QtOpenGL>
#include <QTime>
#include <QTimer>
#include <list>
#include "texture.h"
#include "../lib/parser/parser.h"
#include "visualizerWindow.h"
#include "drawGLFont.h"

using namespace std;

class VisualizerWindow;

enum eTextures
{
	T_WHITE_PAWN = 0,
	T_WHITE_ROOK,
	T_WHITE_BISHOP,
	T_WHITE_KNIGHT,
	T_WHITE_QUEEN,
	T_WHITE_KING,

	T_BLACK_PAWN,
	T_BLACK_ROOK,
	T_BLACK_BISHOP,
	T_BLACK_KNIGHT,
	T_BLACK_QUEEN,
	T_BLACK_KING,

	T_BG,
	T_DEFAULTBG,
	T_GRID,
	T_FONT,

	T_EXPLODE,

	numTextures

};

Piece *findExistance( GameState &state, int unit );

class Gameboard : public QGLWidget
{
	Q_OBJECT
		friend class VisualizerWindow;

	public:
		Gameboard( QWidget *parent );
		~Gameboard();

		void toggleMapGrid();

		bool loadBackground( QString filename );
		void clearBackground();

	private slots:

	protected:
		void initializeGL();
		void resizeGL( int width, int height );
		void paintGL();
		void timerEvent( QTimerEvent * );
		void drawBackground( );
//		void drawScoreboard( Game *game );
		void drawMouse();
		void drawProgressbar( Game * game);
		void drawWinnerScreen( Game *game, int elapsed );
		void drawIntroScreen( Game *game, int elapsed );

		void drawBots( Game* game, float falloff );
		void drawSingleBot( Game *game, Piece* bot, int frame, int unitSize, float falloff, bool dead = false );

		void drawAnimations( Game * game, float falloff);


		void talkRobotsGodDamnitTalk(Game *game);

		bool loadAllTextures( QString & message );
		bool loadTexture(QString filename, eTextures texID, QString & errString);

		void drawControl();

		void drawHealth( int x, int y, int h, int w, int maxHealth, int health, int owner );
		void drawSprite( int x, int y, int h, int w, int texture, bool selected, int owner );

		map<int,string> selectedIDs;

		texture textures[numTextures];

		VisualizerWindow *parent;

		QTime time;
		QTime buttonTimes;

		bool hasMapGrid;
		bool hasDefaultBG;					 //default background

		void mousePressEvent( QMouseEvent *event );
		void mouseReleaseEvent( QMouseEvent *event );
		void mouseMoveEvent( QMouseEvent *event );

		DrawGLFont *drawFont;

		bool leftButtonDown;
		bool leftDoubleClick;
		bool leftButtonDrag;

		bool rightButtonDown;
		bool midButtonDown;

		int curX;
		int curY;

		int clickX;
		int clickY;

		int dragX;
		int dragY;

		int leftButtonTime;
		int rightButtonTime;
		int midButtonTime;

		int timerId;

};
#endif
