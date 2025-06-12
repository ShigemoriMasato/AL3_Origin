#pragma once
#include "Engine/Math/MyMath.h"
#include "Engine/Data/Transform.h"

class MapChip;
class Enemy;

enum class LRDirection {
	Right,
	Left,
};

struct CollisionMapInfo {
	bool isRoof;
	bool isFloor;
	bool isWall;
	Vector3 movement;
};

class Player {
public:

	Player() = default;
	~Player() = default;

	void Initialize(Camera* camera, int player);
	void Update();
	void Draw() const;

	void OnCollition(Enemy enemy);

	Transform GetTransform() const {
		return transform_;
	}
	Vector3 GetVelocity() const {
		return velocity_;
	}

	void SetMapChip(MapChip* mapChip) { mapChip_ = mapChip; }

	AABB GetAABB();

private:

	void Move();

	void CheckCollitionRoofMapChip(CollisionMapInfo& info);
	void CheckCollitionFloorMapChip(CollisionMapInfo& info);
	void CheckCollitionRightMapChip(CollisionMapInfo& info);
	void CheckCollitionLeftMapChip(CollisionMapInfo& info);

	void SwitchLanding(const CollisionMapInfo& info);

	enum Corner {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	MapChip* mapChip_ = nullptr;

	Transform transform_;
	Camera* camera_ = nullptr;

	int model_;
	const float size = 0.8f;

	Vector3 velocity_;
	const float kAttenuation = 0.1f; // 減衰率
	const float kAcceleration = 0.01f; // 加速度
	const float kRunSpeedMax = 0.2f; // 最大速度

	float beginingRotateY_ = 0.0f;
	float turnTimer_ = 0;
	const float kTimeTurn = 0.2f; // 回転にかかる時間
	bool isRight_; // 右向きかどうか

	bool onGround_;
	const float kJumpSpeed = 0.8f; // ジャンプ速度
	const float kGravityAcceleration = 0.05f; // 重力加速度
	const float kFallSpeedMax = 1.0f; // 最大落下速度

	const float kBufferPosition = 0.01f; // 衝突判定のバッファ
	const float kAttenuationLanding = 0.5f; // 着地時の減衰率
};

