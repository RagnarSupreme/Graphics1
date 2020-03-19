#include "Model.h"
#include "Vertex.h"
#include "Rasteriser.h"

Model::Model()
{
}

Model::~Model()
{
}

vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}

vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetVertexCount() const
{
	return _vertices.size();
}


void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));
}

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
}

void Model::ApplyTransformToLocalVertices(const Matrix& transform)
{

	_transformedVertices.clear();
    for (size_t i = 0; i < GetVertexCount(); i++)
    {
        _transformedVertices.push_back(transform * _vertices[i]);
    }
}

void Model::ApplyTransformToTransformedVertices(const Matrix& transform)
{
	for (Vertex& vertex : _transformedVertices)
	{
		vertex = transform * vertex;
	}
}

void Model::DehomogeniseVertices()
{
	for (Vertex& vertex : _transformedVertices)
	{
		vertex.Dehomogenise();
	}
}