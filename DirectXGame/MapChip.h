#pragma once
#include "Engine/Data/Transform.h"
#include <vector>
#include <unordered_map>

enum class MapChipType {
	blank,
	wall
};

class MapChip {
public:

	MapChip();
	~MapChip();

	void Initialize(const char* filepath, int blockHandle, Camera* camera);
	void Update();
	void Draw();

private:

	Vector3 GetPosByIndex(int x, int y);

	std::vector<std::vector<MapChipType>> mapData_;
	std::vector<std::vector<Transform>> mapTransforms_;

	const float blockSize_ = 1.0f;
	const uint32_t blockNumHeight_ = 20;
	const uint32_t blockNumWidth_ = 100;

	int blockHandle_ = -1;

	Camera* camera_ = nullptr;

	std::unordered_map<std::string, MapChipType> mapchipTable_;
};
