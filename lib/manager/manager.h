#ifndef MANAGER_H
#define MANAGER_H

#include "../singleton.h"
#include <map>




/**
  * This is the class where most manager functionality should
  * be derrived from (A manager is a souped up map class, with special singleton powers)
  */
template < typename IdType, typename DataType >
class Manager : public Singleton < Manager<IdType,DataType> >
{
	public:

		typedef std::map<IdType,DataType> DataTable;
		static bool reg(const IdType & id, const DataType & data);
		static bool del(const IdType & id);
		static bool delPointer(const IdType & id);

		static bool exists(const IdType & id);
		static void clear();
		static void clearPointers();
		static unsigned int size();

		static DataType * getItem(const IdType & id);
		static bool setItem(const IdType & id);

		DataTable * data() { return &m_data; }

	protected:
		DataTable m_data;
		//typedef Singleton < ManagerBase<IdType,DataType> > ManagerSingleton;
		//typedef ManagerBase<IdType,DataType> BaseType;
		typedef Manager<IdType,DataType> ManagerType;
		//typedef std::map<IdType,DataType> DataTable;
	private:
};

#include "manager.hpp"

#endif // MANAGER_H
