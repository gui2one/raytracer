#ifndef ACTIONS_H
#define ACTIONS_H

#include "../pch.h"
#include "param.h"

/*
template <typename T>
struct ParamSnapshot{

	std::pair< Param<T>, T > old_value, new_value;
	
	void printValues(){
		printf("what do I do now ?\n");
	}
};
*/

class Action{
public:
	Action(){}
	virtual void redo(){};
	virtual void undo(){};
	
	//~ std::pair< BaseParam *, float > old_value, new_value;
	
private:
};

template<typename T>
class ActionParamChange : public Action{

public:

	ActionParamChange(Param<T> * param, T old, T val, std::function<void()> callback) : Action(){
		m_param = param;
		m_callback = callback;
		old_value = old;
		new_value = val;
		//~ printf("old value stored : %s\n", param->getName().c_str());
		
		
		param->setValue(val);
		
		callback();
	};
	void redo()override{};
	
	void undo()override{
		m_param->setValue(old_value);
		m_callback();
	} ;
	
	Param<T> * m_param;
	T old_value, new_value;
	std::function<void()> m_callback;
		
private:
};

#endif /* ACTIONS_H */

