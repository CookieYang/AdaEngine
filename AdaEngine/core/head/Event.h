#pragma once
#include "AdaMath.h"
#include "pybind11.h"
#include <map>

enum KEY
{
	MOUSELEFT = 0,
	MOUSERIGHT = 1,
	MOUSEMIDDLE = 2,
	KEY_SPACE         =  32,
	KEY_APOSTROPHE     =    39, /* ' */
	KEY_COMMA         =     44,  /* , */
	KEY_MINUS          =    45,  /* - */
	KEY_PERIOD       =      46,  /* . */
	KEY_SLASH       =       47,  /* / */
	KEY_0           =       48,
	KEY_1          =        49,
	KEY_2           =       50,
	KEY_3          =        51,
   KEY_4           =       52,
   KEY_5           =       53,
   KEY_6            =      54,
   KEY_7          =        55,
   KEY_8          =        56,
   KEY_9            =      57,
   KEY_SEMICOLON       =   59,  /* ; */
   KEY_EQUAL      =        61,  /* = */
   KEY_A           =       65,
   KEY_B         =         66,
   KEY_C        =          67,
   KEY_D         =         68,
   KEY_E         =         69,
   KEY_F         =         70,
   KEY_G        =          71,
   KEY_H        =          72,
   KEY_I          =        73,
   KEY_J          =        74,
   KEY_K        =          75,
   KEY_L          =        76,
   KEY_M       =           77,
   KEY_N        =          78,
   KEY_O          =        79,
   KEY_P        =          80,
   KEY_Q       =           81,
   KEY_R         =         82,
   KEY_S        =          83,
   KEY_T        =          84,
   KEY_U        =          85,
   KEY_V       =           86,
   KEY_W      =            87,
   KEY_X      =            88,
   KEY_Y         =         89,
   KEY_Z       =           90,
   KEY_LEFT_BRACKET   =    91,  /* [ */
   KEY_BACKSLASH       =   92 , /* \ */
   KEY_RIGHT_BRACKET  =    93 , /* ] */
   KEY_GRAVE_ACCENT   =    96  ,/* ` */

	/* Function   KEYs */
   KEY_ENTER      =        257,
   KEY_TAB          =      258,
   KEY_BACKSPACE     =     259,
   KEY_INSERT       =      260,
   KEY_DELETE       =      261,
   KEY_RIGHT       =       262,
   KEY_LEFT         =      263,
   KEY_DOWN     =          264,
   KEY_UP            =     265,
   KEY_PAGE_UP       =     266,
   KEY_PAGE_DOWN   =       267,
   KEY_HOME          =     268,
   KEY_END          =      269,
   KEY_CAPS_LOCK      =    280,
   KEY_SCROLL_LOCK   =     281,
   KEY_NUM_LOCK      =     282,
   KEY_PRINT_SCREEN  =     283,
   KEY_PAUSE     =         284,
   KEY_F1        =         290,
   KEY_F2          =       291,
   KEY_F3         =        292,
   KEY_F4         =        293,
   KEY_F5         =        294,
   KEY_F6         =        295,
   KEY_F7        =         296,
   KEY_F8         =        297,
   KEY_F9        =         298,
   KEY_F10       =         299,
   KEY_F11       =         300,
   KEY_F12       =         301,
   KEY_KP_DECIMAL     =    330,
   KEY_KP_DIVIDE       =   331,
   KEY_KP_MULTIPLY    =    332,
   KEY_KP_SUBTRACT  =      333,
   KEY_KP_ADD        =     334,
   KEY_KP_ENTER      =     335,
   KEY_KP_EQUAL     =      336,
   KEY_LEFT_SHIFT     =    340,
   KEY_LEFT_CONTROL   =    341,
   KEY_LEFT_ALT   =        342,
   KEY_LEFT_SUPER     =    343,
   KEY_RIGHT_SHIFT    =    344,
   KEY_RIGHT_CONTROL  =    345,
   KEY_RIGHT_ALT      =    346,
   KEY_RIGHT_SUPER    =    347,
   KEY_MENU         =      348
};

