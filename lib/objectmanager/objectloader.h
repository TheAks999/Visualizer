#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H
#include "../singleton.h"
#include "objectmanager.h"
#include "../timemanager/timeManager.h"
#include "../optionsmanager/optionsman.h"
#include "../parser/parser.h"
#include <string>

class ObjectLoader : public Singleton<ObjectLoader>
{
public:
    //! @todo load definitions file for translation
    // bool loadDefs(const std::string & filename);

    static bool loadGamelog(const std::string & filename);

private:
    //! @todo make this object-v
    //LoadLogic m_logic;
};

#endif // OBJECTLOADER_H
