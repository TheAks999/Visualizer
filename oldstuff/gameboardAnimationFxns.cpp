#include "gameboardWidget.h"
#include <stdlib.h>
#include <time.h>


/** @todo Generalize and put into renderer
void Gameboard::drawAnimations( Game * game, float falloff)
{

	int frame = getAttr( frameNumber );
	for (std::vector<Animation*>::iterator it = game->states[frame].animations.begin();
		it != game->states[frame].animations.end();
		it++)
	{
		switch ( (*it)->type)
		{
#if 0
			case ADD:
				break;
			case ATTACK:
				drawAttack(game,(Attack*)(*it),falloff);
				break;
			case BUILD:
				drawBuild(game,(Build*)(*it),falloff);
				break;
			case COLLIDE:
				drawCollide(game,(Collide*)(*it),falloff);
				break;
			case COMBINE:
				break;
			case HEAL:
				drawHeal(game,(Heal*)(*it),falloff);
				break;
#endif
			case MOVE:
				break;
#if 0
			case REMOVE:
				break;
			case SPLIT:
				break;
#endif
		}
	}
}


Piece *findExistance( GameState &state, int unit )
{
	if( state.pieces.find( unit ) != state.pieces.end() )
		return (Piece *)&state.pieces[unit];

	return 0;

}
*/
