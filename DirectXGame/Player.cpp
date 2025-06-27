#include "Player.h"

using namespace PlayerAct;

Player::Player(Camera* camera, int modelHandle) : Object(camera, ShapeType::Model) {
	handle_ = modelHandle;
}

void Player::Initialize() {
}

void Player::Update() {
	ExecuteQueue();
}
