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

inline std::wstring ORI_ACTIVE_PROJECT_ROOT = L"";
inline const std::wstring ORI_PROJECT_ROOT_PATH = L"\\ORion";
inline std::string ORI_ACTIVE_PATH = "##";


#define ORI_MAX_INSTANCE_PER_MESH 2048
#define ORI_MATERIAL_PREFIX "ORMAT_"
#define ORI_ASSET_POSTFIX ".ORIASSET"
#define ORI_UNIFORM_BLOCK_MEMORY_STRESS 256
#define ORI_MAX_MATERIAL_PER_UNIFORM_BLOCK ((MaxUniformBlockSize() / Memory::s_MaterialPropertiesBufferSize) - ORI_UNIFORM_BLOCK_MEMORY_STRESS)



// payloads
#define ORI_STATIC_MESH_PACKAGE_PAYLOAD "Static_Mesh_Package_Payload"
#define ORI_DYNAMIC_MESH_PACKAGE_PAYLOAD "Dynamic_Mesh_Package_Payload"
#define ORI_MATERIAL_PACKAGE_PAYLOAD "Material_Package_Payload"

#endif // !OE1_PRE_DEF_H_
