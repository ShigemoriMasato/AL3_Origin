#pragma once
#include "Common/Scene.h"
#include "Common/CommonData.h"
#include "../Engine/Camera/DebugCamera.h"
#include "../Player.h"

class TitleScene : public Scene {
public:
	TitleScene(CommonData* commonData);
	~TitleScene();

	Scene* Update() override;
	void Draw() const override;

private:

	Player* player_ = nullptr;
	std::vector<Transform> transform;

	int block_;
	int skydome_;

	Camera* camera;
	DebugCamera* debugCamera;

	bool isDebugCamera = false;

};
