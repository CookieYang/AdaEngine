#pragma once
#include "pybind11.h"
#include "RefCountedPtr.h"

PYBIND11_DECLARE_HOLDER_TYPE(T, RefCountedPtr<T>, true);
// Make pybind11 aware of the non-standard getter member function
namespace pybind11 {
	namespace detail {
		template <typename T>
		struct holder_helper<RefCountedPtr<T>> {
			static const T *get(const RefCountedPtr<T> &p) { return p.get(); }
		};
	}
}