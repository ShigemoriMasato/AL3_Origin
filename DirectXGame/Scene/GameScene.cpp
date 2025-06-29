#include "GameScene.h"
#include "../Engine/Input/Input.h"
#include "../externals/imgui/imgui.h"
#include "../Engine/Math/MyMath.h"

using namespace Matrix;

GameScene::GameScene(std::shared_ptr<CommonData> commonData) : Scene(commonData), 
camera_(new Camera()),
debugCamera_(new DebugCamera()),
player_(std::make_shared<Player>(camera_, commonData->modelHandle_[int(ModelType::Player)])) {
}

GameScene::~GameScene() {
	delete camera_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	debugCamera_->Initialize();
	player_->Initialize();
	cameraTransform_ = {};
	cameraTransform_.position = { 0.0f, 0.0f, -32.0f };
	camera_->SetProjectionMatrix(PerspectiveFovDesc());

	enemies_.clear();
	CreateEnemy();
}

Scene* GameScene::Update() {

	ImGui::Begin("Camera");
	ImGui::Checkbox("Debug Camera", &isDebugCamera);
	ImGui::DragFloat3("scale", &cameraTransform_.scale.x, 0.1f);
	ImGui::DragFloat3("rotation", &cameraTransform_.rotation.x, 0.1f);
	ImGui::DragFloat3("position", &cameraTransform_.position.x, 0.1f);
	ImGui::End();

	if (isDebugCamera) {
		debugCamera_->Update();
		*camera_ = debugCamera_->GetCamera();
	} else {
		camera_->SetTransform(cameraTransform_);
		camera_->MakeMatrix();
	}

	player_->Update();

	for (int i = 0; i < enemies_.size(); ++i) {
		enemies_[i]->Update();
		if (!enemies_[i]->GetIsAlive()) {
			enemies_.erase(enemies_.begin() + i);
			//新しい敵を生成
			CreateEnemy();
		}
	}

	AllCollisionCheck();

	return nullptr;
}

void GameScene::Draw() const {
	player_->Draws();
	
	for (const auto& enemy : enemies_) {
		enemy->Draws();
	}
}

void GameScene::CreateEnemy() {
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(camera_, commonData_->modelHandle_[int(ModelType::Enemy)], player_.get());
	enemy->Initialize();
	enemies_.push_back(enemy);
}

void GameScene::AllCollisionCheck() {

#pragma region Player to EnemyBullet

	Sphere playerSphere = { player_->GetTransform().position, 0.5f };

	for (auto& e : enemies_) {
		for(int i = 0; i < e->GetBullets().size(); ++i) {

			Sphere bulletSphere = { e->GetBullets()[i]->GetTransform().position, 0.5f * e->GetBullets()[i]->GetTransform().scale.x };

			if (CollisionChecker(playerSphere, bulletSphere)) {
				player_->OnCollision(e->GetBullets()[i].get());
				e->GetBullets()[i]->OnCollision(player_.get());
			}
		}
	}

#pragma endregion

#pragma region Enemy to PlayerBullet
	for (auto& e : enemies_) {

		Sphere enemySphere = { e->GetTransform().position, 0.5f * e->GetTransform().scale.x };

		for (int i = 0; i < player_->GetBullets().size(); ++i) {
			Sphere bulletSphere = { player_->GetBullets()[i]->GetTransform().position, 0.5f * player_->GetBullets()[i]->GetTransform().scale.x };
			if (CollisionChecker(enemySphere, bulletSphere)) {
				e->OnCollision(player_->GetBullets()[i].get());
				player_->GetBullets()[i]->OnCollision(e.get());
			}
		}
	}

}
