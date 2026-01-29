#include "../Manager.h"
#include "../../FileSystem/FileSystem.h"
#include "../../Shader/Shader.h"

template<>
void Manager<Shader>::Init() {
	resources.emplace("basic", 
		std::move(Shader(
			FileSystem::getPath("res/shaders/basic.vs"), 
			FileSystem::getPath("res/shaders/basic.fs"))
		));
}

template class Manager<Shader>;