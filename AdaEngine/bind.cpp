#include "Application.h"
#include "Event.h"
#include "AdaMath.h"
#include "SceneNode.h"
#include "SceneRenderable.h"
#include "ScenePawn.h"
#include "SceneMesh.h"
#include "Engine.h"


PYBIND11_MODULE(AdaEngine, m) {
	pybind11::module coreModule = m.def_submodule("Core");
	pybind11::module sceneModule = m.def_submodule("Scene");
	pybind11::module mathModule = m.def_submodule("Math");

	init_PyApplication(coreModule);
	init_Event(coreModule);
	init_Engine(coreModule);

	init_DMath(mathModule);

	init_SceneNode(sceneModule);
	init_SceneRenderable(sceneModule);
	init_ScenePawn(sceneModule);
	init_SceneMesh(sceneModule);
}