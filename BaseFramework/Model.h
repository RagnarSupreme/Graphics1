#pragma once
#include "Vertex.h"
#include "Polygon3D.h"
#include <vector>
#include "Matrix.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();

	//accessors
	vector<Polygon3D>& GetPolygons();
	vector<Vertex>& GetVertices();
	vector<Vertex>& GetTransformedVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	
	void DehomogeniseVertices();
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);
	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);

private:
	vector<Polygon3D> _polygons;
	vector<Vertex> _vertices;
	vector<Vertex> _transformedVertices;
};

