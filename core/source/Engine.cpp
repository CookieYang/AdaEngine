#include "Engine.h"
#include "ClassDB.h"
Engine* Engine::getInstance() {
	static Engine engine;
	return &engine;
}

void Engine::init() {

}