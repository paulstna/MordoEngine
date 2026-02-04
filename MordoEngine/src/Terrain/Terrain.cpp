#include "Terrain.h"
#include "../Core/FileSystem/FileSystem.h"
#include <fstream>
#include <cassert>

using namespace terrain;

void Vertex::InitVertex(const Terrain& terrain, std::size_t x, std::size_t z)
{
	pos = glm::vec3{
		static_cast<float>(x),
		terrain.GetScaledHeightAt(x, z),
		static_cast<float>(z)
	};

	std::size_t terrainSize = terrain.GetSize();
	texCoord = glm::vec2{
		static_cast<float>(x) / static_cast<float>(terrainSize - 1),
		static_cast<float>(z) / static_cast<float>(terrainSize - 1)
	};

	height = terrain.GetNormalizedHeightAt(x,z);
}

bool Terrain::LoadHeightMap(const std::string& filename)
{
	std::ifstream file(FileSystem::getPath(filename), std::ios::binary);
	if (!file)
		return false;

	file.seekg(0, std::ios::end);
	std::streamsize fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::size_t totalElements = fileSize / sizeof(std::uint16_t);
	std::size_t size = static_cast<std::size_t>(std::sqrt(totalElements));

	if (size * size != totalElements)
	{
		std::cerr << "Not a Square!" << std::endl;
		return false;
	}

	p_HeightData.size = size;
	p_HeightData.data.resize(totalElements);

	file.read(reinterpret_cast<char*>(p_HeightData.data.data()),
		fileSize);

	return file.good();
}

bool Terrain::SaveHeightMap(const std::string& filename) const
{
	if (p_HeightData.data.empty())
		return false;

	std::ofstream file(FileSystem::getPath(filename), std::ios::binary);
	if (!file)
		return false;

	file.write(
		reinterpret_cast<const char*>(p_HeightData.data.data()),
		p_HeightData.data.size() * sizeof(std::uint16_t)
	);

	return file.good();
}

bool Terrain::UnloadHeightMap() noexcept
{
	p_HeightData.data.clear();
	p_HeightData.data.shrink_to_fit();
	p_HeightData.size = 0;
	return true;
}

float Terrain::GetHeightScale() const noexcept
{
	return p_HeightScale;
}

void Terrain::SetHeightScale(float scale) noexcept
{
	p_HeightScale = scale;
}

void Terrain::SetScaledHeightAt(std::uint16_t height, std::size_t x, std::size_t z)
{
	assert(x < p_HeightData.size && z < p_HeightData.size);
	p_HeightData.data[index(x, z)] = height;
}

float Terrain::GetNormalizedHeightAt(std::size_t x, std::size_t z) const {
	assert(x < p_HeightData.size && z < p_HeightData.size);
	std::uint16_t h = p_HeightData.data[index(x, z)];
	return static_cast<float>(h) / 65535.0f;
}

float Terrain::GetScaledHeightAt(std::size_t x, std::size_t z) const
{
	return GetNormalizedHeightAt(x, z) * p_HeightScale;
}

std::size_t Terrain::GetSize() const noexcept
{
	return p_HeightData.size;
}

std::size_t Terrain::index(std::size_t x, std::size_t z) const noexcept
{
	return z * p_HeightData.size + x;
}
