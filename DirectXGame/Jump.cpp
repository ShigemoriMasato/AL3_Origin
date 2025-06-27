#include "Jump.h"
#include <stdio.h>
#include "Player.h"

using namespace PlayerAct;

PlayerAct::Jump::Jump(Actor* actor) : Action("Jump", actor),
	player_(dynamic_cast<Player*>(actor)) {

}

void PlayerAct::Jump::Execute() {
	printf("Jump\n");
}
