#include "InputComponent.h"
#include "Config.h"

InputComponent::InputComponent() {
	Config cig;
	cig.loadJson("config/Config.json");
	const rapidjson::Value& keyboardSetting = cig.asMap("KeyboardInputConfig");
	const rapidjson::Value& mouseSetting = cig.asMap("MouseInputCofig");

	for (rapidjson::Value::ConstMemberIterator itr = keyboardSetting.MemberBegin();
		itr != keyboardSetting.MemberEnd(); ++itr)
	{
		eventMapping[itr->name.GetString()] = itr->value.GetString();
		actionMap[itr->value.GetString()] = new delegate<void(Event*)>;
	}

	for (rapidjson::Value::ConstMemberIterator itr = mouseSetting.MemberBegin();
		itr != mouseSetting.MemberEnd(); ++itr)
	{
		eventMapping[itr->name.GetString()] = itr->value.GetString();
		actionMap[itr->value.GetString()] = new delegate<void(Event*)>;
	}
}

bool InputComponent::ProcessEvent(Event* event) {
	switch (event->getType())
	{
	case KEYEVENT:
	{
		KeyEvent* kEvent = dynamic_cast<KeyEvent*>(event);
		KEY key = kEvent->getKey();
		auto find1 = KEYMAP.find(key);
		if (find1 != KEYMAP.end())
		{
			std::string keyString = KEYMAP.find(key)->second;
			if (keyString != "")
			{
				auto find2 = eventMapping.find(keyString);
				if (find2 != eventMapping.end())
				{
					std::string action = eventMapping.find(keyString)->second;
					delegate<void(Event*)>* d = actionMap.find(action)->second;
					if (d)
					{
						d->operator()(event);
						return true;
					}
				}
			}
		}
		return false;
	}
	break;
	case MOUSEMOVEEVENT:
	{
		std::string action = eventMapping.find("MouseMoveX")->second;
		delegate<void(Event*)>* d = actionMap.find(action)->second;
		if (d)
		{
			d->operator()(event);
		}

		std::string action2 = eventMapping.find("MouseMoveY")->second;
		delegate<void(Event*)>* d2 = actionMap.find(action2)->second;
		if (d2)
		{
			d2->operator()(event);
		}
		return true;
	}
	break;

	case SCROLLEVENT:
	{
		std::string action = eventMapping.find("MouseScroll")->second;
		delegate<void(Event*)>* d = actionMap.find(action)->second;
		if (d)
		{
			d->operator()(event);
		}
		return true;
	}
	break;
	default:
		break;
	}
	return false;
}