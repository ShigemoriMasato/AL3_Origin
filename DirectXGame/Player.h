#pragma once
#include "Object/Object.h"

class Player : public Object {
public:

	Player(Camera* camera, int modelhandle);
	~Player() = default;

	void Initialize() override;

	void Update() override;

private:

	Vector3 velocity_{};
	const float speed_ = 0.01f;

};
