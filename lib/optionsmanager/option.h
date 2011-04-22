#ifndef OPTION_H
#define OPTION_H

enum OptionType
{
	OT_NONE,
	OT_INT,
	OT_FLOAT,
	OT_STRING,
	OT_BOOL
};


class OptionBase
{
	public:
		OptionBase(const OptionType & ot):m_type(ot){}
		OptionType type(){return m_type;}

	protected:
		OptionType m_type; //!< Member variable "m_type"
	private:

};

template<class T, OptionType ot>
class Option : public OptionBase
{
	public:
		Option(const T & data):OptionBase(ot),m_data(data){}
		Option():OptionBase(ot){}
		T get(){return m_data;}
		void set(const T & data){m_data = data;}
	protected:
		T m_data;
};


#endif // OPTION_H
