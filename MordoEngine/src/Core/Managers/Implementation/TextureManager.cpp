#include "../Manager.h"
#include "../../FileSystem/FileSystem.h"
#include "../../Texture/Texture.h"

template<>
void Manager<Texture>::Init() {
	resources.emplace("bricks", Texture(FileSystem::getPath("res/textures/bricks.png")));
}

template class Manager<Texture>;