#pragma once
#include "SceneRenderable.h"
#include "MeshSource.h"
#include "Material.h"

class GeometryData;

class SceneMesh : public SceneRenderable {
	RefCountedPtr<MeshSource> renderMesh;
public:
	SceneMesh();
	~SceneMesh();
	void setGeometryData(GeometryData* gData);
	virtual void Run() override;
private:
	virtual void CreateRenderResource() override;
};