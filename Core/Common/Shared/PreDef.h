#ifndef OE1_PRE_DEF_H_
#define OE1_PRE_DEF_H_

#include <GL/glew.h>
#include "UniformBlocks.h"


static GLuint MaxUniformBlockSize()
{
	GLint max_uniform_buff;
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max_uniform_buff);
	return max_uniform_buff;
}

#define ORI_MAX_INSTANCE_PER_MESH 2048
#define ORI_MATERIAL_PREFIX "ORMAT_"
#define ORI_UNIFORM_BLOCK_MEMORY_STRESS 256
#define ORI_MAX_MATERIAL_PER_UNIFORM_BLOCK ((MaxUniformBlockSize() / Memory::s_MaterialPropertiesBufferSize) - ORI_UNIFORM_BLOCK_MEMORY_STRESS)




#endif // !OE1_PRE_DEF_H_
