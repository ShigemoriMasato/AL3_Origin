#include "DeathParticle.h"
#include "Engine/Math/MyMath.h"
#include "Engine/Render/Render.h"
#include <numbers>
#include <cmath>

DeathParticle::DeathParticle() {
	logger_ = new Logger("DeathParticle");
}

DeathParticle::~DeathParticle() {
	delete logger_;
}

void DeathParticle::Initialize(Camera* camera, int modelHandle) {
	camera_ = camera;
	modelHandle_ = modelHandle;
}

void DeathParticle::Update() {

	for (int i = 0; i < timer_.size(); ++i) {
		timer_[i] += 0.016f;
		logger_->Log(std::format("now particle Num : {}", i * 8));

		if (timer_[i] > lifeTime_) {
			
			//終了処理
			timer_.erase(timer_.begin() + i);
			transforms_.erase(transforms_.begin() + i);
			colors_.erase(colors_.begin() + i);

			continue;

			logger_->Log(std::format("delete particle Num : {}", i));

		}

		float t = timer_[i] / lifeTime_;

		for (int j = 0; j < transforms_[i].size(); ++j) {
			float theta = float(j) / 8.0f * std::numbers::pi_v<float> * 2.0f;

			Vector3 normal = Vector3(std::cosf(theta), std::sinf(theta), 0.0f);
			transforms_[i][j].position += normal * speed_;

			colors_[i][j].w = 1.0f - t;
		}
	}

	logger_->Log(std::format("ended particle Num : {}", timer_.size()));

}

void DeathParticle::Draw() {

	for (int i = 0; i < transforms_.size(); ++i) {
		for (int j = 0; j < transforms_[i].size(); ++j) {
			Render::DrawModel(modelHandle_, Matrix::MakeAffineMatrix(transforms_[i][j]), camera_, MaterialData(colors_[i][j], true));
		}
	}

}

void DeathParticle::Boot(Vector3 pos) {

	std::vector<Transform> transform;
	Transform t;
	t.position = pos;
	t.scale = Vector3(1.0f, 1.0f, 1.0f);
	t.rotation = Vector3(0.0f, 0.0f, 0.0f);

	std::vector<Vector4> color;
	Vector4 c(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < 8; ++i) {
		transform.push_back(t);
		color.push_back(c);
	}

	transforms_.push_back(transform);
	colors_.push_back(color);

	timer_.push_back(0.0f);

}
