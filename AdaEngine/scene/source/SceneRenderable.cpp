#include "SceneRenderable.h"


void init_SceneRenderable(pybind11::module& m) {
	pybind11::class_<SceneRenderable, SceneNode, PySceneRenderable<>>(m, "SceneRenderable")
		.def(pybind11::init<>());
}