#pragma once

#include "State.h"

template<class entity_type>
class StateMachine
{
public:
	StateMachine(entity_type* pOwner) : owner(pOwner) {};

	void SetCurrentState(State<entity_type>* s)
	{
		currentState = s;
	}

	void SetPreviousState(State<entity_type>* s)
	{
		previousState = s;
	}

	void SetGlobalState(State<entity_type>* s)
	{
		globalState = s;
	}

	State<entity_type>* CurrentState() const
	{
		return currentState;
	}
	State<entity_type>* GlobalState() const
	{
		return globalState;
	}
	State<entity_type>* PreviousState() const
	{
		return previousState;
	}

	void Update()const
	{
		if (globalState)
		{
			globalState->execute(owner);
		}

		if (currentState)
		{
			currentState->execute(owner);
		}
	}

	void ChangeState(State<entity_type>* pNewState)
	{
		if (currentState != pNewState)
		{
			previousState = currentState;

			currentState->exit(owner);

			currentState = pNewState;

			currentState->enter(owner);
		}	
	}

	void RevertToPreviousState()
	{
		ChangeState(previousState);
	}

private:
	entity_type* owner;

	State<entity_type>* currentState = nullptr;
	State<entity_type>* previousState = nullptr;
	State<entity_type>* globalState = nullptr;
};

