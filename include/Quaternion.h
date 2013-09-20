//###############################################################################
// INTRODUCCION: Quaternion.h
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

#ifndef __Quaternion__
#define __Quaternion__

#include <iostream>

class Vector4;

class Quaternion
{
public:
	static const Quaternion IDENTITY;
	
public:
	//Constructores del quaternion
	Quaternion();
	Quaternion(const Quaternion& other);
	Quaternion(float w, float x, float y, float z);

public:
	//Otras funciones para inicializar un Quaternion a partir de un eje y un angulo
	static Quaternion fromRotate(float degrees, float x, float y, float z);
	static Quaternion fromNlerp(const Quaternion& q1, const Quaternion& q2, float p);

public:
	float& operator[](int index);
	float operator[](int index) const;
	Vector4 vector() const;
	Quaternion operator-() const;
	Quaternion operator+(const Quaternion& other) const;
	Quaternion operator-(const Quaternion& other) const;
	Quaternion operator*(float p) const;
	Quaternion operator*(const Quaternion& other) const;
	
	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator-=(const Quaternion& other);
	Quaternion& operator*=(float p);
	Quaternion& operator*=(const Quaternion& other);
	
	void normalize();
	
	void getGlRotationInfo(float& angle, float& x, float& y, float& z) const;
	
private:
	float m_w;
	float m_x;
	float m_y;
	float m_z;
};

std::ostream& operator<<(std::ostream& out, const Quaternion& q);

#endif // __Quaternion__
