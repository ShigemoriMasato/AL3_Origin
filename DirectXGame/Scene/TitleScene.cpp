#include "TitleScene.h"
#include "GameScene.h"
#include "../Engine/Input/Input.h"
#include "../Engine/Camera/Camera.h"
#include "../Engine/Math/MyMath.h"

using namespace MyMath;

TitleScene::TitleScene(CommonData* commonData) : Scene(commonData) {
	titleHandle_ = commonData->modelHandle_[int(ModelType::Title)];

	camera_ = new Camera();

	fadeInOut_ = new FadeInOut();
}

TitleScene::~TitleScene() {
	delete camera_;
	delete fadeInOut_;
}

void TitleScene::Initialize() {
	camera_->SetProjectionMatrix(PerspectiveFovDesc());
	Transform cameraTransform{};
	cameraTransform.position = { 0.0f, 0.0f, -10.0f };
	camera_->SetTransform(cameraTransform);
	camera_->MakeMatrix();
	fadeInOut_->Initialize(60, camera_); // フェードインアウトの初期化
	fadeInOut_->SwitchFadeInOut(true); // フェードインを開始
}

Scene* TitleScene::Update() {

	fadeInOut_->Update();

	if (Input::GetKeyState(DIK_SPACE)) {
		fadeInOut_->SwitchFadeInOut(false);
	}

	if (fadeInOut_->GetFadeTimer() <= 0) {
		return new GameScene(commonData_);
	}

	return nullptr;
}

void TitleScene::Draw() const {

	Transform transform{};
	transform.position.z = 1.0f;
	Render::DrawModel(titleHandle_, MakeAffineMatrix(transform), camera_);

	fadeInOut_->Draw(); // フェードインアウトの描画
}
