#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>

namespace terrain
{

	struct HeightData
	{
		std::vector<std::uint16_t> data; // 0–65535
		std::size_t size = 0;            // width == height (NxN)
	};

	class Terrain
	{
	protected:
		HeightData p_HeightData;
		float p_HeightScale = 1.0f;
		unsigned int p_Width;
		unsigned int p_Depth;

	public:
		Terrain() = default;
		bool LoadHeightMap(const std::string& filename);
		bool SaveHeightMap(const std::string& filename) const;
		bool UnloadHeightMap() noexcept;

		float GetHeightScale() const noexcept;
		void SetHeightScale(float scale) noexcept;

		void SetScaledHeightAt(std::uint16_t height, std::size_t x, std::size_t z);
		float GetNormalizedHeightAt(std::size_t x, std::size_t z) const;
		float GetScaledHeightAt(std::size_t x, std::size_t z) const;
		std::size_t GetSize() const noexcept;
		virtual ~Terrain() = default;

	private:
		std::size_t index(std::size_t x, std::size_t z) const noexcept;
	};

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec2 texCoord;
		float height;
		void InitVertex(const Terrain& terrain, std::size_t x, std::size_t z);
	};
}
