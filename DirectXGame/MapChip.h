#pragma once
#include "Engine/Data/Transform.h"
#include <vector>
#include <unordered_map>

enum class MapChipType {
	blank,
	wall
};

struct IndexSet {
	uint32_t x;
	uint32_t y;
};

struct Rect;

class MapChip {
public:

	MapChip();
	~MapChip() = default;

	void Initialize(const char* filepath, int blockHandle, Camera* camera);
	void Update();
	void Draw();

	MapChipType GetMapchipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapchipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

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
