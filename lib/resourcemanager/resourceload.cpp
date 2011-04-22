// if this were for windows only I would make this file a DLL
//but it isn't, so I'm forced to make this just a seperate .cpp
//for ease of editing
// 	~Alex Shepard
//	aksfkb@mst.edu

#include "resourceman.h"
#include "texture.h"
#include "typedefs.h"
#include <QString>
#include <iostream>
#include <fstream>
#include <sstream>

ResourceType getResTypeFromStr(const std::string & typeBuff)
{
	if ("texture" == typeBuff)
		return RT_TEXTURE;

	return RT_NONE;
}


/** @brief loadResourceFile
  * load a resource file
  * @param filename the name of the file to load from
  * @return true on success
  */
bool ResourceMan::loadResourceFile(const std::string & filename)
{
	if (!isInit())
	{
		return false;
	}


	/* if we allow multiple loading we can combine files easily
	if (get()->m_options.size())
	{
		//obviously this is the second time you are loading the damn thing
		return false;
	}*/

	std::ifstream input(filename.c_str());

	if (input.eof())
	{
		return false;
	}

	std::string buffer;
	unsigned int lineNum = 1;
	while (!input.eof())
	{
		std::stringstream ss;

		getline(input,buffer);

		if (buffer.size())
		{
        //2 different line carriages because windows is strange
		if (buffer.c_str()[0] != '#' && buffer.c_str()[0] != '\n' && buffer.c_str()[0] != (char)13)
		{
			ss << buffer;
			std::string typebuff;
			std::string namebuff;

			ss >> typebuff;
			ResourceType rt = getResTypeFromStr(typebuff);


			if (ss >> namebuff)
			{
				if (!exists(namebuff))
				{
					std::string pathBuff;
					ss >> pathBuff;
					Resource * res = NULL;


					switch (rt)
					{
						case RT_TEXTURE:
						res = (Resource*)(new ResTexture());

						if (res->load(pathBuff.c_str()))
						{
							ManagerType::reg(namebuff,(Resource*)res);
						}
						else
						{
							delete res;
							std::cout << "Resource Load Error Line " << lineNum << ": Texture \"" << namebuff << "\" at path \"" << pathBuff << "\" didn't load right.\n";
						}

						break;

						default:
						std::cout << "Resource Load Error Line "<< lineNum << ": \"" << typebuff << "\" is not a type\n";
					}
				}
				else
				{
					std::cout << "Resource Load Error Line "<< lineNum << ": Resource name \"" << namebuff << "\" already exists\n";
				}
			}
			else
			{
				std::cout << "Resource Load Error Line "<< lineNum << ": Name buffer read error\n";
			}
		}
		}

		lineNum++;
	}

	input.close();
	return true;

}


/** @brief reg
  * register a value from a file
  * @param rName the id to register the resource with
  * @param filename the value exists at (ex: mypic.png)
  * @return true if the file load was successful and the id didnt exist
  */
bool ResourceMan::regFile(const ResID_t& rName, const std::string& /*filename*/)
{
    if (!exists(rName))
    {
        //load File


        return true;
    }

	#ifdef DEBUG
    std::cout << "Resource name conflict. Name: \"" << rName << "\" already exists\n";
    #endif
    return false;
}


/** @brief saveResourceFile
  * save the resources to a file
  * @param filename the name of the file to save to
  * @return true if it is successful
  */
bool ResourceMan::saveResourceFile(const std::string& /*filename*/)
{

	return false;
}
