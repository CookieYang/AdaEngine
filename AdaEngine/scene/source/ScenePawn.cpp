#include "ScenePawn.h"
#include "CameraComponent.h"
#include "MoveComponent.h"
#include "IRenderInterface.h"

ScenePawn::ScenePawn():bFirstMouse(true) {
	cameraCom = new CameraComponent(this);
	moveCom = new MoveComponent(this);
}

bool ScenePawn::ProcessKeyEvent(Event* kEvent) {
	 KeyEvent* event = dynamic_cast<KeyEvent*>(kEvent);
	 if (event->getAction() == ACTION::REPEATE) {
		 if (event->getKey() == KEY_W)
		 {
			 moveCom->MoveForward(1.0f);
		 }
		 else if (event->getKey() == KEY_S)
		 {
			 moveCom->MoveForward(-1.0f);
		 }
		 else if (event->getKey() == KEY_D)
		 {
			 moveCom->MoveRight(1.0f);
		 }
		 else if (event->getKey() == KEY_A)
		 {
			 moveCom->MoveRight(-1.0f);
		 }
		 return true;
	 }
	 else {
		 return false;
	 }
}

 bool ScenePawn::ProcessMouseMoveEvent(Event* mEvent) {
	 MouseMoveEvent* event = dynamic_cast<MouseMoveEvent*>(mEvent);
	 DMath::vec_t pos = event->getMousePos();
	 if (bFirstMouse)
	 {
		 lastMousePos = pos;
		 bFirstMouse = false;
	 }

	 float xoffset = pos.x - lastMousePos.x;
	 float yoffset = lastMousePos.y - pos.y;
	 lastMousePos = pos;

	 moveCom->AddPitch(xoffset);
	 moveCom->AddYaw(yoffset);
	 return true;
}

 bool ScenePawn::ProcessScrollEvent(Event* sEvent) {
	 ScrollEvent* scrollEvent = dynamic_cast<ScrollEvent*>(sEvent);
	 cameraCom->Zoom -= scrollEvent->getOffset().y;
	 return true;
 }

 void ScenePawn::ActiveControl() {
	 RenderInterface::getSingleton()->setActiveCamera(cameraCom);
 }