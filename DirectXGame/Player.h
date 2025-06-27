#pragma once
#include "Object/Object.h"
#include "PlayerBullet.h"
#include <vector>

class Player : public Object {
public:

	Player(Camera* camera, int modelhandle);
	~Player() = default;

	void Initialize() override;

	void Update() override;

	/// <summary>
	/// BulletとPlayerのDraw
	/// </summary>
	void Draws() const;

private:

	Vector3 velocity_{};
	const float speed_ = 0.01f;

	std::vector<PlayerBullet> bullets_;

};
