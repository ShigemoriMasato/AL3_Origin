#pragma once
#include "Engine/Data/Transform.h"

class FadeInOut {
public:
	FadeInOut() = default;
	~FadeInOut() = default;

	void Initialize(int fadeTime, Camera* camera);
	void Update();
	void Draw() const;

	void SwitchFadeInOut(bool fadeIn);
	void SetPosition(const Vector3& position);

	int GetFadeTimer() const {
		return fadeTimer_;
	}

public:
	Camera* camera_ = nullptr;
	MaterialData mateiral_ = {};
	Transform transform_ = {};
	int fadeTimer_ = 0;
	int fadeTime_ = 0;
	bool isFadeIn_ = false; // trueならフェードイン、falseならフェードアウト
};
