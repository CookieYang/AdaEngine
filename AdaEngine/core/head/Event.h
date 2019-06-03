#pragma once
#include "AdaMath.h"

enum KEY
{
	MOUSELEFT = 0,
	MOUSERIGHT = 1,
	MOUSEMIDDLE = 2,
	KEY_A = 65,
	KEY_S = 83,
	KEY_D = 68,
	KEY_W = 87
};

enum ACTION
{
	PRESS = 1,
	RELEASE = 0
};

enum EVENTYPE {
	NONE,
	KEYEVENT,
	MOUSEMOVEEVENT,
	SCROLLEVENT
};

class Event
{
public:
	Event():bProcced(false) {}
	virtual EVENTYPE getType() { return EVENTYPE::NONE; };
	virtual ~Event() {};
public:
	bool bProcced;
};

class KeyEvent: public Event {
public:
	KeyEvent(KEY k, ACTION act) :key(k), action(act) {}
	virtual EVENTYPE getType() { return EVENTYPE::KEYEVENT; };
	KEY getKey() { return key; };
	ACTION getAction() { return action; };
private:
	KEY key;
	ACTION action;
};

class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(double x, double y) :pos(x, y) {}
	virtual EVENTYPE getType() { return EVENTYPE::MOUSEMOVEEVENT; };
	DVector2 getMousePos() { return pos; };
private:
	DVector2 pos;
};

class ScrollEvent : public Event {
public:
	ScrollEvent(double x, double y):offset(x, y) {}
	virtual EVENTYPE getType() { return EVENTYPE::SCROLLEVENT; };
	DVector2 getOffset() { return offset; };
private:
	DVector2 offset;
};