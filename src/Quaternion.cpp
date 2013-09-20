//###############################################################################
// INTRODUCCION: Quaternion.cpp
//------------------------------------------------------------------------------
// Implementación de las operaciones con cuaterniones. Necesario para poder
// trabajar con rotaciones:
//   - evita gimbal lock
//   - permite interpolar entre cuaterniones
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "Quaternion.h"
#include "Vector4.h"
#include <cmath>
#include <exception>

#ifndef M_PI
#define M_PI 3.14159f
#endif


const Quaternion Quaternion::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion()
	: m_w(0.0f)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_z(0.0f)
{
}

Quaternion::Quaternion(const Quaternion& other)
	: m_w(other.m_w)
	, m_x(other.m_x)
	, m_y(other.m_y)
	, m_z(other.m_z)
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
	: m_w(w)
	, m_x(x)
	, m_y(y)
	, m_z(z)
{
}

Quaternion Quaternion::fromRotate(float degrees, float x, float y, float z)
{
	float radians = degrees * M_PI / 180.0f;
	float c = cos(radians / 2.0f);
	float s = sin(radians / 2.0f);
	return Quaternion(c, x * s, y * s, z * s);
}

Quaternion Quaternion::fromNlerp(const Quaternion& q1, const Quaternion& q2, float p)
{
	if (p > 1.0f)
		p = 1.0f;
	if (p < 0.0f)
		p = 0.0f;
	Quaternion result = (q1 + (q1 - q2) * p);
	result.normalize();
	return result;
}

float& Quaternion::operator[](int index)
{
	switch(index)
	{
	case 0: return m_w;
	case 1: return m_x;
	case 2: return m_y;
	case 3: return m_z;
	}
	return m_w; // warning!
}

float Quaternion::operator[](int index) const
{
	switch(index)
	{
	case 0: return m_w;
	case 1: return m_x;
	case 2: return m_y;
	case 3: return m_z;
	}
	return m_w; // warning!
}

Vector4 Quaternion::vector() const
{
	return Vector4(m_x, m_y, m_z);
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(
			m_w,
			- m_x,
			- m_y,
			- m_z);
}

Quaternion Quaternion::operator+(const Quaternion& other) const
{
	return Quaternion(
			m_w + other.m_w,
			m_x + other.m_x,
			m_y + other.m_y,
			m_z + other.m_z);
}

Quaternion Quaternion::operator-(const Quaternion& other) const
{
	return Quaternion(
			m_w - other.m_w,
			m_x - other.m_x,
			m_y - other.m_y,
			m_z - other.m_z);
}

Quaternion Quaternion::operator*(float p) const
{
	return Quaternion(
			m_w * p,
			m_x * p,
			m_y * p,
			m_z * p);
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
	return Quaternion(
			m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z,
			m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y,
			m_w * other.m_y + m_y * other.m_w + m_z * other.m_x - m_x * other.m_z,
			m_w * other.m_z + m_z * other.m_w + m_x * other.m_y - m_y * other.m_x);
	
}

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
	m_w += other.m_w;
	m_x += other.m_x;
	m_y += other.m_y;
	m_z += other.m_z;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
	m_w -= other.m_w;
	m_x -= other.m_x;
	m_y -= other.m_y;
	m_z -= other.m_z;
	return *this;
}

Quaternion& Quaternion::operator*=(float p)
{
	m_w *= p;
	m_x *= p;
	m_y *= p;
	m_z *= p;
	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	Quaternion result = *this * other;
	m_w = result.m_w;
	m_x = result.m_x;
	m_y = result.m_y;
	m_z = result.m_z;
	return *this;
}	

void Quaternion::normalize()
{
	float l = Vector4(m_w, m_x, m_y, m_z).len();
	m_w /= l;
	m_x /= l;
	m_y /= l;
	m_z /= l;
}

void Quaternion::getGlRotationInfo(float& angle, float& x, float& y, float& z) const
{
	angle = (2.0f * acos(m_w)) * 180.0f / M_PI;
	Vector4 v = vector();
	v.normalize();
	x = v[0];
	y = v[1];
	z = v[2];
}

std::ostream& operator<<(std::ostream& out, const Quaternion& q)
{
	return out << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3];
}
