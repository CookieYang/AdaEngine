#include "OglRenderInterface.h"
#include "RenderInterfaceWrap.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

void passDraw(RenderPass* pass);
void buildPass(RenderPass* pass);
void buildShader(ShaderSource* shader);
void setMaterialUniforms(GLuint program, MaterialVar var);
void setTexture(GLuint program, TextureSource* tex, unsigned int index);

void OglRenderInterface::Init() {
	// init gl in rendering thread
	MakeCurrent();
	glClearColor(0.3f, 0.1f, 0.2f, 1.0f);
}

void OglRenderInterface::SwapBuffer() {
	context->swapBuffers();
	context->PollEvents();
}

void OglRenderInterface::ClearContext() {
	context->makeCurrentNull();
}

void OglRenderInterface::MakeCurrent() {
	context->makeCurrent();
}

double OglRenderInterface::getCurrentTime() {
	return context->getCurrentTime();
}

void OglRenderInterface::Draw() {
	// rendering thread draw
	MakeCurrent();
	double time = getCurrentTime();
	//glClear(GL_COLOR_BUFFER_BIT);
	//glBegin(GL_TRIANGLES);
	//{
	//	glColor3f(1.0, 0.0, 0.0);
	//	glVertex2f(0, .5);
	//	glColor3f(0.0, 1.0, 0.0);
	//	glVertex2f(-.5, -.5);
	//	glColor3f(0.0, 0.0, 1.0);
	//	glVertex2f(.5, -.5);
	//}
	//glEnd();
	RenderPineline* pineLine = RenderInterface::getSingleton()->getCurrentPineline();
	for (auto pass : pineLine->passes) {
		pass.currentTime = time;
		buildPass(&pass);
		passDraw(&pass);
	}
	ClearContext();
}

bool OglRenderInterface::Valid() {
	return context->isContextValid();
}

void OglRenderInterface::sync() {

}

void OglRenderInterface::Finish() {

}

void OglRenderInterface::Destory() {
	context->clearContext();
}

OglRenderInterface::OglRenderInterface() {
	context = std::shared_ptr<GLContext>(new GLContext);
	context->initContext();
}

OglRenderInterface::~OglRenderInterface() {
	Destory();
}


RenderPineline* OglRenderInterface::createPineline(PinelineType type) {
	return RenderPineline::createPineline(type);
}

void OglRenderInterface::_addMaterialToPineline(RenderInterfaceWrap* wrap, Material* mat) {
	return wrap->pineLine->addMaterialToPass(mat);
}

static void buildPass(RenderPass* pass) {
	for (auto mat : pass->activeMaterials) {
		if (mat->getDirty()) {
			if (mat->getShader()->getDirty())
			{
				buildShader(mat->getShader());
				mat->getShader()->setDirty(false);
			}
		}
		mat->setDirty(false);
	}
}

static void buildShader(ShaderSource* shader) {
	std::vector<unsigned int> shaderFrags;
	ShaderData* data = shader->getShaderData();
	shaderFrags.resize(data->shaderStrs.size(), 0);
	shader->program = glCreateProgram();
	for (size_t i = 0; i < shaderFrags.size(); i++)
	{
		int success;
		char infoLog[512];
		ShaderData::shaderString s = data->shaderStrs[i];
		switch (s.shaderType)
		{
		case ShaderData::ShaderType::VERTEXSHADER:
		{
			const char* code = s.shaderStr.c_str();
			shaderFrags[i] = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(shaderFrags[i], 1, &code, NULL);
			glCompileShader(shaderFrags[i]);
			glGetShaderiv(shaderFrags[i], GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shaderFrags[i], 512, NULL, infoLog);
			};
		}
			break;
		case ShaderData::ShaderType::FRAGMENTSHADER:
		{
			const char* code = s.shaderStr.c_str();
			shaderFrags[i] = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(shaderFrags[i], 1, &code, NULL);
			glCompileShader(shaderFrags[i]);
			glGetShaderiv(shaderFrags[i], GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shaderFrags[i], 512, NULL, infoLog);
			};
		}
		break;
		case ShaderData::ShaderType::GEOMETRYSHADER :
		{
			const char* code = s.shaderStr.c_str();
			shaderFrags[i] = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(shaderFrags[i], 1, &code, NULL);
			glCompileShader(shaderFrags[i]);
			glGetShaderiv(shaderFrags[i], GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shaderFrags[i], 512, NULL, infoLog);
			};
		}
		break;
		default:
			break;
		}
		glAttachShader(shader->program, shaderFrags[i]);
	}
	int linkSuccess;
	char linkInfo[512];
	glLinkProgram(shader->program);
	glGetProgramiv(shader->program, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess)
	{
		glGetProgramInfoLog(shader->program, 512, NULL, linkInfo);
	}

	for (size_t i = 0; i < shaderFrags.size(); i++)
	{
		glDeleteShader(shaderFrags[i]);
	}
}

