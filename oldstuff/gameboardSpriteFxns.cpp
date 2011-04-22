#include "gameboardWidget.h"


/** @todo: generalize and put inot renderer
void Gameboard::drawSprite( int x, int y, int w, int h, int texture, bool selected = false, int owner = 2)
{

	glBindTexture( GL_TEXTURE_2D, textures[texture].getTexture() );
	glPushMatrix();
	glTranslatef( x, y, 0 );
	glScalef( w, h, 0 );
	glColor4f(1.0,1.0,1.0,1.0f);
	glBegin(GL_QUADS);

	glTexCoord2f( 0, 0 );
	glVertex3f(0, 1.0f, 0);
	glTexCoord2f( 1, 0 );
	glVertex3f( 1.0f, 1.0f, 0);
	glTexCoord2f( 1, 1 );
	glVertex3f( 1.0f,0, 0);
	glTexCoord2f( 0, 1 );
	glVertex3f(0,0,0);

	glEnd();

	glDisable( GL_TEXTURE_2D );

	if (selected)
	{
		switch (owner)
		{
			case 0:										 //player 1
				glColor4f(5.0f,0.0f,0.0f,1.0f);
				break;
			case 1:										 //player 2
				glColor4f(0.0f,0.0f,5.0f,1.0f);
				break;
			default:
				glColor4f(0.2f,0.2f,0.2f,1.0f);

		}

		glLineWidth(3.0f);

		glBegin (GL_LINE_LOOP);

		glVertex3f(0, 1.0f, 1);
		glVertex3f( 1.0f, 1.0f, 1);
		glVertex3f( 1.0f,0, 1);
		glVertex3f(0,0, 1);

		glEnd();
		glLineWidth(1.0f);
	}

	glPopMatrix();

	glEnable( GL_TEXTURE_2D );

}


void Gameboard::drawSingleBot(Game * game, Piece* bot, int frame, int unitSize, float falloff, bool dead)
{

	int x0, y0, x1, y1;
	x0 = x1 = (bot->file-1)*unitSize;
	y0 = y1 = (bot->rank-1)*unitSize;
	if((unsigned)frame+1 < game->states.size() )
	{
		if( game->states[frame+1].pieces.find(bot->id) != game->states[frame+1].pieces.end() )
		{
			x1 = (game->states[frame+1].pieces[bot->id].file-1)*unitSize;
			y1 = (game->states[frame+1].pieces[bot->id].rank-1)*unitSize;
		}
	}

	//is it selected?
	bool selected = false;
	if ( selectedIDs.find( bot->id ) != selectedIDs.end() )
	{
		selected = true;
	}

	// find owner
	int owner = bot->owner;

	//set bot to appropriate type
	int sprite;

	if( dead )
	{
		sprite = T_EXPLODE;

	} else
	{
		switch (bot->type)
		{
			case 'P':										 // Pawn
				sprite = T_WHITE_PAWN;
				break;

			case 'R':										 // Rook
				sprite = T_WHITE_ROOK;
				break;

			case 'B':										 // Bishop
				sprite = T_WHITE_BISHOP;
				break;

			case 'N':										 // Knight
				sprite = T_WHITE_KNIGHT;
				break;

			case 'Q':										 // Queen
				sprite = T_WHITE_QUEEN;
				break;

			case 'K':										 // King
				sprite = T_WHITE_KING;
				break;
		}


		sprite = sprite + T_BLACK_PAWN*bot->owner;

	}


	drawSprite( (int)(x0+(x1-x0)*falloff),(int)(y0+(y1-y0)*falloff),unitSize,unitSize, sprite, selected, owner );

}





void Gameboard::drawBots( Game *game, float falloff )
{

	int frame = getAttr(frameNumber);
	int unitSize = getAttr( unitSize );

	for(
		std::map<int,Piece>::iterator it = game->states[frame].pieces.begin();
		it != game->states[frame].pieces.end();
		it++
		)
	{
		bool dead = false;
		if( (unsigned int)frame < (unsigned int)game->states.size()-1 )
		{

			if( !findExistance( game->states[frame+1], it->second.id ) )
				dead = true;

			drawSingleBot( game,&(it->second), frame, unitSize, falloff, dead );
		}

	}
}

*/
