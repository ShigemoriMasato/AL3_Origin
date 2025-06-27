#include "Enemy.h"
#include <numbers>

Enemy::Enemy(Camera* camera, int modelHandle) : Object(camera, ShapeType::Model) {
	handle_ = modelHandle;
	
}

void Enemy::Initialize() {
	transform_.position = { 1.0f, 0.0f, 10.0f };
	transform_.rotation.y = std::numbers::pi_v<float>;
	state_ = std::make_shared<EnemyStateApploach>(this);
	fireCooltime_ = 0;
}

void Enemy::Update() {
	state_->Execute();

	frame_++;
	
	if (frame_ > 200) {
		isAlive_ = false;
	}

	--fireCooltime_;
	if (fireCooltime_ < 0) {
		fireCooltime_ = fireCooltimeMax;
		// 弾を発射
		EnemyBullet bullet = EnemyBullet(camera_, transform_.position, transform_.rotation);
		bullet.Initialize();
		bullets_.push_back(bullet);
	}

	for (int i = 0; i < bullets_.size(); ++i) {
		bullets_[i].Update();
		if (bullets_[i].GetIsDelete()) {
			bullets_.erase(bullets_.begin() + i--);
		}
	}
}

void Enemy::Draws() {
	Draw();

	for (const auto& bullet : bullets_) {
		bullet.Draw();
	}
}

std::shared_ptr<EnemyState> Enemy::Down() {
	return state_->Down();
}

std::shared_ptr<EnemyState> Enemy::Up() {
	return state_->Up();
}

void Enemy::MovePosition(Vector3 velocity) {
	transform_.position += velocity;
}

std::shared_ptr<EnemyState> EnemyStateApploach::Down() {
	return std::make_shared<EnemyStateLeave>(enemy_);
}

std::shared_ptr<EnemyState> EnemyStateApploach::Up() {
	return std::shared_ptr<EnemyState>(this); // 変化なし
}

void EnemyStateApploach::Execute() {
	enemy_->MovePosition(Vector3(0.0f, 0.0f, -0.05f));
}

std::shared_ptr<EnemyState> EnemyStateLeave::Down() {
	return std::shared_ptr<EnemyState>(this); // 変化なし
}

std::shared_ptr<EnemyState> EnemyStateLeave::Up() {
	return std::make_shared<EnemyStateApploach>(enemy_);
}

void EnemyStateLeave::Execute() {
	enemy_->MovePosition(Vector3(0.05f, 0.05f, 0.05f));
}
