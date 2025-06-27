#include "GameScene.h"
#include "../Engine/Input/Input.h"
#include "../externals/imgui/imgui.h"
#include "../Engine/Math/MyMath.h"

using namespace Matrix;

GameScene::GameScene(std::shared_ptr<CommonData> commonData) : Scene(commonData), 
camera_(new Camera()),
debugCamera_(new DebugCamera()),
player_(std::make_shared<Player>(camera_, commonData->modelHandle_[int(ModelType::player)])) {
}

GameScene::~GameScene() {
	delete camera_;
	delete debugCamera_;
}

void GameScene::Initialize() {
	debugCamera_->Initialize();
	player_->Initialize();
	cameraTransform_ = {};
	cameraTransform_.position = { 0.0f, 0.0f, -20.0f };
	camera_->SetProjectionMatrix(PerspectiveFovDesc());
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

	return nullptr;
}

void GameScene::Draw() const {
	player_->Draws();
}
