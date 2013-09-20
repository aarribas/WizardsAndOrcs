//###############################################################################
// INTRODUCCION: Vector4.cpp
//------------------------------------------------------------------------------
// Este codigo proporciona una clase para trabajar con vectores de 4 dimensiones,
// x,y,z,w. La clase es necesaria para las operaciones con Quaternions.
//
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

// Creamos cuatro vectores basicos que utilizaremos en varias operaciones
const Vector4 Vector4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);

//##############################################################################
// Constructores de la clase

Vector4::Vector4()
{
	for(int i = 0; i < 4; i++)
		m_values[i] = 0;
}

Vector4::Vector4(const Vector4& other)
{
	for(int i = 0; i < 4; i++)
		m_values[i] = other.m_values[i];
}

Vector4::Vector4(float x, float y, float z, float w)
{
	m_values[0] = x;
	m_values[1] = y;
	m_values[2] = z;
	m_values[3] = w;
}

//##############################################################################
// Operaciones de la clase

Vector4& Vector4::operator=(const Vector4& other)
{
	for(int i = 0; i < 4; i++)
		m_values[i] = other.m_values[i];
	return *this;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(
			m_values[0] + other.m_values[0],
			m_values[1] + other.m_values[1],
			m_values[2] + other.m_values[2],
			m_values[3] + other.m_values[3]);
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	return Vector4(
			m_values[0] - other.m_values[0],
			m_values[1] - other.m_values[1],
			m_values[2] - other.m_values[2],
			m_values[3] - other.m_values[3]);
}

Vector4 Vector4::operator*(float mult) const
{
	return Vector4(
			m_values[0] * mult,
			m_values[1] * mult,
			m_values[2] * mult,
			m_values[3] * mult);
}

float Vector4::operator*(const Vector4& other) const
{
	float result = 0.0f;
	for(int i = 0; i < 4; i++)
		result += m_values[i] * other.m_values[i];
	return result;
}

Vector4 Vector4::operator^(const Vector4& other) const
{
	return Vector4(
			m_values[1] * other.m_values[2] - m_values[2] * other.m_values[1],
			m_values[2] * other.m_values[0] - m_values[0] * other.m_values[2],
			m_values[0] * other.m_values[1] - m_values[1] * other.m_values[0],
			0.0f);
}


Vector4& Vector4::operator+=(const Vector4& other)
{
	for(int i = 0; i < 4; i++)
		m_values[i] += other.m_values[i];
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	for(int i = 0; i < 4; i++)
		m_values[i] -= other.m_values[i];
	return *this;
}

Vector4& Vector4::operator*=(float mult)
{
	for(int i = 0; i < 4; i++)
		m_values[i] *= mult;
	return *this;
}

Vector4& Vector4::operator^=(const Vector4& other)
{
	Vector4 result = *this ^ other;
	for(int i = 0; i < 4; i++)
		m_values[i] = result[i];
	return *this;
}

float Vector4::len() const
{
	float result = 0.0f;
	for(int i = 0; i < 4; i++)
		result += m_values[i] * m_values[i];
	return sqrt(result);
}

void Vector4::normalize()
{
	float l = len();
	if (l != 0.0f)
		for(int i = 0; i < 4; i++)
			m_values[i] /= l;
}

Vector4 Vector4::normalize() const
{
	float l = len();
	if (l == 0.0f)
		return *this;
	else {
		float values[4];
		for(int i = 0; i < 4; i++)
			values[i] = m_values[i] / l;
		return Vector4(values[0], values[1], values[2], values[3]);
	}
}

float Vector4::distance(const Vector4& from, const Vector4& to)
{
	return Vector4(
			from[0] - to[0],
			from[1] - to[1],
			from[2] - to[2],
			from[3] - to[3])
		.len();
}

Quaternion Vector4::asOrientation(const Vector4& from) const
{
	return asOrientation(from, *this);
}

Quaternion Vector4::asOrientation(const Vector4& from, const Vector4& to)
{
	Vector4 f(from);
	Vector4 t(to);
	
	f.normalize();
	t.normalize();
	
	float cosAngle = f * t;
	
	if (fabs(cosAngle - 1.0f) < 0.001f) { // angle ~ 0
		return Quaternion::IDENTITY;
	} else if (fabs(cosAngle + 1.0f) < 0.001f) { // angle ~ PI
		Vector4 ortho;
		if (fabs(f * Vector4::UNIT_X - 1.0f) < 0.001f)
			ortho = f ^ Vector4::UNIT_X;
		else
			ortho = f ^ Vector4::UNIT_Y;
		return Quaternion(
				0.0f,
				ortho[0],
				ortho[1],
				ortho[2]);
	} else {
		float term = sqrt(2.0f + 2.0f * cosAngle);
		Vector4 axis = f ^ t;
		return Quaternion(
				0.5f * term,
				axis[0] / term,
				axis[1] / term,
				axis[2] / term);
	}
}

Vector4 Vector4::rotate(const Quaternion& orientation) const
{
	return (orientation * Quaternion(0.0f, m_values[0], m_values[1], m_values[2]) * -orientation).vector();
}

std::ostream& operator<<(std::ostream& out, const Vector4& vector)
{
	return out << "(" << vector[0] << ", " << vector[1] << ", " << vector[2] << ", " << vector[3] << ")";
}
