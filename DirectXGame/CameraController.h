#pragma once
#include "Engine/Camera/Camera.h"
#include "Engine/Math/MyMath.h"

class Player;

struct Rect {
	float left;
	float right;
	float top;
	float bottom;
};

class CameraController {
public:

	CameraController();
	~CameraController();

	void Initialize(Rect area);
	void Update();

	void Reset();

	Camera* GetCamera() { return camera_; }
	void SetTarget(Player* target) { target_ = target; }
	void SetMatrix(Camera* camera) {
		*camera_ = *camera;
	}

	void SetMovableArea(Rect area) { movableArea_ = area; }

private:

	Player* target_ = nullptr;
	Vector3 targetOffset_ = { 0.0f, 1.8f, -32.0f };
	Vector3 targetPos_ = { 0.0f, 0.0f, 0.0f };
	static inline const float kInterpolationRate = 0.1f;
	float lerpRatio_ = 0.0f;

	static inline const float kVelocityBias = 5.0f;

	Camera* camera_ = nullptr;
	Vector3 camerapos_ = { 0.0f, 0.0f, 0.0f };
	Rect movableArea_ = { 0.0f, 0.0f, 0.0f, 0.0f };
	static inline const Rect kMargin = { -16.0f, 16.0f, 8.0f, -8.0f };

};

