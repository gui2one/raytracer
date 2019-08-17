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
	virtual void Do(){};
	virtual void Undo(){};
	
private:
};

template<typename T>
class ActionParamChange : public Action{

public:

	ActionParamChange(Param<T> * param, T val){
		old_value.first = param;
		old_value.second = param->getValue();
		printf("old value stored\n");
		param->setValue(val);
	};
	void Do()override{} ;
	void Undo()override{} ;
	
	std::pair< Param<T>*, T > old_value, new_value;
		
private:
};

#endif /* ACTIONS_H */

