#include "HeightMapTerrain.h"
#include <iostream>

HeightMapTerrain::HeightMapTerrain(const std::string& filepath)
{
	if (!LoadHeightMap(filepath)){
		std::cerr << "Error: Failed to load heightmap" << filepath << std::endl;
	}
}