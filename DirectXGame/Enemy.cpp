#include "Enemy.h"
#include "Engine/Math/MyMath.h"
#include "Engine/Render/Render.h"
#include <numbers>

void Enemy::Initialize(Camera* camera, int skull) {
	camera_ = camera;
	transform_ = {};
	transform_.position = { 15.0f, 1.5f, 0.0f };
	transform_.rotation = { 0.0f, -std::numbers::pi_v<float> / 2.0f, 0.0f };
	skull_ = skull;
}

void Enemy::Update() {
	rollZTimer_ += 1.0f / 60.0f; // 1フレーム分の時間を加算
	if (rollZTimer_ > kRollZTime_) {
		rollZTimer_ -= kRollZTime_; // タイマーをリセット
	}

	float t = std::sinf(rollZTimer_ * 2.0f * std::numbers::pi_v<float> / kRollZTime_);

	transform_.rotation.x = kRollZAngleStart_ * (1.0f - t) + kRollZAngleEnd_ * t;

	transform_.position.x -= speed_;
}

void Enemy::Draw() const {
	Render::DrawModel(skull_, MakeAffineMatrix(transform_), camera_);
}
