#ifndef MANAGIZER_H
#define MANAGIZER_H
#include <string>
#include "lib/gui/gui.h"
#include "lib/mutex/Mutex.h"
#include "lib/objectmanager/objectloader.h"
#include "lib/objectmanager/objectmanager.h"
#include "lib/renderer/renderer.h"
#include "lib/resourcemanager/resourceman.h"
#include "lib/selectionrender/selectionrender.h"
#include "lib/threadler/threadler.h"
#include "lib/timemanager/timeManager.h"
#include "piracy/dupObj.h"

enum RETURN
{
    M_SUCCESS,
    M_NONCRIT,
    M_CRITICAL
};

class Managizer
{
public:
    static RETURN createSingletons(std::string & error);
    static RETURN destroySingletons(std::string & error);
    static RETURN loadData(std::string & error);
    static RETURN unloadData(std::string & error);

private:
    static Managizer * m_base;
    std::map<std::string,bool(*)()> m_destroyers;

    static inline bool createCrit( bool (*createFunc)(), bool (*destroyFunc)(), std::string & error, const std::string & objectName);
    static inline bool createNoncrit( bool (*createFunc)(), bool (*destroyFunc)(), std::string & error, const std::string & objectName);

    static inline void create();
    static inline void destroy();
    static inline bool isInit();

};

#endif // MANAGIZER_H
