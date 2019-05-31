#pragma once
#include "TransformComponent.h"
#include "MeshSource.h"

class MeshComponent {
public:
	RefCountedPtr<MeshSource> sMesh;
	TransformComponent transComponent;
	void setGeometry(const std::string& name);
	void setMesh(const std::string& name);
	void setMaterial(const std::string& name);
	void setMaterialForSection(const std::string& name, int sectionIndex);
	void updateTransform(const glm::mat4& trans);
	int getSectionNum();
};