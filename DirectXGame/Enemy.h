#pragma once
#include "Engine/Camera/Camera.h"
#include "Engine/Data/Transform.h"

class Player;

class Enemy {
public:

	Enemy() = default;
	~Enemy() = default;

	void Initialize(Camera* camera, int skullHandle, int number);
	void Update();
	void Draw() const;

	void OnCollition(Player*);

	void SetPosition(const Vector3& position) { transform_.position = position; }
	void SetNumber(int number) { number_ = number; }

	AABB GetAABB() const;
	int GetNumber();
	bool GetIsDeath() const {
		return isDeath_;
	}
	bool GetIsInvisible() const {
		return isInvisible_;
	}

private:

	enum class Behavior {
		Unknown,
		Root,
		Death
	};

	void BehaviorUpdate();
	void BehaviorInitialize(Behavior bh);

	void Move();
	void Death();

	Transform transform_;
	Camera* camera_ = nullptr;
	int skull_ = -1;
	inline static const float size = 1.0f;
	int number_ = 0;	//個体識別番号

	float rollZTimer_ = 0.0f;
	inline static const float kRollZTime_ = 1.0f;
	inline static const float kRollZAngleStart_ = 0.2f;
	inline static const float kRollZAngleEnd_ = 0.5f;

	inline static const float speed_ = 0.01f;

	Behavior behavior_ = Behavior::Root;
	Behavior behaviorRequest_ = Behavior::Unknown;

	int deathTime_ = 0;
	bool isInvisible_ = false; // 無敵状態
	bool isDeath_ = false;
};
