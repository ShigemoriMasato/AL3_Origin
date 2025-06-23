#pragma once
#include "Common/Scene.h"
#include "Common/CommonData.h"
#include "../Engine/Camera/DebugCamera.h"

class GameScene : public Scene {
public:
	GameScene(CommonData* commonData);
	~GameScene();

	void Initialize() override;
	Scene* Update() override;
	void Draw() const override;

private:
	Camera* camera_;
	DebugCamera* debugCamera;

	bool isDebugCamera = false;

};
