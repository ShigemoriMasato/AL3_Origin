#include "CameraController.h"
#include "CameraController.h"
#include "Player.h"
#include <algorithm>

CameraController::CameraController() {
	camera_ = new Camera();
}

namespace {
	Vector3 Lerp(Vector3 a, Vector3 b, float t) { return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t }; }
}

CameraController::~CameraController() { 
	delete camera_; 
}

void CameraController::Initialize(Rect area) {
	movableArea_ = area;
	target_ = nullptr;
	camera_->SetProjectionMatrix(PerspectiveFovDesc());
}

void CameraController::Update() {

	const Transform transform = target_->GetTransform();

	if (targetPos_ != transform.position) {
		lerpRatio_ = 0.0f;
	}

	targetPos_ = transform.position + (target_->GetVelocity() * kVelocityBias);
	targetPos_.y = transform.position.y + targetOffset_.y;

	if (lerpRatio_ < 1.0f) {
		lerpRatio_ += kInterpolationRate;
	}

	Transform cameraTransform{};

	camerapos_ = Lerp(camerapos_, targetPos_ + targetOffset_, lerpRatio_);

	camerapos_.x = std::clamp(camerapos_.x, targetPos_.x + kMargin.left, targetPos_.x + kMargin.right);
	camerapos_.y = std::clamp(camerapos_.y, targetPos_.y + kMargin.bottom, targetPos_.y + kMargin.top);
	camerapos_.x = std::clamp(camerapos_.x, movableArea_.left, movableArea_.right);
	camerapos_.y = std::clamp(camerapos_.y, movableArea_.bottom, movableArea_.top);

	cameraTransform.position = camerapos_;

	camera_->SetTransform(cameraTransform);
	camera_->MakeMatrix();
}

void CameraController::Reset() {
	if (!target_) {
		return;
	}

	const Transform targetTf = target_->GetTransform();

	Transform tf;
	tf.position = targetTf.position + targetOffset_;
}
