#include "MapChip.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include "Engine/Render/Render.h"

using namespace Matrix;

MapChip::MapChip() {
	mapTransforms_.resize(blockNumHeight_);
	mapData_.resize(blockNumHeight_);
	for (uint32_t i = 0; i < blockNumHeight_; ++i) {
		mapData_[i].resize(blockNumWidth_);
		mapTransforms_[i].resize(blockNumWidth_);
	}

	mapchipTable_["0"] = MapChipType::blank;
	mapchipTable_["1"] = MapChipType::wall;
}

void MapChip::Initialize(const char* filepath, int blockHandle, Camera* camera) {
	//ファイルを開く
	std::fstream file;
	file.open(filepath);
	assert(file.is_open() && "Failed to open mapchip file.");

	//マップチップについてすべてぶちこむ
	std::stringstream mapchipCsv;
	mapchipCsv << file.rdbuf();
	file.close();

	//情報を整理する
	for (uint32_t i = 0; i < blockNumHeight_; ++i) {
		std::string line;
		getline(mapchipCsv, line);

		std::istringstream lineStream(line);
		for (uint32_t j = 0; j < blockNumWidth_; ++j) {

			std::string value;
			getline(lineStream, value, ',');
			
			if (mapchipTable_.contains(value)) {
				mapData_[i][j] = mapchipTable_[value];
			}
		}
	}

	//transformを設定する
	for (uint32_t i = 0; i < blockNumHeight_; ++i) {
		for (uint32_t j = 0; j < blockNumWidth_; ++j) {
			mapTransforms_[i][j] = {};
			mapTransforms_[i][j].position = GetPosByIndex(j, i);
		}
	}

	blockHandle_ = blockHandle;
	camera_ = camera;
}

void MapChip::Update() {
}

void MapChip::Draw() {
	for(uint32_t i = 0; i < blockNumHeight_; ++i) {
		for (uint32_t j = 0; j < blockNumWidth_; ++j) {
			if (mapData_[i][j] == MapChipType::blank) {
				continue;
			}

			Render::DrawModel(blockHandle_, MakeAffineMatrix(mapTransforms_[i][j]), camera_);
		}
	}
}

Vector3 MapChip::GetPosByIndex(int x, int y) {
	Vector3 pos;
	pos.x = x * blockSize_ - blockSize_ / 2;
	pos.y = (blockNumHeight_ - 1 - y) * blockSize_ + blockSize_ / 2;
	pos.z = 0.0f;
	return pos;
}
