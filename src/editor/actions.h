#ifndef ACTIONS_H
#define ACTIONS_H

#include "../pch.h"

class Action{
public:
	Action(){}
	virtual void Do() = 0;
	virtual void Undo() = 0;
	
private:
};

class ActionParamChange : public Action{

public:
	ActionParamChange();
	void Do() override;
	void Undo() override;
		
private:
};

#endif /* ACTIONS_H */

