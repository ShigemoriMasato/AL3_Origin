#include "Player.h"
#include "Engine/Render/Render.h"
#include "Engine/Input/Input.h"
#include "CameraController.h"
#include "Enemy.h"
#include "MapChip.h"
#include <numbers>
#include <algorithm>
#include <memory>
#include <array>

using namespace Matrix;

Player::Player() {
	deathParticle_ = new DeathParticle();
}

Player::~Player() {
	delete deathParticle_;
}

void Player::Initialize(Camera* camera, int player) {
	camera_ = camera;
	transform_ = Transform();
	transform_.position = { 1.5f, 1.5f, 0.0f };
	transform_.rotation.y = std::numbers::pi_v<float> / 2.0f;
	model_ = player;
	isRight_ = true;

	deathParticle_->Initialize(camera, player);
}

void Player::Update() {

	Move();

	CollisionMapInfo collitionMapInfo{};
	collitionMapInfo.movement = velocity_;

	CheckCollitionRoofMapChip(collitionMapInfo);		// 上
	CheckCollitionFloorMapChip(collitionMapInfo);		// 下
	CheckCollitionRightMapChip(collitionMapInfo);       // 右
	CheckCollitionLeftMapChip(collitionMapInfo);		// 左

	transform_.position += velocity_;

	SwitchLanding(collitionMapInfo);

	deathParticle_->Update();

	for (int& time : particleCooltime_) {
		if (time > 0) { 
			--time;
		}
	}

	//振り向き
	if (turnTimer_ > 0.0f) {
		turnTimer_ -= 1.0f / 60.0f;

		float destinationRotationYTable[] = { std::numbers::pi_v<float> * 3.0f / 2.0f, std::numbers::pi_v<float> / 2.0f };

		float destinationRotationY = destinationRotationYTable[isRight_];

		float t = 1.0f - turnTimer_ / kTimeTurn;

		transform_.rotation.y = beginingRotateY_ * (1.0f - t) + destinationRotationY * t;
	}
}

void Player::Draw() const {
	Render::DrawModel(model_, MakeAffineMatrix(transform_), camera_);

	deathParticle_->Draw();
}

AABB Player::GetAABB() {
	AABB ans;
	ans.min = transform_.position - Vector3(size / 2.0f, size / 2.0f, size / 2.0f);
	ans.max = transform_.position + Vector3(size / 2.0f, size / 2.0f, size / 2.0f);
	return ans;
}

void Player::OnCollition(Enemy enemy) {
	int number = enemy.GetNumber();
	bool boot = false;

	if (number >= particleCooltime_.size()) {
		boot = true;

		while(number >= particleCooltime_.size()) {
			particleCooltime_.push_back(90);
		}
	}
	else if(particleCooltime_[number] <= 0) {
		boot = true;
		particleCooltime_[number] = 90; // 再度発動可能までの時間
	}

	if (boot) {
		deathParticle_->Boot(transform_.position);
	}
}

void Player::Move() {

	//左右移動
	if (Input::GetKeyState(DIK_LEFTARROW) || Input::GetKeyState(DIK_RIGHTARROW)) {

		float acceleration = 0;

		if (Input::GetKeyState(DIK_RIGHTARROW)) {

			if (!isRight_) {
				isRight_ = true;
				beginingRotateY_ = transform_.rotation.y;
				turnTimer_ = kTimeTurn;
			}

			if (velocity_.x < 0) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration += kAcceleration;

		} else {

			if (isRight_) {
				isRight_ = false;
				beginingRotateY_ = transform_.rotation.y;
				turnTimer_ = kTimeTurn;
			}

			if (velocity_.x > 0) {
				velocity_.x *= (1.0f - kAttenuation);
			}
			acceleration -= kAcceleration;
		}

		velocity_.x += acceleration;

	} else {
		velocity_.x *= (1.0f - kAttenuation);
	}

	//速度制限
	velocity_.x = std::clamp(velocity_.x, -kRunSpeedMax, kRunSpeedMax);

	//ジャンプ処理
	if (onGround_) {

		//ジャンプ
		if (Input::GetKeyState(DIK_UPARROW)) {
			velocity_.y += kJumpSpeed;
			onGround_ = false;
		}
	}
	//空中にいるとき
	else {

		bool landing = false;

		//着地判定
		if (velocity_.y < 0) {
			if (transform_.position.y <= 1.5f + kBufferPosition) {
				landing = true;
			}
		}

		//着地後処理
		if (landing) {
			transform_.position.y = 1.5f;
			velocity_.x *= (1.0f - kAttenuation);
			velocity_.y = 0.0f;
			onGround_ = true;
		} else {
			//自由落下
			velocity_.y += -kGravityAcceleration;
			if (velocity_.y < -kFallSpeedMax) {
				velocity_.y = -kFallSpeedMax;
			}
		}
	}

}

void Player::CheckCollitionRoofMapChip(CollisionMapInfo& info) {
	std::array<Vector3, kNumCorner> positionsNew;

	//落ちていくならば処理しない
	if (info.movement.y <= 0) {
		return;
	}

	//移動後の各角度を計算
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(transform_.position + info.movement, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	bool hit = false;

	IndexSet indexSet;
	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	mapChipTypeNext = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y + 1);
	if (mapChipType == MapChipType::wall && mapChipTypeNext != MapChipType::wall) {
		hit = true;
	}

	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	mapChipTypeNext = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y + 1);
	if (mapChipType == MapChipType::wall && mapChipTypeNext != MapChipType::wall) {
		hit = true;
	}

	if (hit) {
		Vector3 top = transform_.position;
		top.y += size / 2;
		indexSet = mapChip_->GetMapChipIndexSetByPosition(top + info.movement);
		Rect rect = mapChip_->GetRectByIndex(indexSet.x, indexSet.y);
		float buffer = rect.bottom - transform_.position.y - size / 2;
		info.movement.y = buffer < 0.0f ? 0.0f : buffer;
		info.isRoof = true;
		velocity_.y = info.movement.y;
	}
}

