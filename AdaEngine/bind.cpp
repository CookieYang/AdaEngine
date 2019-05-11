#include "Application.h"

PYBIND11_MODULE(AdaEngine, m) {
	init_PyApplication(m);
}