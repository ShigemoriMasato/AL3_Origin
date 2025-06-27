#include "Enemy.h"
#include <numbers>

Enemy::StateFunction Enemy::stateFunc[] = {
	&Enemy::Apploach,
	&Enemy::Leave
};

Enemy::Enemy(Camera* camera, int modelHandle) : Object(camera, ShapeType::Model) {
	handle_ = modelHandle;
	
}

void Enemy::Initialize() {
	transform_.position = { 0.0f, 0.0f, 10.0f };
	transform_.rotation.y = std::numbers::pi_v<float>;
}

void Enemy::Update() {
	(this->*stateFunc[int(state_)])();

	frame_++;
	if (frame_ > 60) {
		state_ = EnemyState::Leave;
	}
	
	if (frame_ > 120) {
		isAlive_ = false;
	}
}

void Enemy::Apploach() {
	transform_.position.z -= 0.1f;
}

void Enemy::Leave() {
	transform_.position += Vector3(0.05f, 0.05f, 0.05f);
}
