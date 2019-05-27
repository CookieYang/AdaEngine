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
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glViewport(0, 0, 1280, 720);
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
	glClear(GL_COLOR_BUFFER_BIT);
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
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
			glDrawElements(GL_TRIANGLES, mesh->vData->vertexIndices.size(), GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	glBindTexture(GL_TEXTURE_2D, *tex->textureID);
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
	var1.mVar.mat4 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.1));

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
	MakeCurrent();
	glGenTextures(1, tex->textureID);
	glBindTexture(GL_TEXTURE_2D, *tex->textureID);
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
	glBindTexture(GL_TEXTURE_2D, 0);
	ClearContext();
}

MeshSource* OglRenderInterface::createMesh(const std::string& name) {
	MeshSource* mesh = new MeshSource;
	mesh->setName(name);
	return mesh;
}

void OglRenderInterface::uploadGeometry(MeshSection* mesh) {
	MakeCurrent();
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(mesh->vbos.size(), mesh->vbos.data());
	glGenBuffers(1, &mesh->ebo);

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->vData->vertexIndices.size() * sizeof(unsigned int), mesh->vData->vertexIndices.data(), GL_STATIC_DRAW);

	//float vertex[] = {1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 0.0};
	//float uv[] = {1.0, 0.0,   0.0, 1.0,  0.0, 0.0 };

	if (mesh->vData->vertexPosition.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[0]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * mesh->vData->vertexPosition.size(), mesh->vData->vertexPosition.data(), GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
	}

	if (mesh->vData->vertexUV.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[1]);
		glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * mesh->vData->vertexUV.size(), mesh->vData->vertexUV.data(), GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	if (mesh->vData->vertexNormal.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[2]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * mesh->vData->vertexNormal.size(), mesh->vData->vertexNormal.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	if (mesh->vData->vertexTangent.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[3]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * mesh->vData->vertexTangent.size(), mesh->vData->vertexTangent.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(3);
	}

	if (mesh->vData->vertexBiTanget.size() != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[4]);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * mesh->vData->vertexBiTanget.size(), mesh->vData->vertexBiTanget.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(4);
	}
	glBindVertexArray(0);
	ClearContext();
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