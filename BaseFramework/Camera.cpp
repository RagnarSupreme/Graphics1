#include "Camera.h"

Camera::Camera()
{
	_xRotation = 0.0f;
	_yRotation = 0.0f;
	_zRotation = 0.0f;
	_position = Vertex( 0.0f, 0.0f, -50.0f);
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;
}


Vertex Camera::GetPosition() const
{
	return _position;
}

void Camera::SetPosition(const float xPosition,const float yPosition,const float zPosition)
{
	_position = Vertex(xPosition,yPosition,zPosition);
}

Matrix Camera::GenerateViewingTransformation()
{
	Matrix cameraRotationX = {
		1, 0, 0, 0,
		0, static_cast<float>(cos(_xRotation)),static_cast<float> (sin(_xRotation)), 0,
		0,static_cast<float>(-sin(_xRotation)), static_cast<float>(cos(_xRotation)), 0,
		0, 0, 0, 1 };
	Matrix cameraRotationY ={ 
		static_cast<float>(cos(_yRotation)), 0,static_cast<float>( -sin(_yRotation)), 0,
		0, 1, 0, 0,
		static_cast<float>(sin(_yRotation)), 0, static_cast<float>(cos(_yRotation)), 0,
		0, 0, 0, 1};
	Matrix cameraRotationZ = {
		static_cast<float>(cos(_zRotation)),static_cast<float>( sin(_zRotation)), 0, 0,
		static_cast<float>( -sin(_zRotation)), static_cast<float>(cos(_zRotation)), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1};
	Matrix cameraMovement = {
		1, 0, 0, -_position.GetX(),
		0, 1, 0, -_position.GetY(),
		0, 0, 1, -_position.GetZ(),
		0, 0, 0, 1};

	Matrix generateCameraMatrix = cameraMovement * cameraRotationX * cameraRotationY * cameraRotationZ;

	return generateCameraMatrix;
}