#pragma once
#include "SceneNode.h" 
#include "MeshSource.h"

class SceneMesh : public SceneNode {
	RefCountedPtr<MeshSource> renderMesh;
};