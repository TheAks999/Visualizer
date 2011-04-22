#ifndef RESOURCEMAN_H
#define RESOURCEMAN_H

#include "../singleton.h"
#include "resource.h"
#include "../manager/manager.h"
#include <map>
#include <string>
#include <vector>

/** @todo merge this into the options manager... maybe **/


class ResourceMan : protected Manager <ResID_t,Resource*>
{
	public:
		/** Default constructor */
		ResourceMan();
		/** Default destructor */
		virtual ~ResourceMan();

    static Resource * reference(const std::string & rName, const std::string & referencer);
    static bool release(const std::string & rName, const std::string & referencer);

		template<class T, ResourceType RT>
		static bool reg(const ResID_t & rName, const T & value);
		static bool regFile(const ResID_t & rName, const std::string & filename);
		static bool del(const ResID_t & rName);

		static bool loadResourceFile(const std::string & filename);
		static bool saveResourceFile(const std::string & filename);

		static bool exists(const ResID_t & rName);

		static std::vector<std::string> listResourceNames();

		static bool destroy();
		static bool create(){return Manager <ResID_t,Resource*>::create();}
		static bool isInit(){return Manager<ResID_t,Resource*>::isInit();}

	protected:
	private:

		ResourceType findFileType(const std::string & filename);

};

#endif // RESOURCEMAN_H
