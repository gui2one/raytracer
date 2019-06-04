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
		/* add your private declarations */
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
