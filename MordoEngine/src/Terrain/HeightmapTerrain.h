#pragma once
#include "Terrain.h"
#include <string>

class HeightMapTerrain : public terrain::Terrain 
{
public:
	HeightMapTerrain(const std::string& filepath);
};
