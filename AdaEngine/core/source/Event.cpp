#include "Event.h"

void init_Event(pybind11::module& m) {

	pybind11::enum_<KEY>(m, "ENUMKEY")
		.value("MOUSELEFT", KEY::MOUSELEFT)
		.value("MOUSERIGHT", KEY::MOUSERIGHT)
		.value("MOUSEMIDDLE", KEY::MOUSEMIDDLE)
		.value("KEY_A", KEY::KEY_A)
		.value("KEY_S", KEY::KEY_S)
		.value("KEY_D", KEY::KEY_D)
		.value("KEY_W", KEY::KEY_W)
		.export_values();

	pybind11::enum_<ACTION>(m, "ENUMACTION")
		.value("PRESS", ACTION::PRESS)
		.value("RELEASE", ACTION::RELEASE)
		.value("REPEATE", ACTION::REPEATE)
		.export_values();

	pybind11::enum_<EVENTYPE>(m, "ENUMEVENTYPE")
		.value("NONE", EVENTYPE::NONE)
		.value("KEYEVENT", EVENTYPE::KEYEVENT)
		.value("MOUSEMOVEEVENT", EVENTYPE::MOUSEMOVEEVENT)
		.value("SCROLLEVENT", EVENTYPE::SCROLLEVENT)
		.export_values();

	pybind11::class_<Event, PyEvent<>>(m, "Event")
		.def(pybind11::init<>());


	pybind11::class_<KeyEvent, PyEvent<KeyEvent>>(m, "KeyEvent")
		.def(pybind11::init<>())
		.def("getKey", &KeyEvent::getKey)
		.def("getAction", &KeyEvent::getAction);

	pybind11::class_<MouseMoveEvent, PyEvent<MouseMoveEvent>>(m, "MouseMoveEvent")
		.def(pybind11::init<>())
		.def("getMousePos", &MouseMoveEvent::getMousePos);

	pybind11::class_<ScrollEvent, PyEvent<ScrollEvent>>(m, "ScrollEvent")
		.def(pybind11::init<>())
		.def("getOffset", &ScrollEvent::getOffset);
}