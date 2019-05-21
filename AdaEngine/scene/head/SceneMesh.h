#pragma once
#include "SceneRenderable.h"
#include "MeshSource.h"

class GeometryData;

class SceneMesh : public SceneRenderable {
	RefCountedPtr<MeshSource> renderMesh;
public:
	SceneMesh();
	~SceneMesh();
	void setGeometryData(GeometryData* gData);
	virtual void CreateRenderResource() override;
	virtual void Run() override;
};