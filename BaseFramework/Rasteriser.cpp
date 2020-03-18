#include "Rasteriser.h"
#include "Math.h"
#include "MD2Loader.h"
#include "Bitmap.h"

Rasteriser app;

bool Rasteriser::Initialise()
{
	if (!MD2Loader::LoadModel("cube.md2", _model,
		&Model::AddPolygon, &Model::AddVertex))
	{
		return false;
	}

	return true;
	
}





void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_perspectiveMatrix = { d / aspectRatio, 0, 0, 0,
							0, d, 0, 0,
							0, 0, d, 0,
							0, 0, 1, 0 };
}

void Rasteriser::GenerateViewMatrix(float d, float width, float height)
{
	_viewMatrix = { width / 2.0f, 0, 0, width / 2.0f,
					0, -height / 2.0f, 0, height / 2.0f,
					0, 0, d / 2.0f, d / 2.0f,
					0, 0, 0, 1 };
}



void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	vector <Vertex> vertices = _model.GetVertices();
	vector <Polygon3D> polygons = _model.GetPolygons();

	for (int i = 0; i < _model.GetPolygonCount(); i++)
	{
		
		HPEN pen = CreatePen(int(PS_SOLID), 1, RGB(0, 0, 0));
		HGDIOBJ deletepen = SelectObject(hdc, pen);
		MoveToEx(hdc, static_cast<int> (vertices[polygons[i].GetIndex(2)].GetX()), static_cast<int> (vertices[polygons[i].GetIndex(2)].GetY()), NULL);
		LineTo(hdc, static_cast<int> (vertices[polygons[i].GetIndex(0)].GetX()), static_cast<int> (vertices[polygons[i].GetIndex(0)].GetY()));
		LineTo(hdc, static_cast<int> (vertices[polygons[i].GetIndex(1)].GetX()), static_cast<int> (vertices[polygons[i].GetIndex(1)].GetY()));
		LineTo(hdc, static_cast<int> (vertices[polygons[i].GetIndex(2)].GetX()), static_cast<int> (vertices[polygons[i].GetIndex(2)].GetY()));
		SelectObject(hdc, deletepen);
		DeleteObject(pen);
	}
	
}

Matrix Rasteriser::TranslationMatrix(float Tx, float Ty, float Tz)
{
	return
	{
		1,0,0,Tx,
		0,1,0,Ty,
		0,0,1,Tz,
		0,0,0,1
	};
}

Matrix Rasteriser::ScalingMatrix(float Sx, float Sy, float Sz)
{
	return
	{
		Sx,0,0,0,
		0,Sy,0,0,
		0,0,Sz,0,
		0,0,0,1
	};
}

Matrix Rasteriser::RotationMatrixX(float Rax)
{
	return
	{
		1, 0, 0, 0,
			0,static_cast<float>(cos(Rax)),static_cast<float>(sin(Rax)), 0,
			0, static_cast<float>(-sin(Rax)), static_cast<float>(cos(Rax)), 0,
			0, 0, 0, 1
	};
}
Matrix Rasteriser::RotationMatrixY(float Ray)
{
	return
	{
		static_cast<float>(cos(Ray)), 0, static_cast<float>(-sin(Ray)), 0,
			0, 1, 0, 0,
			static_cast<float>(sin(Ray)), 0,static_cast<float>(cos(Ray)), 0,
			0, 0, 0, 1
	};
}
Matrix Rasteriser::RotationMatrixZ(float Raz)
{
	return
	{
		static_cast<float>(cos(Raz)),static_cast<float>(sin(Raz)), 0, 0,
			static_cast<float>(-sin(Raz)), static_cast<float>(cos(Raz)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};
}

void Rasteriser::Update(const Bitmap& bitmap)
{
	float radians = 3.14f / 180.0f;
	float _xTranslation = 0.0f;
	float _yTranslation = 0.0f;
	float _zTranslation = 0.0f;
	float _yScaling = 1.0f;
	float _xScaling = 1.0f;
	float _zScaling = 1.0f;
	float _xRotations = 0.0f;
	float _yRotations = 1.0f;
	float _zRotations = 0.0f;
	_formedModel = TranslationMatrix(_xTranslation, _yTranslation, _zTranslation) * RotationMatrixX(_xRotations * radians) *
		RotationMatrixY(_yRotations * radians) * RotationMatrixZ(_zRotations * radians) * ScalingMatrix(_xScaling, _yScaling, _zScaling);

	GeneratePerspectiveMatrix(1, static_cast<float>(bitmap.GetWidth()) / static_cast<float>(bitmap.GetHeight()));
	GenerateViewMatrix(1, static_cast<float>(bitmap.GetWidth()), static_cast<float> (bitmap.GetHeight()));
}

void Rasteriser::Render(const Bitmap& bitmap)
{
	HDC hdc = bitmap.GetDC();
	bitmap.Clear(RGB(255, 255, 255));

	_model.ApplyTransformToLocalVertices(_formedModel);
	_model.ApplyTransformToTransformedVertices(_camera.GenerateViewingTransformation());
	_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
	_model.DehomogeniseVertices();
	_model.ApplyTransformToTransformedVertices(_viewMatrix);
	DrawWireFrame(bitmap);
}

