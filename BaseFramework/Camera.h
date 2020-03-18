#pragma once
#include "Vertex.h"
#include <Cmath>
#include "Matrix.h"

class Camera
{
public:
	Camera();
	Camera (float xRotation, float yRotation, float zRotation, const Vertex& position);

	Vertex GetPosition() const;
	void SetPosition(const float xPosition,const float yPosition,const float zPosition);
	Matrix GenerateViewingTransformation();

private:
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _position;
};


