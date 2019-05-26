#pragma once
#include "SceneRenderable.h"
#include "MeshSource.h"


class SceneMesh : public SceneRenderable {
	RefCountedPtr<MeshSource> renderMesh;
	std::string meshName;
	std::vector<std::string> materialNames;
public:
	SceneMesh();
	~SceneMesh();
	void setGeometry(const std::string& name);
	void setMesh(const std::string& name);
	void setMaterial(const std::string& name);
	void setMaterialForSection(const std::string& name, int sectionIndex);
	int getSectionNum();
	virtual void Run() override;
};