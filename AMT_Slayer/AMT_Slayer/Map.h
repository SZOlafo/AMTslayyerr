#pragma once
#include "Repository.cpp"
class Map
{
private:
	const vector3d _MapPoints[500];

public:

	static void drawMap();
	bool isOccupied();

};


