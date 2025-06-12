#pragma once
#include "Engine/Data/Transform.h"
#include "Engine/Log/Logger.h"
#include <vector>

class DeathParticle {
public:

	DeathParticle();
	~DeathParticle();
	void Initialize(Camera* camera, int modelHandle_);
	void Update();
	void Draw();

	void Boot(Vector3 pos);

private:

	bool boot_ = false;

	std::vector<std::vector<Transform>> transforms_;
	std::vector<std::vector<Vector4>> colors_;
	std::vector<float> timer_;
	Camera* camera_ = nullptr;

	Logger* logger_ = nullptr;

	int modelHandle_ = -1;

	const float lifeTime_ = 3.0f;
	const float speed_ = 0.01f;
};

