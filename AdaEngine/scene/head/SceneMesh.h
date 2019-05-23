#pragma once
#include "SceneRenderable.h"
#include "MeshSource.h"
#include "Material.h"

class GeometryData;

class SceneMesh : public SceneRenderable {
	RefCountedPtr<MeshSource> renderMesh;
public:
	SceneMesh();
	SceneMesh(MeshSource* mesh);
	~SceneMesh();
	virtual void Run() override;
};