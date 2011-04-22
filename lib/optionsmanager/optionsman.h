#ifndef OPTIONSMAN_H
#define OPTIONSMAN_H

#include "option.h"
#include "../singleton.h"
#include "../mutex/Mutex.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

typedef std::string OptID_t;

class OptionsMan : public Singleton <OptionsMan>
{
	public:

		static bool loadOptionFile(const std::string & filename);
		static bool saveOptionFile(const std::string & filename);

		OptionBase * operator()(const OptID_t & oName);

		static bool exists(const OptID_t & oName);

		static int getInt(const OptID_t & oName);
		static void setInt(const OptID_t & oName,const int & val);

		static float getFloat(const OptID_t & oName);
		static void setFloat(const OptID_t & oName,const float & val);

		static bool getBool(const OptID_t & oName);
		static void setBool(const OptID_t & oName,const bool & val);

		static std::string getStr(const OptID_t & oName);
		static void setStr(const OptID_t & oName,const std::string & val);

		static OptionType optionType(const OptID_t & oName);

		static bool destroy();

		//general adding functions
		static bool addString(const OptID_t & oName, const std::string & val);
		static bool addInt(const OptID_t & oName, const int & val);
		static bool addFloat(const OptID_t & oName, const float & val);
		static bool addBool(const OptID_t & oName, const bool & val);


	protected:
	private:
		template<class T, OptionType OT>
		static T getVar(const OptID_t & oName);

		template<class T, OptionType OT>
		static void setVar(const OptID_t & oName, const T & val);



		static bool strToBool(const std::string & val);

		static OptionType getTypeFromStr(const std::string & val);

		//helper fxns
		static bool addString(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);
		static bool addInt(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);
		static bool addFloat(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);
		static bool addBool(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);

		std::map<OptID_t, OptionBase* > m_options; //!< Member variable "m_options"
};

#endif // OPTIONSMAN_H