static void passDraw(RenderPass* pass) {
	for (auto mat : pass->activeMaterials) {
		glUseProgram(mat->getShader()->program);
		for (auto mesh : mat->meshRefs) {
			glBindVertexArray(mesh->vao);
			for (auto var : mesh->mInstance.get()->materialVars) {
				setMaterialUniforms(mat->getShader()->program, var);
			}
			for (size_t i = 0; i < mesh->mInstance.get()->textureIDs.size(); i++)
			{
				TextureSource* tex = mesh->mInstance.get()->textureIDs[i].get();
				setTexture(mat->getShader()->program, tex, i);
			}
			glDrawElements(GL_TRIANGLES, mesh->vData->vertexIndices.size(), GL_UNSIGNED_INT, 0);
			GLenum e = glGetError();
			glBindVertexArray(0);
		}
	}
}

static void setMaterialUniforms(GLuint program, MaterialVar mat) {
	switch (mat.mType)
	{
	case MaterialVar::VarType::MAT4:
	{
		glUniform4fv(glGetUniformLocation(program, mat.bindingName.c_str()), 1, glm::value_ptr(mat.mVar.mat4));
	}
		break;
	default:
		break;
	}
}

static void  setTexture(GLuint program, TextureSource* tex, unsigned int index) {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, tex->textureID);
	glUniform1i(glGetUniformLocation(program, tex->bindingName.c_str()), index);
}

RenderPineline* OglRenderInterface::_getCurrentPineline(RenderInterfaceWrap* wrap) {
	return wrap->pineLine;
}

Material* OglRenderInterface::_createMaterial(RenderInterfaceWrap* wrap, const std::string& name, const std::string& shaderName) {
	Material* m = new Material;
	ShaderSource* shader = (ShaderSource*)this->_GetResourceByName(wrap, shaderName, GPUResource::GResourceType::SHDADER);
	m->setName(name);
	m->attachShader(shader);
	return m;
}

MaterialInstance* OglRenderInterface::_createMaterialInstance(RenderInterfaceWrap* wrap, const std::string& matInstanceName, const std::string& matName) {
	MaterialInstance* matInstance = new MaterialInstance;
	Material* m = (Material*)this->_GetResourceByName(wrap, matName, GPUResource::GResourceType::MATRERIAL);
	matInstance->mat = m;
	matInstance->setName(matInstanceName);

	// create defalut material Instance
	MaterialVar var1;
	var1.bindingName = "modelMat";
	var1.mType = MaterialVar::VarType::MAT4;
	var1.mVar.mat4 = glm::mat4(1.0f);

	MaterialVar var2;
	var2.bindingName = "viewMat";
	var2.mType = MaterialVar::VarType::MAT4;
	var2.mVar.mat4 = glm::mat4(1.0f);

	MaterialVar var3;
	var3.bindingName = "projMat";
	var3.mType = MaterialVar::VarType::MAT4;
	var3.mVar.mat4 = glm::mat4(1.0f);

	matInstance->materialVars.push_back(var1);
	matInstance->materialVars.push_back(var2);
	matInstance->materialVars.push_back(var3);

	return matInstance;
}

ShaderSource* OglRenderInterface::createShader(const std::string& name) {
	ShaderSource* shader = new ShaderSource;
	shader->setName(name);
	return shader;
}

