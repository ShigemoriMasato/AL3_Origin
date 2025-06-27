#include "EnemyBullet.h"
#include "Engine/Math/MyMath.h"
#include <numbers>

using namespace Matrix;

EnemyBullet::EnemyBullet(Camera* camera, Vector3 pos, Vector3 rotate) : Object(camera, ShapeType::Cube) {
	handle_ = 1;
	transform_.position = pos;
	velocity_ = {};
	rotate.x -= std::numbers::pi_v<float>; // Y軸回転を反転
	direction_ = Vector3(0.0f, 0.0f, -1.0f) * MakeRotationMatrix(rotate);
	color = 0xffff;//青
}

void EnemyBullet::Initialize() {
	transform_.scale = { 0.3f, 0.3f, 0.3f };
	velocity_ = direction_ * speed;
}

void EnemyBullet::Update() {
	transform_.position += velocity_;

	++frame_;
	if (frame_ > 300) {
		isDelete_ = true;
	}
}
