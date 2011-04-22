#include "scoreboard.h"
#include "../lib/renderer/renderer.h"
#include "../lib/resourcemanager/texture.h"
#include "dupObj.h"
#include <sstream>
#include <iostream>

void Scoreboard::loadFont( int fontTex, string fontWidthsFile )
{
  if( !fnt.loadNewFont( fontTex, fontWidthsFile ) )
  {
    cout << "FAILED TO LOAD" << endl;
  }
}

void Scoreboard::update()
{

}

void Scoreboard::parseScores( Game& g )
{
  player[0] = g.states[0].players[0];
  player[1] = g.states[0].players[1];
  winner = g.winner;
  winReason = g.winReason;

  for(unsigned  int i = 0; i < g.states.size(); i++ )
  {
    Score s;
    s.p0gold = g.states[i].players[0].gold;
    s.p1gold = g.states[i].players[1].gold;
    s.p0time = g.states[i].players[0].time;
    s.p1time = g.states[i].players[1].time;
    scores.push_back( s );
  } 
}

void Scoreboard::renderAt( const unsigned int& turn, const unsigned int& frame )
{

  fnt.setAlignment( 0 );
  fnt.setBold( true );
  glEnable( GL_TEXTURE );
  glEnable( GL_TEXTURE_2D );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glEnable( GL_BLEND );

  glPushMatrix();
  glTranslatef( Renderer::height(), 0, 0 );
  glScalef( .75, .75, 0 );
  fnt.drawString( player[0].playerName );
  glTranslatef( 0, 32, 0 );

  stringstream ss;
  ss << "Gold: " << scores[turn].p0gold;
  fnt.drawString( ss.str() );

  glTranslatef( 0, 32, 0 );
  fnt.drawString( player[1].playerName );

  ss.str( "" );
  ss << "Gold: " << scores[turn].p0gold;
  glTranslatef( 0, 32, 0 );
  fnt.drawString( ss.str() );

  glPopMatrix();

}
