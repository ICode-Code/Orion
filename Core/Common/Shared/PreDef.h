#ifndef OE1_PRE_DEF_H_
#define OE1_PRE_DEF_H_

#include <GL/glew.h>
#include "UniformBlocks.h"


static std::string WideStrToNarrowStr(std::wstring _str)
{
	std::string dest;
	for (wchar_t c : _str)
		dest += (char)c;
	return dest;
}
static GLuint MaxUniformBlockSize()
{
	GLint max_uniform_buff;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max_uniform_buff);
	return max_uniform_buff;
}

/// <summary>
/// Active project root directory
/// </summary>
inline std::string ORI_ACTIVE_PATH = "##";

/// <summary>
/// Active project director, in which dir is the contain browser looking
/// right now
/// </summary>
inline std::string ORI_PROJECT_HOT_DIRECTORY = "##";

/// <summary>
/// All project root directory
/// </summary>

inline const std::string ORI_ORION_PROJECT_ROOT_PATH = "\\ORionEngine\\";
inline const std::string ORI_ENGEIN_METAL_FILE = ".orion_meta.ini";

#define ORI_MATERIAL_WINDOW_ALLOCATION_THRESHOLD 10
#define ORI_MAX_INSTANCE_PER_MESH 2048
#define ORI_STATIC_MESH_ASSET_POSTFIX ".ORISTATICMESHASSET"
#define ORI_DYNAMIC_MESH_ASSET_POSTFIX ".ORIDYNAMICMESHASSET"
#define ORI_TEXTURE_POSTFIX ".ORITEXTURE"
#define ORI_MATERIAL_POSTFIX ".ORIMATERIAL"
#define ORI_MATERIAL_PREFIX "MAT_ORI_"
#define ORI_MATERIAL_INSTA_PREFIX "MAT_ORI_INSTA"
#define ORI_UNIFORM_BLOCK_MEMORY_STRESS 128
#define ORI_MAX_MATERIAL_PER_UNIFORM_BLOCK ((MaxUniformBlockSize() / Memory::s_MaterialPropertiesBufferSize) - ORI_UNIFORM_BLOCK_MEMORY_STRESS)
#define ORI_MAX_ANIMATION_PER_UNIFORM_BLOCK ((MaxUniformBlockSize() / Memory::s_AnimationOffsetBufferSize) - ORI_UNIFORM_BLOCK_MEMORY_STRESS)

#define ORI_MAX_SCENE_CAMERA 128

// payloads
#define ORI_STATIC_MESH_PACKAGE_PAYLOAD			"Static_Mesh_Package_Payload"
#define ORI_DYNAMIC_MESH_PACKAGE_PAYLOAD		"Dynamic_Mesh_Package_Payload"
#define ORI_ENTITY_REPARENT_PACKAGE_PAYLOAD		"Entity_Re-Parent_Package_Payload"
#define ORI_MATERIAL_PACKAGE_PAYLOAD			"Material_Package_Payload"
#define ORI_TEXTURE_PACKAGE_PAYLOAD				"Texture_Package_Payload"

#endif // !OE1_PRE_DEF_H_
