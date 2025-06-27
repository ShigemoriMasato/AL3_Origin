#pragma once
#include "Object/Actor.h"
#include "Object/Object.h"
#include "Jump.h"

class Player : public Actor, public Object {
public:

	Player(Camera* camera, int modelhandle);
	~Player() = default;

	void Initialize() override;

	void Update() override;

private:

};
