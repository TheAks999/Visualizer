#include "timeline.h"
#include <iostream>

/** @brief ~LookupTable
  * destructor!
  */
template <typename T, typename idtype>
 LookupTable<T,idtype>::~LookupTable()
{
	clear();
}

/** @brief node
  *	get a pointer to a node
  * @param turn the turn you are looking for
  * @param frame the frame you are looking for
  * @param id the id of the object you are looking for
  * @return a pointer to the node of the object or NULL if the requested
	object is out of range or doesn't exist
  */
template <typename T, typename idtype>
LookupNode<T,idtype> * LookupTable<T,idtype>::node(const idtype & id, const unsigned int & turn, const unsigned int & frame)
{

	Bucket * buck = bucket(turn,frame);

	if (buck == NULL)
		return NULL;

	typename Bucket::iterator it = buck->find(id);

	if (it == buck->end())
		return NULL;

	return(it->second);
}

/** @brief add
  *	add a node to the structure
  * @param turn the turn to add at
  * @param frame the frame to add at
  * @param id the id of the object
  * @param input the value to input in
  */
template <typename T, typename idtype>
bool LookupTable<T,idtype>::add(const idtype & id, const unsigned int & turn, const unsigned int & frame, const Node & input)
{
	Bucket * buck = bucket(turn,frame);

	if (buck)
	{
	    (*buck)[id] = input;
	    return true;
	}
	return false;
}

/** @brief clear
  *	clear all data from the container
  */
template <typename T, typename idtype>
void LookupTable<T,idtype>::clear()
{
	for (unsigned int i = 0; i < m_table.size(); i++)
		m_table[i].clear();

	m_table.clear();

	m_turns = 0;
	m_frames = 0;
}

/** @brief getFrames
  *	get the number of frames in the object
  * @return the number of frames
  */
template <typename T, typename idtype>
int LookupTable<T,idtype>::getFrames()
{
	return m_frames;
}

/** @brief getTurns
  * get the number of turns per frame
  * @return the number of turns
  */
template <typename T, typename idtype>
int LookupTable<T,idtype>::getTurns()
{
	return m_turns;
}

/** @brief setSize
  *	set the size of the structure
  * clears the structure first
  * @param turns the number of turns the structure is to have
  * @param frames the number of frames the structure is to have
  */
template <typename T, typename idtype>
void LookupTable<T,idtype>::setSize(const unsigned int & turns, const unsigned int & frames)
{
	clear();
	m_turns = turns;
	m_frames = frames;

	m_table.resize(turns*frames);
}

/** @brief LookupTable
  *	constructor
  * frames and turns are 0
  */
template <typename T, typename idtype>
 LookupTable<T,idtype>::LookupTable()
{
	m_turns = 0;
	m_frames = 0;
}

/** @brief LookupTable
  * constructor
  * @param turns: the number of turns the structure is to have
  * @param frames: the number of frames the structure is to have
  */
template <typename T, typename idtype>
 LookupTable<T,idtype>::LookupTable(const unsigned int & turns, const unsigned int & frames)
{
	setSize(turns,frames);
}

/** @brief bucket
  * Included only for completeness, you probably won't need to use this.
  * @param turn: Which turn you want all the gameobjects of
  * @param frame: Which frame you want all the gameobjects of
  * @return pointer to a bucket (map) of all the gameobjects associated with that turn & frame
  */
template <typename T, typename idtype>
std::map< idtype, LookupNode<T,idtype>* > * LookupTable<T,idtype>::bucket(const unsigned int & turn, const unsigned int & frame)
{
    //std::cout << "check: turn (" << turn << " , " << m_turns<< ") frame (" << frame << "," << m_frames << ")\n";
    if (turn >= m_turns || frame >= m_frames)
	    return NULL;

    return &m_table[turn*m_frames + frame];
}

/** @brief add
  * Allows you to add a gameobject set to the lookuptable.
  * A set tracks a gameobject through the object's entire existance in the game.
  * @todo document this function
  */
template <typename T, typename idtype>
bool LookupTable<T,idtype>::add(Set & set)
{
    if (m_frames != set.m_frames || m_turns != set.m_turns)
    {
	//
	std::cout << "Add frames: " << m_frames << "->" << set.m_frames << " turns: " << m_turns << "->" << set.m_turns <<"\n";
	return false;
    }

    for (unsigned int turn = 0; turn < m_turns; turn++)
    {
	for (unsigned int frame = 0; frame < m_frames; frame++)
	{
	    if (set.m_set[turn*m_frames + frame])
	    {
		//std::cout << "somad: " << turn*m_frames + frame << " <==> " <<set.m_set.size() << '\n';
		//std::cout << "test: " << set.m_set[turn*m_frames + frame] << " ==> " << turn*m_frames + frame << "\n";
		m_table[turn*m_frames + frame][set.m_id] = set.m_set[turn*m_frames + frame];
	    }
	    else
	    {
		//std::cout << "test: " << set.m_set[turn*m_frames + frame] << " ==> " << turn*m_frames + frame << "\n";
	    }
	}
    }
    return true;
}
