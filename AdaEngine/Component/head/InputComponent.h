#pragma once
#include "Component.h"
#include "Delegate.h"
#include "Event.h"



class InputComponent : public Component {
public:
	InputComponent();
	~InputComponent() {};
	virtual bool ProcessEvent(Event* event);
	std::map<std::string, std::string> eventMapping;
	std::map<std::string, delegate<void(Event*)>*> actionMap;
};