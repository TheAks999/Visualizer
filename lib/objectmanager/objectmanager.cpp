#include "objectmanager.h"

bool ObjectManager::reg(const ObjIdType & id, GameObject * obj, const unsigned int & turn, const unsigned int & frame)
{
    GameObject * temp = obj;

    //! @todo FILL IN
    return false;
}

bool ObjectManager::del(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame)
{
   // if ()

    //! @todo FILL IN
    return true;
}


LookupNode<GameObject *,ObjIdType> * ObjectManager::get(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame )
{
    if (!Singleton<ObjectManager>::isInit())
	return NULL;


    if (turn >= turns() || frame >= frames())
	return NULL;

    return Single::get()->m_objects.node(id,turn,frame);
}

bool ObjectManager::exists(const ObjIdType & id, const unsigned int & turn, const unsigned int & frame)
{
    return (Single::get()->m_objects.node(id, turn, frame) != NULL);
}

bool ObjectManager::reg(const ObjIdType & id, LookupSet<GameObject*,ObjIdType> & objset)
{
    if (!Singleton<ObjectManager>::isInit())
	return false;
    //! @todo check for shit existing, throw hissy fit if it does
   // std::cout << "Objset Size: " << objset.turns() << " , " << objset.frames() << '\n';
    Singleton<ObjectManager>::get()->m_objects.add(objset);
    return true;
}

bool ObjectManager::destroy()
{
    if (!Single::isInit())
	return false;

   //! @todo CLEAN UP PROPERLY, 'CAUSE THIS SUCKS


    return Single::destroy();
}
