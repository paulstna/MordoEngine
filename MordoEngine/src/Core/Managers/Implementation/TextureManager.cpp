#include "../Manager.h"
#include "../../FileSystem/FileSystem.h"
#include "../../Texture/Texture.h"

template<>
void Manager<Texture>::Init() {
	resources.emplace("grass", Texture(FileSystem::getPath("res/textures/grass_low.png")));
	resources.emplace("dirt", Texture(FileSystem::getPath("res/textures/dirt_mid.jpg")));
	resources.emplace("rock", Texture(FileSystem::getPath("res/textures/rock_high.png")));
}

template class Manager<Texture>;