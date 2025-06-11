#pragma once
#include "Engine/Math/MyMath.h"
#include "Engine/Data/Transform.h"

class Player {
public:

	Player() = default;
	~Player() = default;

	void Initialize(Camera* camera, int player);
	void Update();
	void Draw() const;

private:

	void Move();

	Transform transform_;
	Camera* camera_ = nullptr;

	int model_;
	const float size = 1.0f;

	Vector2 velocity_;
	const float kAttenuation = 0.1f; // 減衰率
	const float kAcceleration = 0.01f; // 加速度
	const float kRunSpeedMax = 0.2f; // 最大速度

	float beginingRotateY_ = 0.0f;
	float turnTimer_ = 0;
	const float kTimeTurn = 0.2f; // 回転にかかる時間
	bool isRight_; // 右向きかどうか

	bool onGround_;
	const float kJumpSpeed = 0.5f; // ジャンプ速度
	const float kGravityAcceleration = 0.01f; // 重力加速度
	const float kFallSpeedMax = 1.0f; // 最大落下速度
};

