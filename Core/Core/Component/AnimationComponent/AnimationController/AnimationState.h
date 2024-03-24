#ifndef OE1_ANIMATION_STATE_H_
#define OE1_ANIMATION_STATE_H_



namespace OE1Core
{
	enum class ANIMATION_STATE
	{
		T_POS, // NONE
		IDEL,

		RUN,
		
		RUN_JUMP,
		RUN_TURN_RIGHT,
		RUN_TURN_LEFT,

		WALK,
		SPRINT,
		LAND,

		JUMP,
		TURN_LEFT,
		TURN_RIGHT,

		CROUCH,
		CROUCH_WALK,
		CROUCH_RUN,

		PRONE_IDLE,//Character laying on the ground in a prone position without moving.
		PRONE_CRAWL,//Character crawling on the ground while prone.

		HIT,//Character being hit or taking damage.

		EMOTE, //Character performing an emote or gesture.
		INTERACT, // Character interacting with objects or the environment.

		STAND,
		SIT,

		MEELE_ATTACK,
		SHOOT,

		BLOCK,// Raises a shield or weapon to reduce or negate incoming damage from attacks
		ROLL,
		DEATH,

		RELOAD,//The animation for reloading the weapon.
		AIM_DOWN_SIGHT,
		AIM_FIRE,
		AIM_IDLE,
		AIM_WALK, //Walking or moving while aiming down sights.

		AIM_RUN, //Running or sprinting while aiming down sights.

		AIM_JUMP,//Jumping while aiming down sights.

		AIM_TURN_LEFT, //Turning left while aiming down sights.

		AIM_TURN_RIGHT, // Turning right while aiming down sights.

		GRENADE_THROW,

		GRENADE_COOK,//Holding the grenade before throwing it.

		GRENADE_IDLE,//Idle animation while holding a grenade.

		GRENADE_THROW_AIM,//Aiming the throw trajectory of a grenade.

		GRENADE_THROW_RUN,//Running while preparing to throw a grenade.

		GRENADE_THROW_JUMP, //Jumping while preparing to throw a grenade.
	};
}

#endif // !OE1_ANIMATION_STATE_H_
