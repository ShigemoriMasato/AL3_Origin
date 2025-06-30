#pragma once
#include "Engine/Camera/Camera.h"
#include <memory>

class RailCameraController {
public:

	RailCameraController(Camera* camera = nullptr);
	~RailCameraController() = default;
	void Initialize();
	void Update();
	Camera GetCamera() { return *camera_; }
	Camera* GetCameraPtr() { return camera_.get(); }

private:

	std::shared_ptr<Camera> camera_;

	std::shared_ptr<Transform> transform_;
};
