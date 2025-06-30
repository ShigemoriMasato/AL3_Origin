#include "RailCameraController.h"
#include "externals/imgui/imgui.h"

RailCameraController::RailCameraController(Camera* camera) :
transform_(std::make_unique<Transform>()),
camera_(std::make_shared<Camera>()) {
	if (camera) {
		*camera_ = *camera;
	}
	camera_->SetTransform(transform_.get());
}

void RailCameraController::Initialize() {
	transform_->position = { 0.0f, 0.0f, -20.0f };
	camera_->SetProjectionMatrix(PerspectiveFovDesc());
}

void RailCameraController::Update() {
	ImGui::Begin("Camera");
	ImGui::DragFloat3("Position", &transform_->position.x, 0.1f);
	ImGui::DragFloat3("Rotation", &transform_->rotation.x, 0.01f);
	ImGui::End();

	transform_->position.z -= 0.01f;

	camera_->MakeMatrix();
}

