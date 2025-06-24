#pragma once
#include "Engine/Data/Transform.h"
#include "Engine/Camera/Camera.h"

class Object {
public:

	Object() = default;
	virtual ~Object() = default;
	// 初期化
	virtual void Initialize() {}
	// 更新
	virtual void Update() {}
	// 描画
	virtual void Draw(const Camera& camera) const {}

protected:

	Transform transform_;

};

