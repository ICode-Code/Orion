#ifndef OE1_DATA_BLOCK_H_
#define OE1_DATA_BLOCK_H_

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>


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
			glm::vec3 TextureCoordinate;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
			glm::ivec4 BoneIndex;
			glm::vec3 Weight;
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

		struct UnprocessedGeometry
		{
			std::vector<Vertex> VertexData;
			std::unordered_map<std::string, TextureType> Texture;
			std::vector<uint32_t> Indices;
			std::string Name;
			glm::vec3 MinPoint;
			glm::vec3 MaxPoint;
		};

	}
}

#endif // !OE1_DATA_BLOCK_H_
