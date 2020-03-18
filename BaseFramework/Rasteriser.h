#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "Camera.h"


class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(const Bitmap& bitmap);
	void Render(const Bitmap& bitmap);
	Matrix modelTransformation;

	Matrix perspectiveTransformation;
	
	Matrix screenViewTransformation;

	Matrix TranslationMatrix(float Tx, float Ty, float Tz);
	Matrix ScalingMatrix(float Sx, float Sy, float Sz);
	Matrix RotationMatrixX(float Rax);
	Matrix RotationMatrixY(float Ray);
	Matrix RotationMatrixZ(float Raz);
	Matrix _translationMatrix;
	Matrix _scallingMatrix;
	Matrix _rotationMatrixX;
	Matrix _rotationMatrixY;
	Matrix _rotationMatrixZ;
	Vertex vertices[4];
	Matrix transform;
private:
	//void DrawBox(HDC hdc, Vertex vertices[]);
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, float width, float height);
	Camera _camera;
	void DrawWireFrame(const Bitmap &bitmap);
	Matrix _perspectiveMatrix;
	Model _model;
	Matrix _formedModel;
	Matrix _viewMatrix;

	
	//Translation Matrix Values
	float Tx = 0;
	float Ty = 0;
	float Tz = 0;
	//Scale Matrix Values
	float Sx = 1;
	float Sy = 1;
	float Sz = 1;
	//Rotation Matrix Values
	float Rax = 1;
	float Ray = 1;
	float Raz = 1;
	//Update
	float _xTranslate = 0;
	float _yTranslate = 0;
	float _zTranslate = 0;
	float _xScale = 1;
	float _yScale = 1;
	float _zScale = 1;
	float _xRotation = 0.0f;
	float _yRotation = 0.0f;
	float _zRotation = 0.0f;

};