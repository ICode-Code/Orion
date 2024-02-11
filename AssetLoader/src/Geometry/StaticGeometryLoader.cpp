#include "StaticGeometryLoader.h"


namespace OE1Core
{
	namespace Loader
	{
		StaticGeometryLoader::StaticGeometryLoader()
		{

		}
		StaticGeometryLoader::~StaticGeometryLoader()
		{

		}

		void StaticGeometryLoader::OELoadStaticGeometry(std::string _path, MeshSet& _mesh_set, std::unordered_map<std::string, TexturePkg>& _tex_buffer)
		{
			PROGRESS_INFO = "Loading to memory.."; PROGRESS_LEVEL = 0.02f;

			if (!LoadToMemory(_path))
			{
				s_Importer.FreeScene();
				PROGRESS_INFO = "Failed to load asset!"; PROGRESS_LEVEL = 1.0f;
				return;
			}
			PROGRESS_INFO = "Unpacking Scene..."; PROGRESS_LEVEL = 0.1f;
			ExtractScene(s_Scene->mRootNode, _mesh_set);
			_tex_buffer = s_LoadedTexture;
			s_LoadedTexture.clear();
			s_Importer.FreeScene();
		}

		bool StaticGeometryLoader::LoadToMemory(std::string _path)
		{
			s_AbsPath = _path;

			s_Scene = s_Importer.ReadFile(
				s_AbsPath,
				aiProcess_Triangulate |
				aiProcess_GenSmoothNormals |
				aiProcess_FlipUVs |
				aiProcess_CalcTangentSpace
			);

			if (!s_Scene || !s_Scene->mRootNode)
			{
				LOG_ERROR("Failed to load model from path: {0}", s_AbsPath);
				return false;
			}

			return true;
		}
		void StaticGeometryLoader::ExtractScene(aiNode* _node, MeshSet& _mesh_set)
		{
			std::vector<DataBlock::UnprocessedGeometry> geom_group_temp;

			for (unsigned int i = 0; i < _node->mNumMeshes; i++)
			{
				aiMesh* mesh = s_Scene->mMeshes[_node->mMeshes[i]];
				DataBlock::UnprocessedGeometry geom = GetSingleMesh(mesh);
				geom_group_temp.push_back(geom);
			}

			if (!geom_group_temp.empty())
			{
				std::get<0>(_mesh_set[s_MeshGroupID]) = _node->mName.C_Str();
				std::get<1>(_mesh_set[s_MeshGroupID]) = geom_group_temp;
			}

			for (unsigned int i = 0; i < _node->mNumChildren; i++)
			{
				s_MeshGroupID++;
				ExtractScene(_node->mChildren[i], _mesh_set);
			}

		}
		DataBlock::UnprocessedGeometry StaticGeometryLoader::GetSingleMesh(aiMesh* _mesh_node)
		{

			// Progress 

			std::string mesh_name = _mesh_node->mName.C_Str();
			PROGRESS_INFO = "Unpacking "; 
			PROGRESS_INFO.append(mesh_name);
			PROGRESS_LEVEL += (0.9f / (float)s_Scene->mNumMeshes);

			DataBlock::UnprocessedGeometry unprocessed_geom;
			unprocessed_geom.Name = mesh_name;

			/// This will help us when we need to create some kind of collesion box
			glm::vec3 minPoint = glm::vec3(std::numeric_limits<float>::max());
			glm::vec3 maxPoint = glm::vec3(std::numeric_limits<float>::lowest());


			/****************************** Loading (Position, Normal, Texture Coordinate, Tangent, Bi-Tangent) *******************************/
			for (unsigned int i = 0; i < _mesh_node->mNumVertices; i++)
			{
				OE1Core::DataBlock::Vertex vertex;

				vertex.Position = Utility::AI_TO_GLM::VECTOR(_mesh_node->mVertices[i]);

				{ // Get Min and Max
					glm::vec3 _pos = vertex.Position;

					minPoint.x = std::min(minPoint.x, _pos.x);
					minPoint.y = std::min(minPoint.y, _pos.y);
					minPoint.z = std::min(minPoint.z, _pos.z);

					maxPoint.x = std::max(maxPoint.x, _pos.x);
					maxPoint.y = std::max(maxPoint.y, _pos.y);
					maxPoint.z = std::max(maxPoint.z, _pos.z);
				}

				vertex.Normal = Utility::AI_TO_GLM::VECTOR(_mesh_node->mNormals[i]);

				if (_mesh_node->mTextureCoords[0])
					vertex.TextureCoordinate = Utility::AI_TO_GLM::VECTOR(_mesh_node->mTextureCoords[0][i]);
				else
					vertex.TextureCoordinate = glm::vec2(1.0f);

				if (_mesh_node->HasTangentsAndBitangents())
				{
					vertex.Tangent = Utility::AI_TO_GLM::VECTOR(_mesh_node->mTangents[i]);
					vertex.Bitangent = Utility::AI_TO_GLM::VECTOR(_mesh_node->mBitangents[i]);
				}


				if (_mesh_node->HasVertexColors(0))
				{
					// Read vertex color data
					aiColor4D color = _mesh_node->mColors[0][i];
					vertex.Color = glm::vec3(color.r, color.g, color.b);
				}
				else
				{
					// Default color if vertex colors are not present
					vertex.Color = glm::vec3(0.5f);
				}

				unprocessed_geom.VertexData.push_back(vertex);
			}
			/*************************************************************************************/


			/************************ Load (Indices) **************************************/
			for (unsigned int i = 0; i < _mesh_node->mNumFaces; i++)
			{
				aiFace face = _mesh_node->mFaces[i];

				for (unsigned int k = 0; k < face.mNumIndices; k++)
					unprocessed_geom.Indices.push_back(face.mIndices[k]);
			}
			/*************************************************************************/

			/*****************************  Deal With Textures ****************************/

			// Get Material Reference
			aiMaterial* crt_mesh_material = s_Scene->mMaterials[_mesh_node->mMaterialIndex];
			unprocessed_geom.Texture = GetTextureSet(crt_mesh_material);

			/*************************************************************************/


			unprocessed_geom.MinPoint = minPoint;
			unprocessed_geom.MaxPoint = maxPoint;

			return unprocessed_geom;
		}

