#pragma once
#include "Object/Object.h"

enum class EnemyState {
	Apploach,
	Leave
};

class Enemy : public Object {
public:

	Enemy(Camera* camera, int modelHandle);
	~Enemy() = default;

	void Initialize() override;

	void Update() override;

	bool GetIsAlive() const { return isAlive_; }

private:
	using StateFunction = void (Enemy::*)(); // メンバ関数ポインタ型を定義
	static StateFunction stateFunc[];       // メンバ関数ポインタの配列を宣言

	void Apploach();
	void Leave();

	EnemyState state_ = EnemyState::Apploach;

	bool isAlive_ = true;

	int frame_ = 0;
};

