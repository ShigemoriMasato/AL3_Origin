#include "EnemyBullet.h"
#include "Engine/Math/MyMath.h"
#include <numbers>

using namespace Matrix;

EnemyBullet::EnemyBullet(Camera* camera, Vector3 pos, Object* target) : Object(camera, ShapeType::Cube) {
	handle_ = 1;
	transform_.position = pos;
	velocity_ = {};
	Vector3 targetpos = target->GetTransform().position;
	direction_ = targetpos - transform_.position;
	direction_ = direction_.Normalize();
	color = 0xffff;//青
}

void EnemyBullet::Initialize() {
	transform_.scale = { 0.2f, 0.3f, 1.0f };
	velocity_ = direction_ * speed;
	//targetへ-Zが向くように調整
	float yaw = std::atan2(direction_.x, direction_.z);
	float pitch = std::atan2(-direction_.y, std::sqrt(direction_.x * direction_.x + direction_.z * direction_.z));

	transform_.rotation = { pitch, yaw, 0.0f };
}

void EnemyBullet::Update() {
	transform_.position += velocity_;

	++frame_;
	if (frame_ > 300) {
		isDelete_ = true;
	}
}
