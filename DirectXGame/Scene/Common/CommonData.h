#pragma once
#include <vector>

enum class ModelType {
	Block,
	skydome,
	player,
	skull,

	ModelCount
};

enum class TextureType {
	block,
};

struct CommonData {
	std::vector<int> modelHandle_;
	std::vector<int> textureHandle_;
};
