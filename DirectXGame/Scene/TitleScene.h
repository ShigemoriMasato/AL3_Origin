#pragma once
#include "Common/Scene.h"
#include "../FadeInOut.h"

class TitleScene : public Scene {
public:

	TitleScene(CommonData* commonData);
	~TitleScene();
	void Initialize() override;
	Scene* Update() override;
	void Draw() const override;

private:

	Camera* camera_ = nullptr;
	
	FadeInOut* fadeInOut_;

	int titleHandle_ = -1;

};
