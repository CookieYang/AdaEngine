#include "ScenePawn.h"
#include "CameraComponent.h"
#include "MoveComponent.h"
#include "InputComponent.h"
#include "Engine.h"

ScenePawn::ScenePawn(){
	cameraCom = new CameraComponent(this);
	moveCom = new MoveComponent(this);
	moveCom->speed = 200.0f;
	InputComponent* inputCom = new InputComponent;
	inputCom->actionMap.find("MoveForward")->second->operator+=(mem_call(*this, &ScenePawn::MoveForward));
	inputCom->actionMap.find("MoveBack")->second->operator+=(mem_call(*this, &ScenePawn::MoveBack));
	inputCom->actionMap.find("MoveRight")->second->operator+=(mem_call(*this, &ScenePawn::MoveRight));
	inputCom->actionMap.find("MoveLeft")->second->operator+=(mem_call(*this, &ScenePawn::MoveLeft));
	inputCom->actionMap.find("TurnRight")->second->operator+=(mem_call(*this, &ScenePawn::TurnRight));
	inputCom->actionMap.find("TurnUp")->second->operator+=(mem_call(*this, &ScenePawn::TurnUp));
	inputCom->actionMap.find("Zoom")->second->operator+=(mem_call(*this, &ScenePawn::Zoom));
	components.push_back(RefCountedPtr<Component>(inputCom));
}

void ScenePawn::MoveForward(Event* event) {
	moveCom->MoveForward(Engine::getInstance()->deltaTime * 1.0f);
}

void ScenePawn::MoveBack(Event* event) {
	moveCom->MoveForward(-Engine::getInstance()->deltaTime * 1.0f);
}

void  ScenePawn::MoveRight(Event* event) {
	moveCom->MoveRight(Engine::getInstance()->deltaTime * 1.0f);
}

void  ScenePawn::MoveLeft(Event* event) {
	moveCom->MoveRight(-Engine::getInstance()->deltaTime * 1.0f);
}

void  ScenePawn::TurnRight(Event* event) {
	MouseMoveEvent* mEvent = static_cast<MouseMoveEvent*>(event);
	moveCom->AddYaw(mEvent->deltaX);
}

void  ScenePawn::TurnUp(Event* event) {
	MouseMoveEvent* mEvent = static_cast<MouseMoveEvent*>(event);
	moveCom->AddPitch(mEvent->deltaY);
}

void  ScenePawn::Zoom(Event* event) {
	ScrollEvent* sEvent = static_cast<ScrollEvent*>(event);
	cameraCom->Zoom -= sEvent->getOffset().y;
}

 void ScenePawn::ActiveControl() {
	 cameraCom->setActive();
 }

 void init_ScenePawn(pybind11::module& m) {
	 pybind11::class_<ScenePawn, SceneRenderable, PySceneRenderable<ScenePawn>>(m, "ScenePawn")
		 .def(pybind11::init<>())
		 .def("ActiveControl", &ScenePawn::ActiveControl)
		 ;
 }