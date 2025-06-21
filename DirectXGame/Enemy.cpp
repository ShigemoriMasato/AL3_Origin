#include "Enemy.h"
#include "Engine/Math/MyMath.h"
#include "Engine/Render/Render.h"
#include <numbers>

void Enemy::Initialize(Camera* camera, int skull, int number) {
	camera_ = camera;
	transform_ = {};
	transform_.position = { 15.0f, 1.5f, 0.0f };
	transform_.rotation = { 0.0f, -std::numbers::pi_v<float> / 2.0f, 0.0f };
	skull_ = skull;
	number_ = number;
}

void Enemy::Update() {
	BehaviorUpdate();

	switch (behavior_) {
	case Behavior::Root:
		Move();
		break;

	case Behavior::Death:
		Death();
		break;
	}
}

void Enemy::Draw() const {
	Render::DrawModel(skull_, MakeAffineMatrix(transform_), camera_);
}

void Enemy::OnCollition(Player*) {
	behaviorRequest_ = Behavior::Death; // 死亡処理を要求
	isInvisible_ = true;
}

AABB Enemy::GetAABB() const {
	AABB aabb;
	aabb.min = transform_.position - Vector3(size / 2, size / 2, size / 2);
	aabb.max = transform_.position + Vector3(size / 2, size / 2, size / 2);
	return aabb;
}

int Enemy::GetNumber() {
	return number_;
}

void Enemy::BehaviorUpdate() {

	if (behaviorRequest_ != Behavior::Unknown) {
		BehaviorInitialize(behaviorRequest_);
		behaviorRequest_ = Behavior::Unknown;
	}
}

void Enemy::BehaviorInitialize(Behavior bh) {

	switch (bh) {
	case Behavior::Root:
		break;
	case Behavior::Death:
		deathTime_ = 0; // 死亡時間をリセット
		break;
	}

}

void Enemy::Move() {
	rollZTimer_ += 1.0f / 60.0f; // 1フレーム分の時間を加算
	if (rollZTimer_ > kRollZTime_) {
		rollZTimer_ -= kRollZTime_; // タイマーをリセット
	}

	float t = std::sinf(rollZTimer_ * 2.0f * std::numbers::pi_v<float> / kRollZTime_);

	transform_.rotation.x = kRollZAngleStart_ * (1.0f - t) + kRollZAngleEnd_ * t;

	transform_.position.x -= speed_;
}

void Enemy::Death() {
	++deathTime_;

	if (deathTime_ >= 60) {
		isDeath_ = true;
		return;
	}


}
