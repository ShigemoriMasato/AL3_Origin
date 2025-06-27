#pragma once
#include "../Engine/Data/Transform.h"
#include "../Engine/Camera/Camera.h"

enum class ShapeType {
	Triangle,
	Sphere,
	Cube,
	Sprite,
	Line,
	Model,
	Count
};

class Object {
public:

	Object(Camera* camera, ShapeType type) : camera_(camera), type_(type) {};
	virtual ~Object() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() const;

	void SetCamera(Camera* camera) {
		camera_ = camera;
	}

	/// <summary>
	/// 三角形、スプライト、球のときのみ適用
	/// </summary>
	/// <param name="lt">三角形左下、スプライト左上、球の半径</param>
	/// <param name="rt">三角形上、スプライト右上</param>
	/// <param name="lb">三角形右下、スプライト左下</param>
	/// <param name="rb">スプライト右下</param>
	void SetRocalPosition(const Vector3& lt = {-0.5f, 0.5f, 0.0f}, const Vector3& rt = {0.5f, 0.5f, 0.0f}, const Vector3& lb = {-0.5f, -0.5f, 0.0f}, const Vector3& rb = {0.5f, -0.5f, 0.0f}) {
		this->lt = lt;
		this->rt = rt;
		this->lb = lb;
		this->rb = rb;
	}

protected:

	Transform transform_{};
	uint32_t color = 0xffffffff;
	int handle_ = 1;

private:

	Camera* camera_ = nullptr;
	ShapeType type_ = ShapeType::Count;

	Vector3 lt = { -0.5f, 0.5f, 0.0f };
	Vector3 rt = { 0.5f, 0.5f, 0.0f };
	Vector3 lb = { -0.5f, -0.5f, 0.0f };
	Vector3 rb = { 0.5f, -0.5f, 0.0f };
};

