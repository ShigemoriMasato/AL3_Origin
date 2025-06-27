#pragma once
#include "Object/Object.h"

class EnemyBullet : public Object {
public:

	EnemyBullet(Camera* camera, Vector3 pos, Object* target);
	~EnemyBullet() = default;
	void Initialize() override;
	void Update() override;
	bool GetIsDelete() const { return isDelete_; }

private:

	Vector3 velocity_;
	Vector3 direction_;
	static inline const float speed = 0.2f;
	bool isDelete_ = false;

	int frame_ = 0;

};

