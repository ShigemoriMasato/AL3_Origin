#pragma once
#include "Engine/Camera/Camera.h"
#include "Engine/Data/Transform.h"

class Player;

class Enemy {
public:

	Enemy() = default;
	~Enemy() = default;

	void Initialize(Camera* camera, int skullHandle, int number);
	void Update();
	void Draw() const;

	void OnCollition(Player* player);

	void SetPosition(const Vector3& position) { transform_.position = position; }
	void SetNumber(int number) { number_ = number; }

	AABB GetAABB() const;
	int GetNumber();

private:

	Transform transform_;
	Camera* camera_ = nullptr;
	int skull_ = -1;
	const float size = 1.0f;
	int number_ = 0;	//個体識別番号

	float rollZTimer_ = 0.0f;
	const float kRollZTime_ = 1.0f;
	const float kRollZAngleStart_ = 0.2f;
	const float kRollZAngleEnd_ = 0.5f;

	const float speed_ = 0.01f;
};
