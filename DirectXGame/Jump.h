#pragma once
#include "Object/Action.h"
#include "Object/Actor.h"
#include <memory>

class Player;

namespace PlayerAct {

	class Jump : public Action {
	public:

		Jump(Actor* actor);
		~Jump() = default;

		void Execute() override;

	private:

		float jumpSpeed_ = 5.0f;
		Player* player_ = nullptr;

	};

}
