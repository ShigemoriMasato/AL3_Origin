#pragma once
#include "Object/Object.h"

class PlayerBullet : public Object {
public:

	PlayerBullet(Camera* camera, Vector3 pos);
	~PlayerBullet() = default;
	void Initialize() override;
	void Update() override;

private:

	Vector3 velocity_;

};

