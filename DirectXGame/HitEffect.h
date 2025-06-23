#pragma once
#include "Engine/Camera/Camera.h"
#include "Engine/Log/Logger.h"
#include <vector>

class HitEffect {
public:
	HitEffect();
	~HitEffect();
	void Initialize(Camera* camera, int modelHandle_);
	void Update();
	void Draw() const;

	void Boot(Vector3 pos);

private:

	bool boot_ = false;

	std::vector<std::vector<Transform>> transforms_;
	std::vector<std::vector<Vector4>> colors_;
	std::vector<float> timer_;
	Camera* camera_ = nullptr;

	Logger* logger_ = nullptr;

	int textureHandle_ = -1;

	const float kLifeTime = 1.0f;
	const float kScaleTime = 0.2f;
};
