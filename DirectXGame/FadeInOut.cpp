#include "FadeInOut.h"
#include "Engine/Math/MyMath.h"
#include "Engine/Render/Render.h"
#include "Engine/Camera/Camera.h"

using namespace MyMath;
using namespace Matrix;

void FadeInOut::Initialize(int fadeTime, Camera* camera) {
	fadeTime_ = fadeTime;
	camera_ = camera;
	mateiral_ = { 0.0f, 0.0f, 0.0f, 1.0f, true }; // 初期カラーを白に設定
	transform_ = Transform();
	transform_.position.z = -1;
}

void FadeInOut::Update() {
	if (!isFadeIn_) {
		--fadeTimer_;
	} else {
		if (fadeTimer_ < fadeTime_) {
			++fadeTimer_;
		}
	}

	mateiral_.color.w = lerp(1.0f, 0.0f, static_cast<float>(fadeTimer_) / fadeTime_);

	Vector3 buffer = camera_->GetPosition();
	buffer.z += 1;
	transform_.position = buffer;
}

void FadeInOut::Draw() const {
	Render::DrawSprite(
		Vector4(-5.0f, 4.0f, 0.0f, 1.0f), // 左上
		Vector4(5.0f, 4.0f, 0.0f, 1.0f), // 右上
		Vector4(-5.0f, -4.0f, 0.0f, 1.0f), // 左下
		Vector4(5.0f, -4.0f, 0.0f, 1.0f), // 右下
		MakeAffineMatrix(transform_), camera_,
		mateiral_
	);
}

void FadeInOut::SwitchFadeInOut(bool fadeIn) {
	isFadeIn_ = fadeIn;
}

void FadeInOut::SetPosition(const Vector3& position) {
	transform_.position = position * 0.3f;
	transform_.scale = Vector3(1.0f + position.x * 0.3f, 1.0f + position.y * 0.3f, 1.0f);
}
