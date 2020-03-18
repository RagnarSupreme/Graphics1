#include "Vertex.h"
#include "Rasteriser.h"

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 1.0f;
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

Vertex::Vertex(const Vertex& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
	_w = other.GetW();
}



float Vertex::GetX() const
{
	return _x;
}

void Vertex::SetX(const float x)
{
	_x = x;
}

float Vertex::GetY() const
{
	return _y;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

float Vertex::GetZ() const
{
	return _z;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}

float Vertex::GetW() const
{
	return _w;
}

void Vertex::SetW(const float w)
{
	_w = w;
}
Vertex& Vertex::operator=(const Vertex& rhs)
{

	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
	}
	return *this;
}

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

void Vertex::Dehomogenise()
{
	_x /= _w;
	_y /= _w;
	_z /= _w;
	_w /= _w;
}

/*
x	1 0 0 Tx 	 x
y = 0 1 0 Ty  *  y	= Translation
z	0 0 1 Tz	 z
1	0 0 0 1	     1

x	Sx 0 0 0		x
y = 0 Sy 0 0	*	y = Scaling
z	0 0 Sz 0		z
1	0 0 0  1		1

x	COS e -SIN e 0  0		x
y = SIN e COS e 0   0	*	y	= Rotation around Z
z	0	  0     1   0		z
1	0	  0		0	1		1

x	1	0	 0		0		x
y = 0	COSe -SINe  0	*	y	= Rotation around X
z	0	SINe COSe   0   0	z
1	0	0	 0		1		1

x	COSe  0 SINe 0		x
y = 0	  1 0	 0	*	y	= Rotation around Y
z	-SINe 0 COSe 0		z
1	0	  0 0	 1		1
*/