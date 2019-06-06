#ifndef PARAM_H
#define PARAM_H

class BaseParam
{
	public : 
	
		BaseParam(){};
		
		virtual ~BaseParam(){};
		
		inline void setName(std::string _name ){ name = _name;}		
		inline std::string getName(){ return name; }
		
	private:
		std::string name = "default_param_name";
};

template<typename T>
class Param : public BaseParam
{
	public:
		Param(){}
		Param(const Param& other){}
		~Param(){};
		
		inline T getValue() { return value; }
		inline void setValue( T input ) { value = input; }
	private:
	
		T value;
		
};


class ParamMenu : public BaseParam
{
	public: 
		ParamMenu(){}
		ParamMenu(std::vector<std::string> _entries){
			int inc = 0;
			for(std::string str : _entries)
			{
				std::pair< std::string, int> entry;
				entry.first = str;
				entry.second = inc;
				
				entries.push_back(entry);
				inc++;
			}
		}
		ParamMenu(const ParamMenu& other){}
		
		inline int getValue(){ return value; }
		inline void setValue(int _val){ value = _val; }
		
		std::vector<std::pair< std::string, int>> entries;
	private:
		int value;
		
};
//~ template<>
//~ class Param <glm::vec3>{
		//~ 
		//~ public :
		//~ 
		//~ 
		//~ private :
			//~ glm::vec3 value
//~ }

#endif /* PARAM_H */ 
