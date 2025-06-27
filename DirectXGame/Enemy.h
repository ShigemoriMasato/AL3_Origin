#pragma once
#include "Object/Object.h"
#include "EnemyBullet.h"
#include "TimeCall.h"
#include <memory>

class Enemy;

class EnemyState {
public:
	EnemyState(Enemy* enemy) : enemy_(enemy) {}
	virtual std::shared_ptr<EnemyState> Down() = 0;
	virtual std::shared_ptr<EnemyState> Up() = 0;
	virtual void Execute() = 0;
protected:

	Enemy* enemy_;

};

class EnemyStateApploach : public EnemyState {
public:
	EnemyStateApploach(Enemy* enemy) : EnemyState(enemy) {}
	std::shared_ptr<EnemyState> Down() override;
	std::shared_ptr<EnemyState> Up() override;
	void Execute() override;

private:

};

class EnemyStateLeave : public EnemyState {
public:
	EnemyStateLeave(Enemy* enemy) : EnemyState(enemy) {}
	std::shared_ptr<EnemyState> Down() override;
	std::shared_ptr<EnemyState> Up() override;
	void Execute() override;

private:

};

class Enemy : public Object {
public:
	Enemy(Camera* camera, int modelHandle, Object* target);
	~Enemy() = default;

	void Initialize() override;

	void Update() override;

	std::shared_ptr<EnemyState> Down();
	std::shared_ptr<EnemyState> Up();

	bool GetIsAlive() const { return isAlive_; }

	void MovePosition(Vector3 velocity);

	/// <summary>
	/// EnemyBulletとEnemyのDraw
	/// </summary>
	void Draws();

private:

	void Fire();

	void Death() { isAlive_ = false; }

	using StateFunction = void (Enemy::*)(); // メンバ関数ポインタ型を定義
	static StateFunction stateFunc[];       // メンバ関数ポインタの配列を宣言

	std::shared_ptr<EnemyState> state_;

	bool isAlive_ = true;

	int frame_ = 0;

	//弾
	std::vector<EnemyBullet> bullets_;
	int fireCooltime_ = 0;
	static inline const int fireCooltimeMax = 60;

	//TimeCall
	TimeCall* timecall_ = nullptr;

	Object* target_ = nullptr; // プレイヤーへの参照
};

