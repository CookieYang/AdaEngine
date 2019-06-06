#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/quaternion.hpp"
#include "pybind11.h"

namespace DMath {
	void FPU_MatrixF_x_MatrixF(const float *a, const float *b, float *r);

	//template <typename T> T LERP(T x, T y, float z) { return (x + (y - x)*z); }
	template <typename T> T Clamp(T x, T y, T z) { return ((x < y) ? y : ((x > z) ? z : x)); }
	template <typename T> T max(T x, T y) { return (x > y) ? x : y; }
	template <typename T> T min(T x, T y) { return (x < y) ? x : y; }
	template <typename T> bool IsWithin(T x, T y, T z) { return (x >= y) && (x <= z); }

	struct matrix_t;
	struct vec_t
	{
	public:
		float x, y, z, w;

		void Lerp(const vec_t& v, float t);
		void Set(float v);
		void Set(float _x, float _y, float _z = 0.f, float _w = 0.f);

		vec_t& operator -= (const vec_t& v);
		vec_t& operator += (const vec_t& v);
		vec_t& operator *= (const vec_t& v);
		vec_t& operator *= (float v);

		vec_t operator * (float f) const;
		vec_t operator - () const;
		vec_t operator - (const vec_t& v) const;
		vec_t operator + (const vec_t& v) const;
		vec_t operator * (const vec_t& v) const;

		const vec_t& operator + () const;
		float Length() const;
		float LengthSq() const;
		vec_t Normalize();
		vec_t Normalize(const vec_t& v);
		vec_t Abs() const;
		void Cross(const vec_t& v);
		void Cross(const vec_t& v1, const vec_t& v2);
		float Dot(const vec_t &v) const;
		float Dot3(const vec_t &v) const;

		void Transform(const matrix_t& matrix);
		void Transform(const vec_t & s, const matrix_t& matrix);

		void TransformVector(const matrix_t& matrix);
		void TransformPoint(const matrix_t& matrix);
		void TransformVector(const vec_t& v, const matrix_t& matrix);
		void TransformPoint(const vec_t& v, const matrix_t& matrix);

		float& operator [] (size_t index);
		const float& operator [] (size_t index) const;
	};

	vec_t makeVect(float _x, float _y, float _z = 0.f, float _w = 0.f);
	vec_t makeVect(glm::vec2 v);
	vec_t Normalized(const vec_t& v);
	vec_t TransformPoint(const vec_t& v, const matrix_t& mat);

	vec_t Cross(const vec_t& v1, const vec_t& v2);

	float Dot(const vec_t &v1, const vec_t &v2);

	vec_t BuildPlan(const vec_t & p_point1, const vec_t & p_normal);

	struct matrix_t
	{
	public:

		union
		{
			float m[4][4];
			float m16[16];
			struct
			{
				vec_t right, up, dir, position;
			} v;
			vec_t component[4];
		};

		matrix_t(const matrix_t& other);
		matrix_t() {}
		glm::mat4 toGLM();
		operator float * ();
		operator const float* () const;
		void Translation(float _x, float _y, float _z);
		void Translation(const vec_t& vt);
		float* data();

		void Scale(float _x, float _y, float _z);
		void Scale(const vec_t& s);

		matrix_t& operator *= (const matrix_t& mat);
		matrix_t operator * (const matrix_t& mat) const;

		void Multiply(const matrix_t &matrix);
	
		void Multiply(const matrix_t &m1, const matrix_t &m2);

		float GetDeterminant() const;

		float Inverse(const matrix_t &srcMatrix, bool affine = false);
		void SetToIdentity();
		void Transpose();

		void RotationAxis(const vec_t & axis, float angle);

		void OrthoNormalize();
	};
	void composeMat(matrix_t& mat, const vec_t &pos, const vec_t &scale, const vec_t &rot);
	void decomposeMat(matrix_t mat, vec_t &pos, vec_t &scale, vec_t &rot);
};

void init_DMath(pybind11::module& m);

