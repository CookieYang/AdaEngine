#pragma once
#include <cassert>
#include <atomic>
#include <iostream>

class RefCountable {
public:
	int addRef() {
		return	++refCount;
	}
	int decRef() {
		int r =	--refCount;
		assert(r >= 0);
		if (r == 0) {
			delete this;
		}
		return r;
	}
	int getRefCount() const {
		return refCount;
	}

protected:
	RefCountable():refCount(0) {};
	virtual ~RefCountable() { 
		assert(refCount == 0); 
	};
private:
	std::atomic_long refCount;
	RefCountable(const RefCountable&);
	RefCountable& operator = (const RefCountable&);
};

template <class T>
class RefCountedPtr {
public:
	RefCountedPtr() : rawPtr(nullptr) {};
	RefCountedPtr(T* ptr) : rawPtr(ptr) {
		if (rawPtr) {
			rawPtr->addRef();
		}
	}
	RefCountedPtr(const RefCountedPtr<T> &sour) : rawPtr(sour.rawPtr) {
		if (rawPtr) {
			rawPtr->addRef();
		}
	}
	RefCountedPtr& operator =(const RefCountedPtr<T> &right) {
		if (this != &right) {
			if (rawPtr != nullptr) {
				rawPtr->decRef();
			}
			rawPtr = right.rawPtr;
			if (rawPtr) {
				rawPtr->addRef();
			}
		}
		return *this;
	}
	~RefCountedPtr() {
		if (rawPtr != 0) {
			rawPtr->decRef();
		}
	}
	T& operator*() const { return *rawPtr; }
	T* operator->() const { return (&**this); }
	
	friend bool operator ==(const RefCountedPtr<T> &left, const RefCountedPtr<T> &right) {
		return (left.rawPtr == right.rawPtr);
	}

	friend bool operator !=(const RefCountedPtr<T> &left, const RefCountedPtr<T> &right) {
		return (left.rawPtr != right.rawPtr);
	}

	friend bool operator <(const RefCountedPtr<T> &left, const RefCountedPtr<T> &right) {
		return (left.rawPtr < right.rawPtr);
	}

	friend bool operator >(const RefCountedPtr<T> &left, const RefCountedPtr<T> &right) {
		return (left.rawPtr > right.rawPtr);
	}

	friend bool operator <=(const RefCountedPtr<T> &left, const RefCountedPtr<T> &right) {
		return (left.rawPtr <= right.rawPtr);
	}

	friend bool operator >=(const RefCountedPtr<T> &left, const RefCountedPtr<T> &right) {
		return (left.rawPtr >= right.rawPtr);
	}

	bool isNull() const { return rawPtr == nullptr; }
	bool isValid() const { return rawPtr != nullptr; }

	T* get() const { return rawPtr; }

	void reset(T* ptr = nullptr) {
		if (ptr != nullptr) {
			ptr->addRef();
		}
		if (rawPtr != nullptr) {
			rawPtr->decRef();
		}
		rawPtr = ptr;
	}
private:
	T* rawPtr;
};