#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include "../lib/components/gocfamily_render.h"
#include "../lib/parser/structures.h"
#include "../lib/renderer/textRenderer/drawGLFont.h"
#include <list>
#include <iostream>
using namespace std;

struct Score
{
  int p0gold;
  int p1gold;
  int p0time;
  int p1time;

};

class Scoreboard : public GOCFamily_Render
{
  public:
    const GOC_IDType componentID() const { return GOC_IDType( "ScoreboardRender" ); }

    void loadFont( int fontTex, string fontWidthsFile );

    void update();
    void renderAt( const unsigned int& turn, const unsigned int& frame );

    void parseScores( Game& g );

    vector<Score> scores;

    Player player[2];
    int winner;
    string winReason;

  private:
    DrawGLFont fnt;

};
#endif
