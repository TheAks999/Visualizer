#include "objectloader.h"
#include "../../piracy/piratemap.h"
#include "../../piracy/renderdata.h"
#include "../../piracy/piracylocations.h"
#include "../../piracy/objecttype.h"
#include "../../piracy/piratehealth.h"
#include "../../piracy/shiphealth.h"
#include "../../piracy/scoreboard.h"
#include "../components/goc_owner.h"
#include "../../piracy/gold.h"
#include "../renderer/renderer.h"
#include "../../piracy/dupObj.h"
#include "../selectionrender/selectionrender.h"
#include "../gui/controlbar.h"

typedef int idtype;

bool ObjectLoader::loadGamelog(const std::string & filename)
{
    //! @todo PUT THE LOADING LOGIC HERE!!
    Game game;


    if( !parseFile( game, filename.c_str() ) )
    {
      throw "Cannot Load Gamelog";
    }


    GameObject *go = new GameObject( 1 );
    PirateMap *pm = new PirateMap();
    pm->generateMap( game );
    pm->setOwner( go );
    go->setGOC( pm );
    //! @todo make the added stuff a render object
    //Renderer::registerConstantObj( 1, go->getGOC("") );

    go = new GameObject( 2 );
    go->setGOC( SelectionRender::get() );
    SelectionRender::get()->setOwner( go );
    //! @todo make the added stuff a render object
    //Renderer::registerConstantObj( 2, go );

    go = new GameObject( 3 );
    Scoreboard *sb = new Scoreboard();
    ResTexture res;
    res.load( "./piracy/textures/font1.png" );
    sb->loadFont( res.getTexture(), "./piracy/textures/font1.dat"  );
    sb->parseScores( game );

    sb->setOwner( go );
    go->setGOC( sb );
    //! @todo make the added stuff a render object
    //Renderer::registerConstantObj( 3, go );

    unsigned int numTurns = game.states.size();
    unsigned int numFrames = OptionsMan::getInt("numFrames");

    ObjectManager::setSize(numTurns,numFrames);

    TimeManager::setTurn(0);
    TimeManager::setNumTurns( numTurns );
    std::map<idtype, LookupSet<GameObject*,idtype> > looksets;

    unsigned int id;
    for (unsigned int turn = 0; turn < game.states.size(); turn++)
    {

      for( 
          std::map<int,Pirate>::iterator i = game.states[turn].pirates.begin();
          i != game.states[turn].pirates.end(); 
          i++ )
      {
  	     id = i->second.id;
         if( looksets.find( id ) == looksets.end() )
         {
           looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
         }

  	    GameObject * pirate = new GameObject(id);

  	    //setup stuff
        // PirateData * data = new PirateData();
  	    PiracyLocation * loc = new PiracyLocation();
  	    GOC_Owner * owner = new GOC_Owner(pirate, i->second.owner);
  	    Gold * gold = new Gold(pirate,i->second.gold);
  	    ObjectType * type = new ObjectType(pirate,POT_PIRATE);
        PirateHealth * health = new PirateHealth(pirate,i->second.health,OptionsMan::getInt("pirateMaxHealth"));

  	    loc->parseLocation(&(i->second));

  	    loc->setOwner(pirate);

  	    pirate->setGOC(loc);
  	    pirate->setGOC(owner);
  	    pirate->setGOC(gold);
  	    pirate->setGOC(type);
        pirate->setGOC(health);

  	    //end setup

	    if (!looksets[id].addNode(pirate,turn,0))
	    {
		std::cout << "Pirate node adding fail\n";
	    }
      }

      for( 
          std::map<int,Ship>::iterator i = game.states[turn].ships.begin();
          i != game.states[turn].ships.end();
          i++ )
      {

  	    id = i->second.id;
  	    if (looksets.find(id) == looksets.end())
  	    {
          looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
  	    }

  	    GameObject* ship = new GameObject(id);
  	    //setup stuff

	    //ShipData * data = new ShipData();
  	    PiracyLocation* loc = new PiracyLocation();
  	    GOC_Owner* owner = new GOC_Owner(ship, i->second.owner);
  	    Gold* gold = new Gold(ship,i->second.gold);
  	    ObjectType* type = new ObjectType(ship,POT_SHIP);
	    ShipHealth* health = new ShipHealth(ship,i->second.health,OptionsMan::getInt("shipMaxHealth"));
  	    //ShipRender * render = new ShipRender();

  	    //render->setOwner(ship);
  //	    data->parseShip(game,id,turn);
  	    loc->parseLocation(&(i->second));


  	    loc->setOwner(ship);
  //	    data->setOwner(ship);

  //	    ship->setGOC(data);
  	    ship->setGOC(loc);
  	    ship->setGOC(owner);
  	    ship->setGOC(gold);
  	    ship->setGOC(type);
        ship->setGOC(health);

  	    //end setup
	    if (!looksets[id].addNode(ship,turn,0))
	    {
		std::cout << "Ship node adding fail\n";
	    }
      }

      for( 
          std::map<int, Treasure>::iterator i = game.states[turn].treasures.begin();
          i != game.states[turn].treasures.end();
          i++ )
      {
  	    id = i->second.id;
  	    if (looksets.find(id) == looksets.end())
  	    {
          looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
  	    }

  	    GameObject * treasure = new GameObject(id);
  	    //setup stuff

	    //TreasureData * data = new TreasureData();
  	    PiracyLocation * loc = new PiracyLocation();
  	    Gold * gold = new Gold(treasure,i->second.gold);
  	    ObjectType * type = new ObjectType(treasure,POT_TREAS);

  //	    data->parseTreasure(game,id,turn);
  	    loc->parseLocation(&(i->second));


  //	    data->setOwner(treasure);
  	    loc->setOwner(treasure);

  //	    treasure->setGOC(data);
  	    treasure->setGOC(loc);
  	    treasure->setGOC(gold);
  	    treasure->setGOC(type);

  	    //end setup

	    if(!looksets[id].addNode(treasure,turn,0))
	    {
		std::cout << "Treasure node adding fail\n";
	    }

      }

      for( 
          std::map<int, Port>::iterator i = game.states[turn].ports.begin();
          i != game.states[turn].ports.end();
          i++ )
      {
  	    id = i->second.id;
  	    if (looksets.find(id) == looksets.end())
  	    {
  		    looksets.insert( std::pair<idtype,LookupSet<GameObject*,idtype> >(id,LookupSet<GameObject*,idtype>(numTurns,numFrames,id) ));
  	    }

  	    GameObject * port = new GameObject(id);
  	    //setup stuff

	    //PortData * data = new PortData();
  	    PiracyLocation * loc = new PiracyLocation();
  	    GOC_Owner * owner = new GOC_Owner(port, i->second.owner);
  	    ObjectType * type = new ObjectType(port,POT_PORT);


  //	    data->parsePort(game,id,turn);
  	    loc->parseLocation(&(i->second));

  //	    data->setOwner(port);
  	    loc->setOwner(port);

	//    port->setGOC(data);
  	    port->setGOC(loc);
  	    port->setGOC(owner);
  	    port->setGOC(type);
  	    //port->setGOC(render);
  	    //end setup

	    if (!looksets[id].addNode(port,turn,0))
	    {
		std::cout << "Port node adding fail\n";
	    }
      }

  }

     std::map<idtype,LookupSet<GameObject*,idtype> > :: iterator it = looksets.begin();
    for (; it != looksets.end(); it++)
    {
	//
	//std::cout << "add ships & shit\n";
    	if (!ObjectManager::reg(it->first,it->second))
	    std::cout << "Object load error: id " << it->first << '\n';
    }

    return true;
}

