#pragma once
#include "Engine/Camera/Camera.h"
#include <memory>

class RailCameraController {
public:

	RailCameraController(Camera* camera);
	~RailCameraController() = default;
	void Initialize();
	void Update();

private:

	Camera* camera_ = nullptr;

	std::shared_ptr<Transform> transform_;
};
