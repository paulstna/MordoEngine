#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>

template<typename T>
class Manager
{
public:
	static void Init();

	static T& Get(const std::string& resourceID){
		auto it = resources.find(resourceID);
		if (it == resources.end())
			throw std::runtime_error("Resource not found: " + resourceID);

		return it->second;
	}

	static bool Exists(const std::string& resourceID) {
		return resources.find(resourceID) != resources.end();
	}

	static void Clear() {
		resources.clear();
	}

private:
	inline static std::unordered_map<std::string, T> resources{};
	Manager() = delete;
};
