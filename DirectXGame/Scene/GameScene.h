#pragma once
#include "Common/Scene.h"
#include "Common/CommonData.h"
#include "../Engine/Camera/DebugCamera.h"
#include "../Player.h"

class GameScene : public Scene {
public:
	GameScene(std::shared_ptr<CommonData> commonData);
	~GameScene();

	void Initialize() override;
	Scene* Update() override;
	void Draw() const override;

private:
	Camera* camera_;
	DebugCamera* debugCamera_;

	bool isDebugCamera = false;

	std::shared_ptr<Player> player_ = nullptr;
};
