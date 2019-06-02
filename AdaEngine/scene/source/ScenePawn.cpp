#include "ScenePawn.h"
#include "CameraComponent.h"
#include "MoveComponent.h"

ScenePawn::ScenePawn() {
	cameraCom = new CameraComponent(this);
	moveCom = new MoveComponent(this);
}

 void ProcessKeyEvent(Event* kEvent) {

}

 void ProcessMouseMoveEvent(Event* mEvent) {

}

 void ProcessScrollEvent(Event* sEvent) {
 
 }