#ifndef RESOURCE_H
#define RESOURCE_H
#include <set>
#include <string>
#include "typedefs.h"

#ifdef DEBUG
#include <iostream>
#endif



class Resource
{
	public:
		/** Default constructor */
		Resource(ResourceType type)
		{
			m_type = type;
		}

		/** Default destructor */
		virtual ~Resource(){}

		virtual bool load(const std::string & filename) = 0;
		virtual bool unload()
		{
			return true;
		}

		ResourceType type()
		{
			return m_type;
		}

        inline bool isReferencedBy(const std::string & referencer)
        {
            if (m_references.find(referencer) != m_references.end())
            {
                return true;
            }
            return false;
        }

        inline std::set<std::string> referenceList()
        {
            return m_references;
        }

        inline unsigned int numReferences()
        {
            return m_references.size();
        }

        #ifdef DEBUG
		void printReferences()
		{
		    std::cout << "References:\n"
		    for (std::set<std::string>::iterator it = m_references.begin();
                    it != m_references.end(); it++)
            {
                std::cout << *it << '\n';
            }
		}
		#endif

        inline bool reference(const std::string & referencer)
        {
            if (!isReferencedBy(referencer))
            {
                m_references.insert(referencer);
                return true;
            }

            #ifdef DEBUG
            std::cout << "Referencer: \"" << reference << "\" already exists\n";
            #endif
            return false;
        }

        inline bool deReference(const std::string & referencer)
        {
            if (isReferencedBy(referencer))
            {
                m_references.erase(referencer);
                return true;
            }

            #ifdef DEBUG
            std::cout << "Referencer: \"" << reference << "\" doesn't exist\n";
            #endif
            return false;
        }


	protected:
	ResourceType m_type;
	std::set<std::string> m_references;
	std::string filename;
	private:
};



#endif // RESOURCE_H
