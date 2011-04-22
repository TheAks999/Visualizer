#ifndef PIRATEMAP_H
#define PIRATEMAP_H

#include "../lib/components/gocfamily_render.h"
#include "../lib/parser/parser.h"
#include "../lib/resourcemanager/texture.h"
#include <string>
#include <fstream>

class PirateMap : public GOCFamily_Render
{
  public:
    PirateMap();
    ~PirateMap();

    virtual const GOC_IDType componentID() const;

    void generateMap( Game& g );

    static void drawTGA( std::string filename );

    enum Orientation
    {
      horizontal,
      vertical
    };

    enum TileType
    {
      water,
      land
    };

    float interp(
      float x,
      float x0,
      float x1,
      float y0,
      float y1  );

    QRgb interpolate(
      int x,
      int y,
      int size,
      QImage *images,
      int *depths,
      int depth );

    int distToTile(
      const int& x,
      const int& y,
      const int& mapsize,
      const TileType& type,
      const std::map<int, Tile>& tiles
      );

    void boxBlur(
      int **map,
      const int& width,
      const int& height,
      const int& radius );

    void blur(
      int **map,
      const int& width,
      const int& height,
      const int& radius,
      const float* gaussian,
      Orientation orient );

    int m_width;
    int m_power;

    ResTexture mapTexture;

    void update();
    virtual void renderAt(
      const unsigned int& turn,
      const unsigned int& frame
      );

  private:
};
#endif
