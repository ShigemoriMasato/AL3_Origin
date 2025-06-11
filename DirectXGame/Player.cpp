#include "Player.h"
#include "Engine/Render/Render.h"
#include "Engine/Input/Input.h"
#include <numbers>
#include <algorithm>

using namespace Matrix;

void Player::Initialize(Camera* camera, int player) {
	camera_ = camera;
	transform_ = Transform();
	transform_.position = { 1.5f, 1.5f, 0.0f };
	transform_.rotation.y = std::numbers::pi_v<float> / 2.0f;
	model_ = player;
	isRight_ = true;
}

void Player::Update() {

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
			if (transform_.position.y <= 1.5f) {
				landing = true;
			}
		}

		//着地後処理
		if (landing) {
			transform_.position.y = 1.0f + size / 2;
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

	transform_.position.x += velocity_.x;
	transform_.position.y += velocity_.y;
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
}
