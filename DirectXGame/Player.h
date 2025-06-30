#pragma once
#include "Object/Object.h"
#include "PlayerBullet.h"
#include <vector>
#include <memory>

class Player : public Object {
public:

	Player(Camera* camera, int modelhandle, int bullethandle);
	~Player() = default;

	void Initialize() override;

	void Update() override;

	/// <summary>
	/// BulletとPlayerのDraw
	/// </summary>
	void Draws() const;

	std::vector<std::shared_ptr<PlayerBullet>> GetBullets() { return bullets_; }

	Transform GetTransform() const override;

private:

	Vector3 velocity_{};
	const float speed_ = 0.01f;

	int cooltime_ = 0;
	const int maxCooltime_ = 5;
	int bulletModelHandle_ = 0;
	std::vector<std::shared_ptr<PlayerBullet>> bullets_;

	std::shared_ptr<Transform> playerTransform_ = nullptr;

	Matrix4x4 screenTransform_{};
};
