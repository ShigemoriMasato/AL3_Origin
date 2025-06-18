#pragma once
#include "CommonData.h"
#include "../../Engine/Render/Render.h"

class Scene {
public:
	Scene(CommonData* commonData);
	~Scene() = default;

	virtual void Initialize() = 0;
	[[nodiscard]]
	virtual Scene* Update() = 0;
	virtual void Draw() const = 0;

protected:

	CommonData* commonData_;

};
