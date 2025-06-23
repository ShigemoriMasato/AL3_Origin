#include "HitEffect.h"
#include "Engine/Render/Render.h"
#include <random>
#include <numbers>

HitEffect::HitEffect() {
	logger_ = new Logger("HitEffect");
}

HitEffect::~HitEffect() {
	delete logger_;
}

void HitEffect::Initialize(Camera* camera, int textureHandle) {
	camera_ = camera;
	textureHandle_ = textureHandle;
}

void HitEffect::Update() {
	
	for (int i = 0; i < transforms_.size(); ++i) {

		if (timer_[i] > kLifeTime) {
			transforms_.erase(transforms_.begin() + i);
			timer_.erase(timer_.begin() + i);
			--i;
			continue;
		}

		timer_[i] += 1.0f / 60.0f;

		logger_->Log(std::format("timer complete : {}, {}", i, timer_[i]));

		for (int j = 0; j < transforms_[i].size(); ++j) {

			float t = 1.0f;

			//scaleの大きさの倍率
			if (timer_[i] < kScaleTime) {
				t = float(timer_[i]) / kScaleTime;
			} else if (timer_[i] > kLifeTime - kScaleTime) {
				t = float(kLifeTime - timer_[i]) / kScaleTime;
			}

			if (!j) {
				
				transforms_[i][j].scale = Vector3(1.5f, 1.5f, 1.0f) * t;

			} else {

				transforms_[i][j].scale = Vector3(0.3f, 2.0f, 1.0f) * t;

			}

			logger_->Log(std::format("Update Complete : {}-{}", i, j));

		}
	}
}

void HitEffect::Draw() const {
	for(const auto& transform : transforms_) {
		for (const auto& t : transform) {
			Render::DrawSprite(MakeAffineMatrix(t), camera_, {1.0f, 1.0f, 1.0f, 0.99f}, {}, textureHandle_);
		}
	}
}

void HitEffect::Boot(Vector3 pos) {
	std::vector<Transform> transform;
	Transform t{};
	t.scale = { 0.0f, 0.0f, 1.0f };

	t.position = pos;
	transform.push_back(t);

	t.rotation.z = float(std::rand() % 2048) / 1000.0f * std::numbers::pi_v<float>;
	transform.push_back(t);

	t.rotation.z = float(std::rand() % 2048) / 1000.0f * std::numbers::pi_v<float>;
	transform.push_back(t);

	transforms_.push_back(transform);

	timer_.push_back(0.0f);
}