TextureSource* OglRenderInterface::createTexture(const std::string& name) {
	TextureSource* tex =  new TextureSource;
	tex->setName(name);
	return tex;
}

void OglRenderInterface::uploadTexture(TextureSource* tex) {
	glGenTextures(1, &tex->textureID);
	glBindTexture(GL_TEXTURE_2D, tex->textureID);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* rawData = tex->getRawData();
	if (rawData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->getWidth(), tex->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, rawData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

MeshSource* OglRenderInterface::createMesh(const std::string& name) {
	MeshSource* mesh = new MeshSource;
	mesh->setName(name);
	return mesh;
}

void OglRenderInterface::uploadGeometry(MeshSection* mesh) {
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ebo);
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->vData->vertexIndices.size() * sizeof(unsigned int), mesh->vData->vertexIndices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	size_t totalSize = 0; 
	
	size_t offset = 0;
	glm::vec3* vP = mesh->vData->vertexPosition.data();
	glm::vec2* vUV = mesh->vData->vertexUV.data();
	glm::vec3* vN = mesh->vData->vertexNormal.data();
	glm::vec3* vT = mesh->vData->vertexTangent.data();
	glm::vec3* vB = mesh->vData->vertexBiTanget.data();
	if (vP) {
		totalSize += mesh->vData->vertexPosition.size() * sizeof(glm::vec3);
	}
	if (vUV) {
		totalSize += mesh->vData->vertexUV.size() * sizeof(glm::vec2);
	}
	if (vN) {
		totalSize += mesh->vData->vertexNormal.size() * sizeof(glm::vec3);
	}
	if (vT) {
		totalSize += mesh->vData->vertexTangent.size() * sizeof(glm::vec3);
	}
	if (vB) {
		totalSize += mesh->vData->vertexBiTanget.size() * sizeof(glm::vec3);
	}
	glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);
	if (vP)
	{
		size_t  offVP = mesh->vData->vertexPosition.size() * sizeof(glm::vec3);
		glBufferSubData(GL_ARRAY_BUFFER, 0, offVP, vP);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(offset));
		glEnableVertexAttribArray(0);
		offset += offVP;
	}
	

	if (vUV)
	{
		size_t offUV = mesh->vData->vertexUV.size() * sizeof(glm::vec2);
		glBufferSubData(GL_ARRAY_BUFFER, 0, offUV, vUV);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(offset));
		glEnableVertexAttribArray(1);
		offset += offUV;
	}

	if (vN)
	{
		size_t offN = mesh->vData->vertexNormal.size() * sizeof(glm::vec3);
		glBufferSubData(GL_ARRAY_BUFFER, 0, offN, vN);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(offset));
		glEnableVertexAttribArray(2);
		offset += offN;
	}

	if (vT)
	{
		size_t offT = mesh->vData->vertexTangent.size() * sizeof(glm::vec3);
		glBufferSubData(GL_ARRAY_BUFFER, 0, offT, vT);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(offset));
		glEnableVertexAttribArray(3);
		offset += offT;
	}

	if (vB)
	{
		size_t offB = mesh->vData->vertexBiTanget.size() * sizeof(glm::vec3);
		glBufferSubData(GL_ARRAY_BUFFER, 0, offB, vB);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(offset));
		glEnableVertexAttribArray(4);
		offset += offB;
	}
	glBindVertexArray(0);
}

GPUResource* OglRenderInterface::_GetResourceByName(RenderInterfaceWrap* wrap, std::string name, GPUResource::GResourceType type) {
	GPUResource* resource = nullptr;
	switch (type)
	{
	case GPUResource::MESH:
		resource = wrap->MeshSourceMap[name];
		break;
	case GPUResource::SHDADER:
		resource = wrap->ShaderSourceMap[name].get();
		break;
	case GPUResource::TEXTURE:
		resource = wrap->TextureSourceMap[name];
		break;
	case GPUResource::MATRERIAL:
		resource = wrap->MaterialMap[name].get();
		break;
	case GPUResource::MATERIALINS:
		resource = wrap->MaterialInstanceMap[name];
		break;
	default:
		break;
	}
	return resource;
}