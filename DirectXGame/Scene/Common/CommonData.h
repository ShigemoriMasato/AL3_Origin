#pragma once
#include <vector>

enum class ModelType {
	Block,
	skydome,

	ModelCount
};

enum class TextureType {

};

struct CommonData {
	std::vector<int> modelHandle_;
	std::vector<int> textureHandle_;
};
