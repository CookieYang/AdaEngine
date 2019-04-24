#pragma once
class Engine {
public:
	static Engine* getInstance();
	void init();
private:
	Engine() {};
	~Engine() {};
};