//###############################################################################
// INTRODUCCION: Vector4.h
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

#ifndef __Vector4__
#define __Vector4__

#include <iostream>

class Quaternion;

class Vector4
{
//##############################################################################
// Constantes de la clase
public:
	static const Vector4 ZERO;
	static const Vector4 UNIT_X;
	static const Vector4 UNIT_Y;
	static const Vector4 UNIT_Z;
	
//##############################################################################
// Constructores de la clase
public:
	Vector4();
	Vector4(const Vector4& other);
	Vector4(float x, float y, float z, float w = 0.0f);
	
//##############################################################################
// Operaciones de la clase
public:
	Vector4& operator=(const Vector4& other);
	float& operator[](int i) { return m_values[i]; }
	float operator[](int i) const { return m_values[i]; }
	
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator*(float mult) const;
	float operator*(const Vector4& other) const;	// dot product
	Vector4 operator^(const Vector4& other) const;	// cross product

	Vector4& operator+=(const Vector4& other);
	Vector4& operator-=(const Vector4& other);
	Vector4& operator*=(float mult);
	Vector4& operator^=(const Vector4& other);
	
	float len() const;
	void normalize();
	Vector4 normalize() const;
	static float distance(const Vector4& from, const Vector4& to);
	
	Quaternion asOrientation(const Vector4& from) const;
	static Quaternion asOrientation(const Vector4& from, const Vector4& to);
	Vector4 rotate(const Quaternion& orientation) const;
	
private:
	float m_values[4];
};

std::ostream& operator<<(std::ostream& out, const Vector4& vector);

#endif // __Vector4__