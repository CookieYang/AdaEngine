#include "OglRenderInterface.h"
#include "RenderInterfaceWrap.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "MeshSource.h"

void passDraw(RenderPass* pass);
void buildPass(RenderPass* pass);
void buildShader(ShaderSource* shader);
void setMaterialUniforms(GLuint program, const std::string& bindingName, MaterialVar var, int index);

void OglRenderInterface::Init() {
	// init gl in rendering thread
	RenderInterface::MakeCurrent();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.0f);
	glViewport(0, 0, Engine::getInstance()->config->windowFrame[2], Engine::getInstance()->config->windowFrame[3]);
}

void OglRenderInterface::Draw(double time) {
	// rendering thread draw
	RenderInterface::MakeCurrent();
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
		pass.passBegin();
		buildPass(&pass);
		passDraw(&pass);
		pass.passEnd();
	}
	Engine::getInstance()->win->SwapBuffer();
}

void OglRenderInterface::sync() {

}

void OglRenderInterface::Finish() {

}

OglRenderInterface::OglRenderInterface() {
	RenderInterface::MakeCurrent();
	Engine::getInstance()->win->SetSwapInterval(0);
	context = std::unique_ptr<GLContext>(new GLContext);
	context->initContext();
	RenderInterface::ClearCurrent();
}

OglRenderInterface::~OglRenderInterface() {
	
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
			if (mesh->passMask & pass->passMask)
			{
				glBindVertexArray(mesh->vao);
				int texIndex = 0;
				// update transform
				mesh->mInstance.get()->materialVars["modelMat"] = mesh->trans;
				CameraComponent* camera = RenderInterface::getSingleton()->getActiveCamera();
				if (camera)
				{
					mesh->mInstance.get()->materialVars["viewMat"] = camera->GetViewMatrix();
					mesh->mInstance.get()->materialVars["projMat"] = camera->GetProjMatrix();
				}
				for (auto item : mesh->mInstance.get()->materialVars) {
					MaterialVar var = item.second;
					setMaterialUniforms(mat->getShader()->program, item.first, var, texIndex);
					if (var.mType == MaterialVar::VarType::TEXTURE2D)
					{
						texIndex++;
					}
				}
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
				glDrawElements(GL_TRIANGLES, mesh->drawCount, GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		}
	}
}

static void setMaterialUniforms(GLuint program, const std::string& bindingName, MaterialVar mat, int index) {
	switch (mat.mType)
	{
	case MaterialVar::VarType::MAT4:
	{
		glUniformMatrix4fv(glGetUniformLocation(program, bindingName.c_str()), 1, GL_FALSE, glm::value_ptr(mat.mVar.mat4));
	}
		break;
	case MaterialVar::VarType::TEXTURE2D:
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, *mat.mVar.texID);
		glUniform1i(glGetUniformLocation(program, bindingName.c_str()), index);
	}
	break;
	default:
		break;
	}
}

RenderPineline* OglRenderInterface::_getCurrentPineline(RenderInterfaceWrap* wrap) {
	return wrap->pineLine;
}

void OglRenderInterface::_setActiveCamera(RenderInterfaceWrap* wrap, CameraComponent* camera) {
	wrap->camera = camera;
}

CameraComponent* OglRenderInterface::_getActiveCamera(RenderInterfaceWrap* wrap) {
	return wrap->camera;
}

void OglRenderInterface::updateMaterialParam(MaterialInstance* mat, const std::string& paramName, MaterialVar var) {
	mat->materialVars[paramName] = var;
}

void OglRenderInterface::uploadTexture(TextureSource* tex) {
	RenderInterface::MakeCurrent();
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
	glBindTexture(GL_TEXTURE_2D, 0);
}



void OglRenderInterface::uploadGeometry(MeshSource* meshSource) {
	RenderInterface::MakeCurrent();
	for (size_t i = 0; i < meshSource->getSectionNum(); i++)
	{
		MeshSection* mesh = meshSource->getMeshSection(i);
		GeometryData::VertexData* vData = meshSource->getSectionData(i);
		glGenVertexArrays(1, &mesh->vao);
		glGenBuffers(mesh->vbos.size(), mesh->vbos.data());
		glGenBuffers(1, &mesh->ebo);

		glBindVertexArray(mesh->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vData->vertexIndices.size() * sizeof(unsigned int), vData->vertexIndices.data(), GL_STATIC_DRAW);

		//float vertex[] = {1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 0.0};
		//float uv[] = {1.0, 0.0,   0.0, 1.0,  0.0, 0.0 };

		if (vData->vertexPosition.size() != 0) {
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[0]);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vData->vertexPosition.size(), vData->vertexPosition.data(), GL_STATIC_DRAW);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
			glEnableVertexAttribArray(0);
		}


		if (vData->vertexUV.size() != 0) {
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[1]);
			glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * vData->vertexUV.size(), vData->vertexUV.data(), GL_STATIC_DRAW);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
			glEnableVertexAttribArray(1);
		}

		if (vData->vertexNormal.size() != 0) {
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[2]);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vData->vertexNormal.size(), vData->vertexNormal.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}


		if (vData->vertexTangent.size() != 0) {
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[3]);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vData->vertexTangent.size(), vData->vertexTangent.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
			glEnableVertexAttribArray(3);
		}

		if (vData->vertexBiTanget.size() != 0) {
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[4]);
			glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * vData->vertexBiTanget.size(), vData->vertexBiTanget.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
			glEnableVertexAttribArray(4);
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void OglRenderInterface::resizeViewport(int width, int height) {
	RenderInterface::MakeCurrent();
	glViewport(0, 0, width, height);
}
