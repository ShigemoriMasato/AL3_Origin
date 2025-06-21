#pragma once
#include "Common/Scene.h"
#include "Common/CommonData.h"
#include "../Engine/Camera/DebugCamera.h"
#include "../Player.h"
#include "../MapChip.h"
#include "../CameraController.h"
#include "../Enemy.h"
#include "../Engine/Log/Logger.h"
#include "../FadeInOut.h"
#include <vector>

class GameScene : public Scene {
public:
	GameScene(CommonData* commonData);
	~GameScene();

	void Initialize() override;
	Scene* Update() override;
	void Draw() const override;

private:

	void CheeckAllCollisions();

	Player* player_ = nullptr;
	MapChip* mapChip_ = nullptr;
	CameraController* cameraController_;
	std::vector<Enemy*> enemies_;
	DeathParticle* deathParticle_ = nullptr;
	FadeInOut* fadeInOut_ = nullptr;

	Logger* logger_ = nullptr;

	int skydome_;

	Camera* camera_;
	DebugCamera* debugCamera;

	bool isDebugCamera = false;

};
