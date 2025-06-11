#include "TitleScene.h"
#include "../Engine/Input/Input.h"
#include "../externals/imgui/imgui.h"

using namespace Matrix;

TitleScene::TitleScene(CommonData* commonData) : Scene(commonData) {
	camera_ = new Camera();
	debugCamera = new DebugCamera();
	player_ = new Player();
	player_->Initialize(camera_, commonData_->modelHandle_[int(ModelType::player)]);

	cameraController_ = new CameraController();
	cameraController_->Initialize({ 12.0f, 88.0f, 88.0f, 7.2f });
	cameraController_->SetTarget(player_);

	mapChip_ = new MapChip();
	mapChip_->Initialize("resources/blocks.csv", commonData_->modelHandle_[int(ModelType::Block)], camera_);

	debugCamera->Initialize();
	skydome_ = commonData_->modelHandle_[int(ModelType::skydome)];
}

TitleScene::~TitleScene() {
	delete camera_;
	delete player_;
	delete mapChip_;
	delete debugCamera;
	delete cameraController_;
}

Scene* TitleScene::Update() {

	cameraController_->Update();

	if (isDebugCamera) {
		debugCamera->Update();
		*camera_ = debugCamera->GetCamera();
	} else {
		*camera_ = *cameraController_->GetCamera();

		camera_->SetProjectionMatrix(PerspectiveFovDesc());
	}

	camera_->MakeMatrix();

	if (Input::GetKeyState(DIK_SPACE) && !Input::GetPreKeyState(DIK_SPACE)) {
		isDebugCamera = !isDebugCamera; // Toggle camera mode
	}

	player_->Update();

	return nullptr;
}

void TitleScene::Draw() const {
	Render::DrawModel(skydome_, MakeIdentity4x4(), camera_, { 1.0f, 1.0f, 1.0f, 1.0f, true }, {});

	player_->Draw();

	mapChip_->Draw();
}
