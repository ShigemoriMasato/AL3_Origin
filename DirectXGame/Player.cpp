#include "Player.h"
#include "Engine/Input/Input.h"
#include "externals/imgui/imgui.h"
#include <algorithm>
#include <numbers>

Player::Player(Camera* camera, int modelHandle, int bullethandle) : Object(camera, ShapeType::Model) {
	handle_ = modelHandle;
	bulletModelHandle_ = bullethandle;
	transform_->rotation.y = std::numbers::pi_v<float>;
	tag = "Player";
}

void Player::Initialize() {
	transform_->position = { 0.0f, 0.0f, 20.0f };
}

void Player::Update() {

	velocity_ = {};

	if (Input::GetKeyState(DIK_W)) {
		velocity_.y += 0.1f;
	}

	if (Input::GetKeyState(DIK_S)) {
		velocity_.y -= 0.1f;
	}

	if (Input::GetKeyState(DIK_A)) {
		velocity_.x -= 0.1f;
	}

	if (Input::GetKeyState(DIK_D)) {
		velocity_.x += 0.1f;
	}

	if (Input::GetKeyState(DIK_Q)) {
		transform_->rotation.y -= 0.05f;
	}

	if (Input::GetKeyState(DIK_E)) {
		transform_->rotation.y += 0.05f;
	}

	transform_->position += velocity_;

	ImGui::Begin("player");
	ImGui::DragFloat3("Position", &transform_->position.x, 0.1f);
	ImGui::End();

	transform_->position.x = std::clamp(transform_->position.x, -7.2f, 7.2f);
	transform_->position.y = std::clamp(transform_->position.y, -4.0f, 4.0f);

	if (cooltime_ > 0) {
		--cooltime_;
	}
	
	screenTransform_ = MakeAffineMatrix(*transform_) * MakeScaleMatrix(camera_->GetTransform().scale) * Inverse(MakeRotationMatrix(camera_->GetTransform().rotation)) * MakeTranslationMatrix(camera_->GetTransform().position);

	if (cooltime_ <= 0 && Input::GetKeyState(DIK_SPACE)) {
		cooltime_ = maxCooltime_;
		// プレイヤーの弾を発射
		Vector3 rotate = transform_->rotation - camera_->GetTransform().rotation;
		rotate.y -= std::numbers::pi_v<float>;
		Vector3 position = { screenTransform_.m[3][0], screenTransform_.m[3][1], screenTransform_.m[3][2] };
		std::shared_ptr<PlayerBullet> bullet = std::make_shared<PlayerBullet>(camera_, position, rotate, bulletModelHandle_);
		bullet->Initialize();
		bullets_.push_back(bullet);
	}

	for (int i = 0; i < bullets_.size(); ++i) {
		bullets_[i]->Update();
		if (!bullets_[i]->GetIsActive()) {
			bullets_.erase(bullets_.begin() + i--);
		}
	}

	ImGui::Begin("WorldPlayer");
	Vector3 pos = { screenTransform_.m[3][0], screenTransform_.m[3][1] , screenTransform_.m[3][2] };
	ImGui::Text("Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
	Vector3 rot = transform_->rotation + camera_->GetTransform().rotation;
	ImGui::Text("Rotation: (%.2f, %.2f, %.2f)", rot.x, rot.y, rot.z);
	ImGui::End();
}

void Player::Draws() const {
	Draw(&screenTransform_);

	for (const auto& bullet : bullets_) {
		bullet->Draw();
	}
}

Transform Player::GetTransform() const {
	Transform ans = *transform_;
	ans.scale *= camera_->GetTransform().scale;
	ans.rotation += camera_->GetTransform().rotation;
	ans.position += camera_->GetTransform().position;
	return ans;
}
