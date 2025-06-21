#pragma once
#include "Engine/Math/MyMath.h"
#include "Engine/Data/Transform.h"
#include "DeathParticle.h"

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

enum class PlayerState {
	Alive,
	Death,
};

class Player {
public:

	Player();
	~Player();

	void Initialize(Camera* camera, int player, int attackEffect);
	void Update();
	void Draw() const;

	void OnCollition(Enemy& enemy);

	void SetMapChip(MapChip* mapChip) { mapChip_ = mapChip; }

	AABB GetAABB();
	PlayerState GetState() const {
		return state_;
	}
	bool GetIsAttack() const {
		return isAttack_;
	}
	Transform GetTransform() const {
		return transform_;
	}
	Vector3 GetVelocity() const {
		return velocity_;
	}

private:

	void Move();
	void Attack();

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

	enum class Behavior {
		Unknown,
		Root,
		Attack
	};

	void BehaviorUpdate();
	void BehaviorInitialize(Behavior bh);

	enum class AttackPhase {
		Accumulate,
		Rush,
		Fin
	};

	//描画関連
	Transform transform_;
	Camera* camera_ = nullptr;
	int model_;
	const float size = 0.8f;

	//死亡処理
	PlayerState state_ = PlayerState::Alive;
	std::vector<int> particleCooltime_;
	DeathParticle* deathParticle_ = nullptr;

	//移動
	Vector3 velocity_;
	const float kAttenuation = 0.1f; // 減衰率
	const float kAcceleration = 0.01f; // 加速度
	const float kRunSpeedMax = 0.2f; // 最大速度

	//振り向き
	float beginingRotateY_ = 0.0f;
	float turnTimer_ = 0;
	const float kTimeTurn = 0.2f; // 回転にかかる時間
	bool isRight_; // 右向きかどうか

	//着地系
	bool onGround_;
	const float kJumpSpeed = 0.8f; // ジャンプ速度
	const float kGravityAcceleration = 0.05f; // 重力加速度
	const float kFallSpeedMax = 1.0f; // 最大落下速度

	//Mapchipの当たり判定
	MapChip* mapChip_ = nullptr;
	const float kBufferPosition = 0.01f; // 衝突判定のバッファ
	const float kAttenuationLanding = 0.5f; // 着地時の減衰率

	//攻撃モーション
	Behavior behaviorRequest_ = Behavior::Root;
	Behavior behavior_ = Behavior::Root;
	int attackCooltime_ = 0;
	const int kAttackCooltime = 30; // 攻撃クールタイム
	int attackTime_ = 0;
	const int kAttackTime = 20;
	const int kAccumulateTime = 5;
	const int kRushTime = 9;
	const float kMaxAttackVelocity = 0.7f;
	AttackPhase attackphase_;
	Transform effectTransform_;
	const Vector3 kEffectOffset = { 1.2f, 0.0f, 0.0f }; // 攻撃エフェクトのオフセット
	int attackEffect_ = -1; // 攻撃エフェクトのテクスチャハンドル
	bool isAttack_ = false;
};

