#pragma once
#include "Object/Action.h"

class Player;

namespace PlayerAct {
	class Move : public Action {
	public:

		Move(Actor* actor);
		~Move() = default;
		/// <summary>
		/// キューに入れられるかどうか(初期値true)
		/// </summary>
		/// <returns>true:入れる</returns>
		bool CanExecute() override { return true; }
		/// <summary>
		/// 実行する関数
		/// </summary>
		void Execute() override;
		/// <summary>
		/// キューに残り続けるか
		/// </summary>
		/// <returns>true:残る false:消える</returns>
		bool ShouldKeep() override { return true; }

	private:

		Player* player_ = nullptr;
		float speed_ = 0.1f;

	};

}
