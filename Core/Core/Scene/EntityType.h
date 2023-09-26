#ifndef OE1_ENTITY_TYPE_H_
#define OE1_ENTITY_TYPE_H_


#include "imgui/IconsFontAwesome6.h"
#include <unordered_map>
#include <string>

namespace OE1Core
{
	enum class EntityType : unsigned char
	{
		T_STATIC_MESH			= 0x1,
		T_POINT_LIGHT			= 0x2,
		T_DIRECTIONAL_LIGHT		= 0x3,
		T_PLAYER				= 0x4,
		T_BILLBOARD				= 0x5,
		T_CAMERA				= 0x6,
		T_EMPTY					= 0x7,
		T_TERRAIN				= 0x8,
		T_PARTICLE_SYSTEM		= 0x9,
		T_NPC					= 0xA,
		T_WATER					= 0xB,
		T_TRIGGER				= 0xC,
		T_SPAWNER				= 0xD,
		T_PICKUP				= 0xE,
		T_ENEMY					= 0xF,
		T_PROJECTILE			= 0x10,
		T_VEHICLE				= 0x11,
		T_DOOR					= 0x12,
		T_AUDIO_SOURCE			= 0x13,
		T_AUDIO_LISTENER		= 0x14,
		T_UNIDENTIFIED			= 0x15
	};
	static std::unordered_map < EntityType, std::pair < std::string, std::string >> s_TypeRegistry
	{
		{ EntityType::T_STATIC_MESH,		std::make_pair<std::string, std::string>("StaticMesh",			ICON_FA_CUBE)	},
		{ EntityType::T_POINT_LIGHT,		std::make_pair<std::string, std::string>("PointLight",			ICON_FA_LIGHTBULB) },
		{ EntityType::T_DIRECTIONAL_LIGHT,	std::make_pair<std::string, std::string>("DirectionalLight",	ICON_FA_SUN) },
		{ EntityType::T_PLAYER,				std::make_pair<std::string, std::string>("Player",				ICON_FA_FLAG_CHECKERED) },
		{ EntityType::T_BILLBOARD,			std::make_pair<std::string, std::string>("Billboard",			ICON_FA_IMAGES) },
		{ EntityType::T_CAMERA,				std::make_pair<std::string, std::string>("Camera",				ICON_FA_VIDEO) },
		{ EntityType::T_EMPTY,				std::make_pair<std::string, std::string>("Empty",				ICON_FA_HOURGLASS_EMPTY) },
		{ EntityType::T_TERRAIN,			std::make_pair<std::string, std::string>("Terrain",				ICON_FA_BORDER_TOP_LEFT) },
		{ EntityType::T_PARTICLE_SYSTEM,	std::make_pair<std::string, std::string>("ParticleSystem",		ICON_FA_WAND_SPARKLES) },
		{ EntityType::T_NPC,				std::make_pair<std::string, std::string>("NPC",					ICON_FA_GRADUATION_CAP) },
		{ EntityType::T_WATER,				std::make_pair<std::string, std::string>("Water",				ICON_FA_WATER) },
		{ EntityType::T_TRIGGER,			std::make_pair<std::string, std::string>("Trigger",				ICON_FA_CIRCLE_DOT) },
		{ EntityType::T_SPAWNER,			std::make_pair<std::string, std::string>("Spawner",				ICON_FA_BROOM) },
		{ EntityType::T_PICKUP,				std::make_pair<std::string,	std::string>("Pickup",				ICON_FA_HAND_HOLDING) },
		{ EntityType::T_ENEMY,				std::make_pair<std::string, std::string>("Enemy",				ICON_FA_FACE_ANGRY) },
		{ EntityType::T_PROJECTILE,			std::make_pair<std::string, std::string>("Projectile",			ICON_FA_JET_FIGHTER) },
		{ EntityType::T_VEHICLE,			std::make_pair<std::string, std::string>("Vehicle",				ICON_FA_CAR_SIDE) },
		{ EntityType::T_DOOR,				std::make_pair<std::string, std::string>("Door",				ICON_FA_DOOR_CLOSED) },
		{ EntityType::T_AUDIO_SOURCE,		std::make_pair<std::string, std::string>("AudioSource",			ICON_FA_VOLUME_HIGH) },
		{ EntityType::T_AUDIO_LISTENER,		std::make_pair<std::string, std::string>("AudioListener",		ICON_FA_HEADPHONES) },
		{ EntityType::T_UNIDENTIFIED,		std::make_pair<std::string, std::string>("Unidentified",		ICON_FA_QUESTION) }
	};
}

#endif // !OE1_ENTITY_TYPE_H_