const std::map<KEY, std::string> KEYMAP = {
{KEY::MOUSELEFT,"MouseLeft"}, 
{KEY::MOUSERIGHT, "MouseRight"} ,
{KEY::KEY_SPACE, "KeySpace"} ,
{KEY::KEY_APOSTROPHE, "KeyApostrophe"} ,
{KEY::KEY_COMMA, "KeyComma"} ,
{KEY::KEY_MINUS, "KeyMinus"} ,
{KEY::KEY_PERIOD, "KeyPeriod"} ,
{KEY::KEY_SLASH, "KeySlash"} ,
{KEY::KEY_0, "Key0"} ,
{KEY::KEY_1, "Key1"} ,
{KEY::KEY_2, "Key2"} ,
{KEY::KEY_3, "Key3"} ,
{KEY::KEY_4, "Key4"} ,
{KEY::KEY_5, "Key5"} ,
{KEY::KEY_6, "Key6"} ,
{KEY::KEY_7, "Key7"} ,
{KEY::KEY_8, "Key8"} ,
{KEY::KEY_9, "Key9"} ,
{KEY::KEY_SEMICOLON, "KeySemicolon"} ,
{KEY::KEY_EQUAL, "KeyEqual"} ,
{KEY::KEY_A, "KeyA"} ,
{KEY::KEY_B, "KeyB"} ,
{KEY::KEY_C, "KeyC"} ,
{KEY::KEY_D, "KeyD"} ,
{KEY::KEY_E, "KeyE"} ,
{KEY::KEY_F, "KeyF"} ,
{KEY::KEY_G, "KeyG"} ,
{KEY::KEY_H, "KeyH"} ,
{KEY::KEY_I, "KeyI"} ,
{KEY::KEY_J, "KeyJ"} ,
{KEY::KEY_K, "KeyK"} ,
{KEY::KEY_L, "KeyL"} ,
{KEY::KEY_M, "KeyM"} ,
{KEY::KEY_N, "KeyN"} ,
{KEY::KEY_O, "KeyO"} ,
{KEY::KEY_P, "KeyP"} ,
{KEY::KEY_Q, "KeyQ"} ,
{KEY::KEY_R, "KeyR"} ,
{KEY::KEY_S, "KeyS"} ,
{KEY::KEY_T, "KeyT"} ,
{KEY::KEY_U, "KeyU"} ,
{KEY::KEY_V, "KeyV"} ,
{KEY::KEY_W, "KeyW"} ,
{KEY::KEY_X, "KeyX"} ,
{KEY::KEY_Y, "KeyY"} ,
{KEY::KEY_Z, "KeyZ"} ,
{KEY::KEY_LEFT_BRACKET, "KeyleftBracket"} ,
{KEY::KEY_BACKSLASH, "KeyBackSlash"} ,
{KEY::KEY_RIGHT_BRACKET, "KeyRightBracket"} ,
{KEY::KEY_GRAVE_ACCENT, "KeyGraveAccent"} ,
{KEY::KEY_ENTER, "KeyEnter"} ,
{KEY::KEY_TAB, "KeyTab"} ,
{KEY::KEY_BACKSPACE, "KeyBackSpace"} ,
{KEY::KEY_INSERT, "KeyInsert"} ,
{KEY::KEY_DELETE, "KeyDelete"} ,
{KEY::KEY_UP, "KeyUp"} ,
{KEY::KEY_DOWN, "KeyDown"} ,
{KEY::KEY_RIGHT, "KeyRight"} ,
{KEY::KEY_LEFT, "KeyLeft"} ,
{KEY::KEY_PAGE_UP, "KeyPageUp"} ,
{KEY::KEY_PAGE_DOWN, "KeyPageDown"} ,
{KEY::KEY_HOME, "KeyHome"} ,
{KEY::KEY_END, "KeyEnd"} ,
{KEY::KEY_CAPS_LOCK, "KeyCapsLock"} ,
{KEY::KEY_SCROLL_LOCK, "KeyScrollLock"} ,
{KEY::KEY_NUM_LOCK, "KeyNumLock"} ,
{KEY::KEY_PRINT_SCREEN, "KeyPrintScreen"} ,
{KEY::KEY_PAUSE, "KeyPause"} ,
{KEY::KEY_F1, "KeyF1"} ,
{KEY::KEY_F2, "KeyF2"} ,
{KEY::KEY_F3, "KeyF3"} ,
{KEY::KEY_F4, "KeyF4"} ,
{KEY::KEY_F5, "KeyF5"} ,
{KEY::KEY_F6, "KeyF6"} ,
{KEY::KEY_F7, "KeyF7"} ,
{KEY::KEY_F8, "KeyF8"} ,
{KEY::KEY_F9, "KeyF9"} ,
{KEY::KEY_F10, "KeyF10"} ,
{KEY::KEY_F11, "KeyF11"} ,
{KEY::KEY_F12, "KeyF12"} ,
{KEY::KEY_KP_DECIMAL, "KeyKpDecimal"} ,
{KEY::KEY_KP_DIVIDE, "KeyKpDivide"} ,
{KEY::KEY_KP_MULTIPLY, "KeyKpMultiply"} ,
{KEY::KEY_KP_SUBTRACT, "KeyKpSubtract"} ,
{KEY::KEY_KP_ADD, "KeyKpAdd"} ,
{KEY::KEY_KP_ENTER, "KeyKpEnter"} ,
{KEY::KEY_KP_EQUAL, "KeyKpEqual"} ,
{KEY::KEY_LEFT_SHIFT, "KeyLeftShift"} ,
{KEY::KEY_LEFT_ALT, "KeyLeftAlt"} ,
{KEY::KEY_LEFT_SUPER, "KeyLeftSuper"} ,
{KEY::KEY_RIGHT_SHIFT, "KeyRightShift"} ,
{KEY::KEY_RIGHT_CONTROL, "KeyRightControl"} ,
{KEY::KEY_RIGHT_ALT, "KeyRightAlt"} ,
{KEY::KEY_RIGHT_SUPER, "KeyRightSuper"} ,
{KEY::KEY_MENU, "KeyMenu"},
};

enum ACTION
{
	PRESS = 1,
	RELEASE = 0,
	REPEATE = 2
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
	Event() {};
	virtual EVENTYPE getType() { return EVENTYPE::NONE; };
	virtual ~Event() {};
public:
	bool bProcced = false;
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
	MouseMoveEvent(double x, double y) { pos = DMath::makeVect(x, y); };
	virtual EVENTYPE getType() { return EVENTYPE::MOUSEMOVEEVENT; };
	DMath::vec_t getMousePos() { return pos; };
	double deltaY = 0;
	double deltaX = 0;
private:
	DMath::vec_t pos;
};

class ScrollEvent : public Event {
public:
	ScrollEvent(double x, double y) { offset = DMath::makeVect(x, y); };
	virtual EVENTYPE getType() { return EVENTYPE::SCROLLEVENT; };
	DMath::vec_t getOffset() { return offset; };
private:
	DMath::vec_t offset;
};

template <class Base = Event> 
class PyEvent : public Base {
public:
	using Base::Base; // Inherit constructors
	EVENTYPE getType() override { PYBIND11_OVERLOAD(EVENTYPE, Base, getType, );}
};

void init_Event(pybind11::module& m);