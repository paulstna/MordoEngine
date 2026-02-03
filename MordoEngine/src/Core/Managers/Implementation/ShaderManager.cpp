#include "../Manager.h"
#include "../../FileSystem/FileSystem.h"
#include "../../Shader/Shader.h"

template<>
void Manager<Shader>::Init() {
	resources.emplace("terrain", 
		std::move(Shader(
			FileSystem::getPath("res/shaders/terrain.vs"), 
			FileSystem::getPath("res/shaders/terrain.fs"))
		));
}

template class Manager<Shader>;