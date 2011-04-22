#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include <vector>
#include <map>
#include <cstdlib>

//! @todo move shit to .hpp
template <typename T, typename idtype>
struct LookupNode
{

	LookupNode()
	{
		prev = NULL;
		next = NULL;
	}

	LookupNode(const T & t)
	{
		prev = NULL;
		next = NULL;
		data = t;
	}

	LookupNode(const T & t,LookupNode<T,idtype> * p, LookupNode<T,idtype> * n)
	{
		prev = p;
		next = n;
		data = t;
	}

	LookupNode<T,idtype> *prev, *next;
	T data;

};

template <typename T, typename idtype>
 class LookupTable;

template <typename T, typename idtype>
class LookupSet
{
public:
    LookupSet(const unsigned int & turns, const unsigned int & frames, const idtype & id)
    {
	m_set.resize(frames*turns);
	m_frames = frames;
	m_turns = turns;

	for (unsigned int i = 0; m_set.size() > i; i++)
	{
	    m_set[i] = NULL;
	}
	m_id = id;
    }

    LookupSet(){}; //maps bitch at you without this

    unsigned int frames()
    {
	return m_frames;
    }

    unsigned int turns()
    {
	return m_turns;
    }

    bool addNode(const T & data, const unsigned int & turn,const unsigned int & frame )
    {
	 if (frame >= m_frames || turn >= m_turns)
	{

		return false;
	 }
	 if (m_set[turn*m_frames + frame])
	     return false;

	 m_set[turn*m_frames +frame ] = new LookupNode<T,idtype>(data);


	 LookupNode<T,idtype> * prev;
	 LookupNode<T,idtype> * next;

	 for (int i = turn*m_frames +frame-1; i > -1; i--)
	 {
	    if (m_set[i])
		prev = m_set[i];
	 }

	 for (unsigned int i = turn*m_frames +frame+1; i < m_set.size(); i++)
	 {
	    if (m_set[i])
		next = m_set[i];
	 }

	 m_set[turn*m_frames +frame]->prev = prev;
	 m_set[turn*m_frames +frame]->next = next;


	 return true;
    }

    bool addNode(const LookupNode<T,idtype> *& node, const unsigned int & turn, const unsigned int & frame  )
    {
	if (frame >= m_frames || turn >= m_turns)
	       return false;

	if (m_set[frame*m_turns + turn])
	    return false;

	m_set[frame*m_turns + turn] = node;

	return true;
    }

    idtype id()
    {
	return m_id;
    }

private:
    std::vector<LookupNode<T,idtype>*> m_set;
    unsigned int m_frames, m_turns;
    idtype m_id;
    friend class LookupTable<T,idtype>;
};



template <typename T, typename idtype>
class LookupTable
{
	public:
		typedef std::vector< std::map<idtype,LookupNode<T,idtype>* > > Table;
		typedef std::map< idtype, LookupNode <T,idtype>* > Bucket;
		typedef LookupNode<T,idtype> Node;
		typedef LookupSet<T,idtype> Set;

		/** Default constructor */
		LookupTable(const unsigned int & turns, const unsigned int & frames);
		LookupTable();

		void setSize(const unsigned int & turns, const unsigned int & frames);
		int getTurns();
		int getFrames();

		void clear();

		bool add(const idtype & id, const unsigned int & turn, const unsigned int & frame,  const Node & input);
		bool add(Set & set);

		Node * node( const idtype & id,const unsigned int & turn, const unsigned int & frame);
		Bucket * bucket(const unsigned int & turn, const unsigned int & frame);

		/** Default destructor */
		virtual ~LookupTable();



	protected:
		Table m_table;
		unsigned int m_frames;
		unsigned int m_turns;
	private:
};

#include "timeline.hpp"
#endif // LOOKUPTABLE_H
