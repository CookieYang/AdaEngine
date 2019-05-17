#pragma once
template <class T>
struct  GetSimpleTypeT
{
	typedef T type_t;
};

template <class T>
struct GetSimpleTypeT<T &>
{
	typedef T type_t;
};

template <class T>
struct GetSimpleTypeT<T const>
{
	typedef T type_t;
};