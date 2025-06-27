#include "PlayerBullet.h"
#include "Engine/Math/MyMath.h"

using namespace Matrix;

PlayerBullet::PlayerBullet(Camera* camera, Vector3 pos, Vector3 rotate) : Object(camera, ShapeType::Cube) {
	handle_ = 1;
	transform_.position = pos;
	
	velocity_ = {};
	direction_ = Vector3(0.0f, 0.0f, 1.0f) * MakeRotationMatrix(rotate);
}

void PlayerBullet::Initialize() {
	transform_.scale = { 0.3f, 0.3f, 0.3f };
	velocity_ = direction_ * speed;
}

void PlayerBullet::Update() {
	transform_.position += velocity_;

	if (transform_.position.Length() >= 100.0f) {
		isDelete_ = true;
	}
}
