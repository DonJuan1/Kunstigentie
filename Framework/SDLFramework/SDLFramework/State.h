#pragma once

#include <string>

template<class entity_type>
class State
{
public:
	virtual void enter(entity_type*) = 0;
	virtual void execute(entity_type*) = 0;
	virtual void exit(entity_type*) = 0;

	virtual std::string name() = 0;

	virtual ~State(){}
};


