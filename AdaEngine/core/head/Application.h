#pragma once
#include <memory>
#include "pybind11.h"

class Application {
public:
	// do initilization(Engine)
	virtual void Initilize();
	// run
	void Run();

	virtual void Destory();

	Application();

	virtual ~Application();

	// interface python need override(be public for simple, but don't call it forever)
	virtual void doRun() {};

};

class PyApplication : public Application {
public:
	using Application::Application;

	void Initilize() override {
		PYBIND11_OVERLOAD(
			void,
			Application,
			Initilize,

		);
	}

	void Destory() override {
		PYBIND11_OVERLOAD(
			void,
			Application,
			Destory,

			);
	}

	void doRun() override {
		PYBIND11_OVERLOAD(
			void,
			Application,
			doRun,

			);
	}
};
void init_PyApplication(pybind11::module &m);


