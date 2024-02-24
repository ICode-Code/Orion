#ifndef OE1_DATA_BLOCK_H_
#define OE1_DATA_BLOCK_H_

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <map>

#define MAX_BONE_PER_VERTEX 4

namespace OE1Core
{
	namespace DataBlock
	{

		enum TextureType
		{
			DIFFUSE = 0,
			NORMAL,
			METAL,
			ROUGHNESS,
			METAL_ROUGHNESS,
			OPACITY,
			EMISSIVE,
			AO,
			SPECULAR,
			SHADOW,
			REFLECTION,
			TRANSLUCENCY
		};

		struct TreeVertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TextureCoordinate;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
		};

		struct GrassVertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TextureCoordinate;
		};

		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Color;
			glm::vec3 Normal;
			glm::vec2 TextureCoordinate;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
		};

		struct WeightedVertex
		{
			glm::vec3 Position;
			glm::vec3 Color;
			glm::vec3 Normal;
			glm::vec2 TextureCoordinate;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;

			glm::ivec4 BoneIndex =	glm::ivec4(-1, -1, -1, -1);
			glm::vec4 Weight =		glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		};

		struct Image2D
		{
			unsigned char* Data = nullptr;
			int Width = -1;
			int Height = -1;
			int Channel = -1;
			std::string Name = "";
			std::string Path = "";
			bool Valid = false;
		};
		struct Image2DArray
		{
			std::vector<Image2D> ImageDataArray;
		};
		struct ImageHDRI
		{
			float* Data = nullptr;
			int Width = -1;
			int Height = -1;
			int Channel = -1;
			std::string Name = "";
			std::string Path = "";
			bool Valid = false;
		};

		/// <summary>
		/// This guy hold information about StaticMesh 
		/// this is a temporary state for the mesh adta this will be transformed into StaticMesh Class
		/// that can be rendered
		/// </summary>
		struct UnprocessedGeometry
		{
			std::vector<Vertex> VertexData;
			/// <summary>
			/// This Texture buffer does not hold and actual image data just it's
			/// name and type, in the parseing stage we identify it name and quere the actuall texture data
			/// rembmber NAME and TYPE ONLY
			/// </summary>
			std::unordered_map<std::string, TextureType> Texture;
			std::vector<uint32_t> Indices;
			std::string Name;
			glm::vec3 MinPoint;
			glm::vec3 MaxPoint;
		};
		struct BoneInfo
		{
			int ID = -1;
			glm::mat4 Offset = glm::mat4(1.0f);
		};

		using BoneMap = std::map<std::string, BoneInfo>;

		struct UnprocessedDynamicGeometry
		{
			BoneMap BoneIDMap;
			std::vector<WeightedVertex> VertexData;
			std::vector<uint32_t> Indices;
			/// <summary>
			/// This Texture buffer does not hold and actual image data just it's
			/// name and type, in the parseing stage we identify it name and quere the actuall texture data
			/// rembmber NAME and TYPE ONLY
			/// </summary>
			std::unordered_map<std::string, TextureType> Texture;
			uint32_t BoneCount;
			std::string Name;
			glm::vec3 MinPoint;
			glm::vec3 MaxPoint;
		};

	}
}

#endif // !OE1_DATA_BLOCK_H_
