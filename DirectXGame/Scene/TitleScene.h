#pragma once
#include "Common/Scene.h"

class TitleScene : public Scene {
public:

	TitleScene(CommonData* commonData);
	~TitleScene();
	void Initialize() override;
	Scene* Update() override;
	void Draw() const override;

private:

};
