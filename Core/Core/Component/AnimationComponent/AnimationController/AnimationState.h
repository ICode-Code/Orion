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

	inline static std::unordered_map<ANIMATION_STATE, std::string> ANIMATION_MAP = {
		{ANIMATION_STATE::T_POS, "T_POS"},
		{ANIMATION_STATE::IDEL, "IDEL"},
		{ANIMATION_STATE::RUN, "RUN"},
		{ANIMATION_STATE::RUN_JUMP, "RUN_JUMP"},
		{ANIMATION_STATE::RUN_TURN_RIGHT, "RUN_TURN_RIGHT"},
		{ANIMATION_STATE::RUN_TURN_LEFT, "RUN_TURN_LEFT"},
		{ANIMATION_STATE::WALK, "WALK"},
		{ANIMATION_STATE::SPRINT, "SPRINT"},
		{ANIMATION_STATE::LAND, "LAND"},
		{ANIMATION_STATE::JUMP, "JUMP"},
		{ANIMATION_STATE::TURN_LEFT, "TURN_LEFT"},
		{ANIMATION_STATE::TURN_RIGHT, "TURN_RIGHT"},
		{ANIMATION_STATE::CROUCH, "CROUCH"},
		{ANIMATION_STATE::CROUCH_WALK, "CROUCH_WALK"},
		{ANIMATION_STATE::CROUCH_RUN, "CROUCH_RUN"},
		{ANIMATION_STATE::PRONE_IDLE, "PRONE_IDLE"},
		{ANIMATION_STATE::PRONE_CRAWL, "PRONE_CRAWL"},
		{ANIMATION_STATE::HIT, "HIT"},
		{ANIMATION_STATE::EMOTE, "EMOTE"},
		{ANIMATION_STATE::INTERACT, "INTERACT"},
		{ANIMATION_STATE::STAND, "STAND"},
		{ANIMATION_STATE::SIT, "SIT"},
		{ANIMATION_STATE::MEELE_ATTACK, "MEELE_ATTACK"},
		{ANIMATION_STATE::SHOOT, "SHOOT"},
		{ANIMATION_STATE::BLOCK, "BLOCK"},
		{ANIMATION_STATE::ROLL, "ROLL"},
		{ANIMATION_STATE::DEATH, "DEATH"},
		{ANIMATION_STATE::RELOAD, "RELOAD"},
		{ANIMATION_STATE::AIM_DOWN_SIGHT, "AIM_DOWN_SIGHT"},
		{ANIMATION_STATE::AIM_FIRE, "AIM_FIRE"},
		{ANIMATION_STATE::AIM_IDLE, "AIM_IDLE"},
		{ANIMATION_STATE::AIM_WALK, "AIM_WALK"},
		{ANIMATION_STATE::AIM_RUN, "AIM_RUN"},
		{ANIMATION_STATE::AIM_JUMP, "AIM_JUMP"},
		{ANIMATION_STATE::AIM_TURN_LEFT, "AIM_TURN_LEFT"},
		{ANIMATION_STATE::AIM_TURN_RIGHT, "AIM_TURN_RIGHT"},
		{ANIMATION_STATE::GRENADE_THROW, "GRENADE_THROW"},
		{ANIMATION_STATE::GRENADE_COOK, "GRENADE_COOK"},
		{ANIMATION_STATE::GRENADE_IDLE, "GRENADE_IDLE"},
		{ANIMATION_STATE::GRENADE_THROW_AIM, "GRENADE_THROW_AIM"},
		{ANIMATION_STATE::GRENADE_THROW_RUN, "GRENADE_THROW_RUN"},
		{ANIMATION_STATE::GRENADE_THROW_JUMP, "GRENADE_THROW_JUMP"}
	};
}

#endif // !OE1_ANIMATION_STATE_H_
