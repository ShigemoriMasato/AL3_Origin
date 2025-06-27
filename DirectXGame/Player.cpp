#include "Player.h"
#include "Engine/Input/Input.h"
#include "externals/imgui/imgui.h"
#include <algorithm>

Player::Player(Camera* camera, int modelHandle) : Object(camera, ShapeType::Model) {
	handle_ = modelHandle;
}

void Player::Initialize() {
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
		transform_.rotation.y -= 0.05f;
	}

	if (Input::GetKeyState(DIK_E)) {
		transform_.rotation.y += 0.05f;
	}

	transform_.position += velocity_;

	ImGui::Begin("player");
	ImGui::DragFloat3("Position", &transform_.position.x, 0.1f);
	ImGui::End();

	transform_.position.x = std::clamp(transform_.position.x, -7.2f, 7.2f);
	transform_.position.y = std::clamp(transform_.position.y, -4.0f, 4.0f);

	if (Input::GetKeyState(DIK_SPACE) && !Input::GetPreKeyState(DIK_SPACE)) {
		// プレイヤーの弾を発射
		PlayerBullet bullet = PlayerBullet(camera_, transform_.position, transform_.rotation);
		bullet.Initialize();
		bullets_.push_back(bullet);
	}

	for (int i = 0; i < bullets_.size(); ++i) {
		bullets_[i].Update();
		if (bullets_[i].GetIsDelete()) {
			bullets_.erase(bullets_.begin() + i);
		}
	}

}

void Player::Draws() const {
	Draw();

	for (const auto& bullet : bullets_) {
		bullet.Draw();
	}
}
