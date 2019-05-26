#include "OglRenderInterface.h"
#include "RenderInterfaceWrap.h"

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
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	{
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(0, .5);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-.5, -.5);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(.5, -.5);
	}
	glEnd();
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

void OglRenderInterface::passDraw(RenderPass* pass) {

}

Material* OglRenderInterface::_createMaterial(RenderInterfaceWrap* wrap, const std::string& name, const std::string& shaderName) {
	Material* m = new Material;
	ShaderSource* shader = (ShaderSource*)this->_GetResourceByName(wrap, "defalut_shader", GPUResource::GResourceType::SHDADER);
	m->setName(name);
	m->attachShader(shader);
	return m;
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

}

MeshSource* OglRenderInterface::createMesh(const std::string& name) {
	MeshSource* mesh = new MeshSource;
	mesh->setName(name);
	return mesh;
}

void OglRenderInterface::uploadGeometry(MeshSection* mesh) {

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
	default:
		break;
	}
	return resource;
}