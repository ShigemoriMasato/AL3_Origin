#include "TitleScene.h"
#include "../Engine/Input/Input.h"
#include "../externals/imgui/imgui.h"

using namespace Matrix;

TitleScene::TitleScene(CommonData* commonData) : Scene(commonData) {
	camera_ = new Camera();
	debugCamera = new DebugCamera();
	player_ = new Player();
	player_->Initialize(camera_, commonData_->modelHandle_[int(ModelType::player)]);

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
}

Scene* TitleScene::Update() {

	if (Input::GetKeyState(DIK_SPACE) && !Input::GetPreKeyState(DIK_SPACE)) {
		isDebugCamera = !isDebugCamera; // Toggle camera mode
	}

	player_->Update();

	if (isDebugCamera) {
		debugCamera->Update();
		*camera_ = debugCamera->GetCamera();
	} else {
		Transform transform{};
		transform.position.z = -10.0f;

		camera_->SetTransform(transform);
		camera_->SetProjectionMatrix(PerspectiveFovDesc());
	}

	camera_->MakeMatrix();

	return nullptr;
}

void TitleScene::Draw() const {
	Render::DrawModel(skydome_, MakeIdentity4x4(), camera_, { 1.0f, 1.0f, 1.0f, 1.0f, true }, {});

	player_->Draw();

	mapChip_->Draw();
}