void Player::CheckCollitionFloorMapChip(CollisionMapInfo& info) {
	if (info.movement.y >= 0) {
		return;
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	bool hit = false;
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(transform_.position + info.movement, static_cast<Corner>(i));
	}

	IndexSet indexSet;
	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	mapChipTypeNext = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y - 1);
	if (mapChipType == MapChipType::wall && mapChipTypeNext != MapChipType::wall) {
		hit = true;
	}

	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	mapChipTypeNext = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y - 1);
	if (mapChipType == MapChipType::wall && mapChipTypeNext != MapChipType::wall) {
		hit = true;
	}

	if (hit) {
		Vector3 bottom = transform_.position;
		bottom.y -= size / 2;
		indexSet = mapChip_->GetMapChipIndexSetByPosition(bottom + info.movement);
		Rect rect = mapChip_->GetRectByIndex(indexSet.x, indexSet.y);
		float buffer = rect.top - transform_.position.y + 0.5f + kBufferPosition;
		info.movement.y = buffer > 0.0f ? 0.0f : buffer;
		info.isFloor = true;
		velocity_.y = info.movement.y;
	}
}

void Player::CheckCollitionRightMapChip(CollisionMapInfo& info) {
	if (info.movement.x <= 0.0f) {
		return;
	}

	MapChipType mapChipType;
	bool hit = false;
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(transform_.position + info.movement, static_cast<Corner>(i));
	}

	IndexSet indexSet;
	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	if (mapChipType == MapChipType::wall) {
		hit = true;
	}

	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	if (mapChipType == MapChipType::wall) {
		hit = true;
	}

	if (hit) {
		Vector3 right = transform_.position;
		right.x += size / 2;
		indexSet = mapChip_->GetMapChipIndexSetByPosition(right + info.movement);
		Rect rect = mapChip_->GetRectByIndex(indexSet.x, indexSet.y);
		float buffer = rect.left - transform_.position.x - size / 2 - kBufferPosition;
		info.movement.x = buffer < 0.0f ? 0.0f : buffer;
		info.isWall = true;
		velocity_.x = info.movement.x;
	}
}

void Player::CheckCollitionLeftMapChip(CollisionMapInfo& info) {
	if (info.movement.x >= 0) {
		return;
	}

	MapChipType mapChipType;
	bool hit = false;
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(transform_.position + info.movement, static_cast<Corner>(i));
	}

	IndexSet indexSet;
	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	if (mapChipType == MapChipType::wall) {
		hit = true;
	}

	indexSet = mapChip_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
	if (mapChipType == MapChipType::wall) {
		hit = true;
	}

	if (hit) {
		Vector3 left = transform_.position;
		left.x -= size / 2;
		indexSet = mapChip_->GetMapChipIndexSetByPosition(left + info.movement);
		Rect rect = mapChip_->GetRectByIndex(indexSet.x, indexSet.y);
		float buffer = rect.right - transform_.position.x + size / 2 + kBufferPosition;
		info.movement.x = buffer > 0.0f ? 0.0f : buffer;
		info.isWall = true;
		velocity_.x = info.movement.x;
	}
}

void Player::SwitchLanding(const CollisionMapInfo& info) {
	if (onGround_) {

		///着地しているとき
		//上に向かって進んでいるとき
		if (velocity_.y > 0.0f) {

			onGround_ = false;

		} else {
			MapChipType mapChipType;
			bool hit = false;

			Vector3 bufferPosition = Vector3(0.0f, kBufferPosition + 0.3f, 0.0f);

			//下にブロックがあるかの判定
			IndexSet indexSet;
			indexSet = mapChip_->GetMapChipIndexSetByPosition(CornerPosition(transform_.position - bufferPosition, Corner::kLeftBottom));
			mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
			if (mapChipType == MapChipType::wall) {
				hit = true;
			}

			indexSet = mapChip_->GetMapChipIndexSetByPosition(CornerPosition(transform_.position - bufferPosition, Corner::kRightBottom));
			mapChipType = mapChip_->GetMapchipTypeByIndex(indexSet.x, indexSet.y);
			if (mapChipType == MapChipType::wall) {
				hit = true;
			}

			//下にブロックがなかったらfalse
			if (!hit) {
				onGround_ = false;
			}
		}

	} else {

		// 空中にいるとき
		if (info.isFloor) {
			onGround_ = true;
			velocity_.x *= (1.0f - kAttenuationLanding);
			velocity_.y = 0.0f;
		}

	}
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {
	Vector3 offsetTable[kNumCorner] = {
		center + Vector3(size / 2.0f, -size / 2.0f, 0.0f),
		center + Vector3(-size / 2.0f, -size / 2.0f, 0.0f),
		center + Vector3(size / 2.0f, size / 2.0f, 0.0f),
		center + Vector3(-size / 2.0f, size / 2.0f, 0.0f)
	};

	return offsetTable[static_cast<uint32_t>(corner)];
}
