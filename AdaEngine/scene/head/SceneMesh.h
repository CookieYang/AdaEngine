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
	void setGeometryData(MeshSource* gData);
	virtual void Run() override;
private:
	virtual void CreateRenderResource() override;
};