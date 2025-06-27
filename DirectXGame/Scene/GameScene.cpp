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
}

Scene* GameScene::Update() {
	debugCamera_->Update();
	*camera_ = debugCamera_->GetCamera();
	player_->Update();

	return nullptr;
}

void GameScene::Draw() const {
	player_->Draw();
}
