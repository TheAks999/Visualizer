#include "managizer.h"

RETURN Managizer::createSingletons(std::string & error)
{
    create();

    //! @todo make more non-crit systems.

    RETURN retval = M_SUCCESS;

    if (!createNoncrit(Mutex::create,Mutex::destroy,error,"Mutex"))
    {
	retval = M_NONCRIT;
    }

    if (!createNoncrit(Threadler::create,Threadler::destroy,error,"Threadler"))
    {
	retval = M_NONCRIT;
    }


    if (!createCrit(OptionsMan::create,OptionsMan::destroy,error,"Options Manager"))
    {
	return M_CRITICAL;
    }

    if (!createCrit(ObjectManager::create,ObjectManager::destroy,error,"Object Manager"))
    {
	return M_CRITICAL;
    }

    if (!createCrit(GUI::create,GUI::destroy,error,"GUI"))
    {
	return M_CRITICAL;
    }

    if (!createCrit(Renderer::create,Renderer::destroy,error,"Renderer"))
    {
	return M_CRITICAL;
    }

    if (!createCrit(ResourceMan::create,ResourceMan::destroy,error,"Resource Manager"))
    {
	return M_CRITICAL;
    }

    if (!createCrit(ObjectLoader::create,ObjectLoader::destroy,error,"Object Loader"))
    {
	return M_CRITICAL;
    }

    if (!createCrit(TimeManager::create,TimeManager::destroy,error,"Time Manager"))
    {
	return M_CRITICAL;
    }


    return retval;
}

RETURN Managizer::destroySingletons(std::string & error)
{
    if (!m_base)
	return M_CRITICAL;

    RETURN retval = M_SUCCESS;
    std::map<std::string,bool(*)()>::iterator destructionIterator
	    = m_base->m_destroyers.begin();
    for (; destructionIterator != m_base->m_destroyers.end(); destructionIterator++)
    {
	if (!(*(destructionIterator->second))())
	{
	    retval = M_CRITICAL;
	    error += "Destructor for: ";
	    error += destructionIterator->first;
	    error += "wouldn't work\n";
	}
    }
    m_base->m_destroyers.clear();
    destroy();
    return retval;
}

RETURN Managizer::loadData(std::string & error)
{
    //! @todo make less things critical

    if( !OptionsMan::loadOptionFile( "./options.cfg" ) )
    {
	error += "Critical Error: Could Not Load options.cfg\n";
	    return M_CRITICAL;
    }

    // initialize global options
    if (!OptionsMan::addInt("numTurns",1))
    {
	error += "Critical Error: Add option \"numTurns\" failed\n";
	return M_CRITICAL;
    }

    if(!OptionsMan::addBool("sliderDragging", false ))
    {
	error += "Critical Error: Add option \"sliderDragging\" failed\n";
	return M_CRITICAL;
    }

    if (!OptionsMan::addInt( "currentTurn", 0 ))
    {
	error += "Critical Error: Add option \"currentTurn\" failed\n";
	return M_CRITICAL;
    }
    // done initializing

    //TimeManager::setSpeed( 1 );
    if (!TimeManager::setup())
    {
	error += "Critical Error: Could not setup the time manager\n";
	return M_CRITICAL;
    }


    if ( !ResourceMan::loadResourceFile("./textures.r") )
    {
	error += "Critical Error: Could Not Load resource.cfg\n";
	return M_CRITICAL;
    }

    if ( !GUI::setup() )
    {
	error += "Critical Error: GUI could not set up\n";
	return M_CRITICAL;
    }

    Renderer::setParent( GUI::getGUI() );

    if ( !Renderer::setupOGL() )
    {
        error += "Critical Error: Renderer could not set up Opengl\n";
	return M_CRITICAL;
    }

    if ( !Renderer::setupResize() )
    {
	error += "Critical Error: Renderer could not resize the screen\n";
	return M_CRITICAL;
    }

    if (!Renderer::isSetup())
    {
	error += "Critical Error: Renderer is not completely set up\n";
	return M_CRITICAL;
    }




    return M_SUCCESS;
}

RETURN Managizer::unloadData(std::string & error)
{
    return M_CRITICAL;
}


bool Managizer::createCrit( bool (*createFunc)(),bool (*destroyFunc)(), std::string & error, const std::string & objectName)
{
    if (!createFunc())
    {
	error += "Critical Error: Options Mangager wouldn't create\n";
	destroySingletons(error);
	return false;
    }
    m_base->m_destroyers[objectName] = destroyFunc;

    return true;
}

bool Managizer::createNoncrit( bool (*createFunc)(), bool (*destroyFunc)(), std::string & error, const std::string & objectName)
{
    if (!createFunc())
    {
	error += "Non-Critical Error: ";
	error += objectName;
	error += " wouldn't create\n";
	return false;
    }

    m_base->m_destroyers[objectName] = destroyFunc;
    return true;
}

void Managizer::create()
{
    if (!m_base)
	m_base = new Managizer;
}

void Managizer::destroy()
{
    if (m_base)
	delete m_base;

    m_base = NULL;
}

bool Managizer::isInit()
{
    return m_base;
}

Managizer * Managizer::m_base = NULL;
