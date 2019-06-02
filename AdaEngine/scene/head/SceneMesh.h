#pragma once
#include "SceneRenderable.h"

class MeshComponent;

class SceneMesh : public SceneRenderable {
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
	virtual void doRun() override;
	virtual void doUpdateTransform() override;
protected:
	MeshComponent* mesh;
};