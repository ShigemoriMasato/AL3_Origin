#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(Camera* camera, Vector3 pos) : Object(camera, ShapeType::Cube) {
	handle_ = 1;
	transform_.position = pos;
}

void PlayerBullet::Initialize() {
	transform_.scale = { 0.1f, 0.1f, 0.1f };
}

void PlayerBullet::Update() {

}
