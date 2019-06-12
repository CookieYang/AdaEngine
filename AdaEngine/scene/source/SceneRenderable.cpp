#include "SceneRenderable.h"


void init_SceneRenderable(pybind11::module& m) {
	pybind11::class_<SceneRenderable, SceneNode, PySceneRenderable<>>(m, "SceneRenderable")
		.def("MakeRenderableNode", []() { return new SceneRenderable; }, pybind11::return_value_policy::reference);
}