		StaticGeometryLoader::TextureSet StaticGeometryLoader::GetTextureSet(aiMaterial* _material)
		{
			TextureSet texture_set;

			RegisterSingleTexture(texture_set, DataBlock::TextureType::DIFFUSE,				aiTextureType_DIFFUSE,				_material);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::NORMAL,				aiTextureType_NORMALS,				_material);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::OPACITY,				aiTextureType_OPACITY,				_material);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::ROUGHNESS,			aiTextureType_SHININESS,			_material);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::METAL_ROUGHNESS,		aiTextureType_UNKNOWN,				_material);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::METAL,				aiTextureType_METALNESS,			_material);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::EMISSIVE,			aiTextureType_EMISSIVE,				_material);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::AO,					aiTextureType_AMBIENT_OCCLUSION,	_material);

			return texture_set;
		}
		void StaticGeometryLoader::RegisterSingleTexture(TextureSet& _texture_set, DataBlock::TextureType _oe_texture_type, aiTextureType _ai_texture_type, aiMaterial* _material)
		{
			int texture_count = _material->GetTextureCount(_ai_texture_type);
			std::string n = _material->GetName().C_Str();
			aiString texture_path;
			if (texture_count != 0)
			{
				// Read texture Path
				_material->GetTexture(_ai_texture_type, 0, &texture_path);

				std::string TextureName = GetTextureName(texture_path.C_Str());
				if (!IsTextureAlreadyLoaded(TextureName))
				{
					RegisterTexture(TextureName, _oe_texture_type, ReadTextureData(TextureName));
				}

				_texture_set.insert(std::make_pair(TextureName, _oe_texture_type));
			}
		}
		DataBlock::Image2D StaticGeometryLoader::ReadTextureData(std::string _path)
		{
			// if the texture is embeded get that
			if (const aiTexture* embd_texture = s_Scene->GetEmbeddedTexture(_path.c_str()))
				return TextureLoader::OELoadImage(embd_texture);

			// If the texture is separted get that 
			std::string relative_texture_path = NameHandle::FilterPath(s_AbsPath) + _path.c_str();
			return TextureLoader::OELoadImage(relative_texture_path);
		}
		std::string StaticGeometryLoader::GetTextureName(std::string _path)
		{
			if (const aiTexture* embd_texture = s_Scene->GetEmbeddedTexture(_path.c_str()))
				return std::string(embd_texture->mFilename.C_Str());

			return NameHandle::FilterFileNameExt(_path);
		}
		bool StaticGeometryLoader::IsTextureAlreadyLoaded(std::string _name)
		{
			return s_LoadedTexture.find(_name) != s_LoadedTexture.end();
		}
		TexturePkg StaticGeometryLoader::GetLoadedTexture(std::string _name)
		{
			return s_LoadedTexture[_name];
		}
		void StaticGeometryLoader::RegisterTexture(std::string _name, DataBlock::TextureType _type, DataBlock::Image2D _image)
		{
			TexturePkg pkg;
			pkg.TexData = _image;
			pkg.TexType = _type;

			s_LoadedTexture.insert(std::make_pair(_name, pkg));
		}
	}
}