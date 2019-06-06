#include "Application.h"
#include "Event.h"

PYBIND11_MODULE(AdaEngine, m) {
	pybind11::module coreModule = m.def_submodule("core");
	pybind11::module sceneModule = m.def_submodule("scene");
	init_PyApplication(coreModule);
	init_Event(coreModule);
}