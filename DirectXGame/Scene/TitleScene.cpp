#include "TitleScene.h"
#include "GameScene.h"
#include "../Engine/Input/Input.h"

TitleScene::TitleScene(CommonData* commonData) : Scene(commonData) {

}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
}

Scene* TitleScene::Update() {

	if (Input::GetKeyState(DIK_SPACE)) {
		return new GameScene(commonData_);
	}

	return nullptr;
}

void TitleScene::Draw() const {
}
