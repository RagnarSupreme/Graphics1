#pragma once
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	int GetIndex(int) const;

	Polygon3D& operator= (const Polygon3D& rhs);

private:
	int _indices[3];
};

