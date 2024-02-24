#include "CoreGeometryLoader.h"


namespace OE1Core
{
	namespace Loader
	{
		void CoreGeometryLoader::SetTextureCheckCallback(TextureLoadCheckCallback _callback)
		{
			TextureLoaded = _callback;
		}

		LoadPackage CoreGeometryLoader::BeginLoad(LoadArgs _args)
		{
			s_LoadArgument = _args;

			LoadPackage loadPackage;
			loadPackage.LoadArg = s_LoadArgument;

			PROGRESS_INFO = "Loading to memory.."; PROGRESS_LEVEL = 0.02f;

			if (!LoadToMemory(s_LoadArgument.SourcePath))
			{
				s_Importer.FreeScene();
				PROGRESS_INFO = "Failed to load asset!"; PROGRESS_LEVEL = 1.0f;
				return loadPackage;
			}
			PROGRESS_INFO = "Unpacking Scene..."; PROGRESS_LEVEL = 0.1f;
			
			s_SceneContainAnimation = false;
			if(s_LoadArgument.HasAnimation)
				s_SceneContainAnimation = HasBoneStructure(s_Scene->mRootNode);

				loadPackage.HasValidData = true;
			if (s_SceneContainAnimation)
			{
				loadPackage.IsStaticMesh = false;
				ExtractDynamicScene(s_Scene->mRootNode, loadPackage);
			}
			else
			{
				loadPackage.IsStaticMesh = true;
				ExtractStaticScene(s_Scene->mRootNode, loadPackage);
			}
			
			s_Importer.FreeScene();
			s_TextureSignature.clear();

			return loadPackage;
		}
		
		bool CoreGeometryLoader::LoadToMemory(std::string _path)
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

		void CoreGeometryLoader::ExtractStaticScene(aiNode* _node, LoadPackage& _package)
		{
			std::vector<DataBlock::UnprocessedGeometry> geom_group_temp;

			for (unsigned int i = 0; i < _node->mNumMeshes; i++)
			{
				aiMesh* mesh = s_Scene->mMeshes[_node->mMeshes[i]];
				DataBlock::UnprocessedGeometry geom = GetSingleMesh(mesh, _package.Textures);
				geom_group_temp.push_back(geom);
			}

			if (!geom_group_temp.empty())
			{
				std::get<0>(_package.StaticMeshSet[s_MeshGroupID]) = _node->mName.C_Str();
				std::get<1>(_package.StaticMeshSet[s_MeshGroupID]) = geom_group_temp;
			}

			for (unsigned int i = 0; i < _node->mNumChildren; i++)
			{
				s_MeshGroupID++;
				ExtractStaticScene(_node->mChildren[i], _package);
			}
		}
		
		void CoreGeometryLoader::ExtractDynamicScene(aiNode* _node, LoadPackage& _package)
		{
			std::vector<DataBlock::UnprocessedDynamicGeometry> geom_group_temp;

			for (unsigned int i = 0; i < _node->mNumMeshes; i++)
			{
				aiMesh* mesh = s_Scene->mMeshes[_node->mMeshes[i]];
				DataBlock::UnprocessedGeometry static_data = GetSingleMesh(mesh, _package.Textures);
				DataBlock::UnprocessedDynamicGeometry geom = CollectSingleMeshBone(mesh, static_data, _package);
				geom_group_temp.push_back(geom);
			}

			if (!geom_group_temp.empty())
			{
				std::get<0>(_package.SkinnedMeshSet[s_MeshGroupID]) = _node->mName.C_Str();
				std::get<1>(_package.SkinnedMeshSet[s_MeshGroupID]) = geom_group_temp;
			}

			for (unsigned int i = 0; i < _node->mNumChildren; i++)
			{
				s_MeshGroupID++;
				ExtractDynamicScene(_node->mChildren[i], _package);
			}
		}
		
		DataBlock::UnprocessedGeometry CoreGeometryLoader::GetSingleMesh(aiMesh* _mesh_node, std::unordered_map<std::string, TexturePkg>& _textures_buffer)
		{

			// Progress 

			std::string mesh_name = _mesh_node->mName.C_Str();
			PROGRESS_INFO = "Unpacking ";
			PROGRESS_INFO.append(mesh_name);
			PROGRESS_LEVEL += (0.9f / (float)s_Scene->mNumMeshes);

			DataBlock::UnprocessedGeometry unprocessed_geom;
			unprocessed_geom.Name = mesh_name;

			/****************************** Loading (Position, Normal, Texture Coordinate, Tangent, Bi-Tangent) *******************************/
			for (unsigned int i = 0; i < _mesh_node->mNumVertices; i++)
			{
				OE1Core::DataBlock::Vertex vertex;

				vertex.Position = Utility::AI_TO_GLM::VECTOR(_mesh_node->mVertices[i]);

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
			unprocessed_geom.Texture = GetTextureSet(crt_mesh_material, _textures_buffer);

			/*************************************************************************/


			unprocessed_geom.MinPoint = Utility::AI_TO_GLM::VECTOR(_mesh_node->mAABB.mMin);
			unprocessed_geom.MaxPoint = Utility::AI_TO_GLM::VECTOR(_mesh_node->mAABB.mMax);;

			return unprocessed_geom;
		}
		
		DataBlock::UnprocessedDynamicGeometry CoreGeometryLoader::CollectSingleMeshBone(aiMesh* _mesh, DataBlock::UnprocessedGeometry& _static_geom, LoadPackage& _package)
		{
			DataBlock::UnprocessedDynamicGeometry unprocessed_geom;

			unprocessed_geom.Indices = _static_geom.Indices;
			unprocessed_geom.Texture = _static_geom.Texture;

			unprocessed_geom.MinPoint = _static_geom.MinPoint;
			unprocessed_geom.MaxPoint = _static_geom.MaxPoint;

			for (size_t i = 0; i < _static_geom.VertexData.size(); i++)
			{
				DataBlock::WeightedVertex weighted_vertex;
				weighted_vertex.Position			= _static_geom.VertexData[i].Position;
				weighted_vertex.Color				= _static_geom.VertexData[i].Color;
				weighted_vertex.Normal				= _static_geom.VertexData[i].Normal;
				weighted_vertex.Tangent				= _static_geom.VertexData[i].Tangent;
				weighted_vertex.Bitangent			= _static_geom.VertexData[i].Bitangent;
				weighted_vertex.TextureCoordinate	= _static_geom.VertexData[i].TextureCoordinate;

				unprocessed_geom.VertexData.push_back(weighted_vertex);
			}

			if (_mesh->HasBones())
			{
				for (size_t i = 0; i < _mesh->mNumBones; i++)
				{

					int BoneID = -1;

					aiBone* _bone = _mesh->mBones[i];
					if (_package.BoneInfoMap.find(_bone->mName.C_Str()) == _package.BoneInfoMap.end())
					{
						DataBlock::BoneInfo _bone_info;
						_bone_info.ID = _package.BoneCounter;
						_bone_info.Offset = Utility::AI_TO_GLM::AiMatrix4x4ToGlm(&_bone->mOffsetMatrix);
						_package.BoneInfoMap.insert(std::make_pair(_bone->mName.C_Str(), _bone_info));
						BoneID = _package.BoneCounter;
						_package.BoneCounter++;
					}
					else
						BoneID = _package.BoneInfoMap[_bone->mName.C_Str()].ID;

					auto bone_weights = _mesh->mBones[i]->mWeights;

					// Number of vertex affected by this bone
					size_t weight_count = (size_t)_mesh->mBones[i]->mNumWeights;

					for (size_t k = 0; k < weight_count; k++)
					{
						size_t vertex_id = (size_t)bone_weights[k].mVertexId;
						float weight = bone_weights[k].mWeight;

						// set vertex with the weights
						for (size_t j = 0; j < MAX_BONE_PER_VERTEX; j++)
						{
							if (unprocessed_geom.VertexData[vertex_id].BoneIndex[(int)j] < 0)
							{
								unprocessed_geom.VertexData[vertex_id].BoneIndex[(int)j] = (int)BoneID;
								unprocessed_geom.VertexData[vertex_id].Weight[(int)j] = weight;
								break;
							}
						}
					}

				}
			}

			return unprocessed_geom;
		}
		
		TextureSet CoreGeometryLoader::GetTextureSet(aiMaterial* _material, std::unordered_map<std::string, TexturePkg>& _textures_buffer)
		{
			TextureSet texture_set;

			RegisterSingleTexture(texture_set, DataBlock::TextureType::DIFFUSE, aiTextureType_DIFFUSE, _material, _textures_buffer);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::NORMAL, aiTextureType_NORMALS, _material, _textures_buffer);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::OPACITY, aiTextureType_OPACITY, _material, _textures_buffer);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::ROUGHNESS, aiTextureType_SHININESS, _material, _textures_buffer);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::METAL_ROUGHNESS, aiTextureType_UNKNOWN, _material, _textures_buffer);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::METAL, aiTextureType_METALNESS, _material, _textures_buffer);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::EMISSIVE, aiTextureType_EMISSIVE, _material, _textures_buffer);
			RegisterSingleTexture(texture_set, DataBlock::TextureType::AO, aiTextureType_AMBIENT_OCCLUSION, _material, _textures_buffer);

			return texture_set;
		}

		void CoreGeometryLoader::RegisterSingleTexture(
			TextureSet& _texture_set, 
			DataBlock::TextureType _oe_texture_type, 
			aiTextureType _ai_texture_type, 
			aiMaterial* _material,
			std::unordered_map<std::string, TexturePkg>& _textures_buffer)
		{
			int texture_count = _material->GetTextureCount(_ai_texture_type);
			std::string n = _material->GetName().C_Str();
			aiString texture_path;
			if (texture_count != 0)
			{
				// Read texture Path
				_material->GetTexture(_ai_texture_type, 0, &texture_path);

				std::string TextureName = GetTextureName(texture_path.C_Str());

				// Now check if the texture is loaded already 
				if (!IsTextureAlreadyLoaded(TextureName))
				{
					TexturePkg pkg;
					pkg.TexData = ReadTextureData(TextureName);
					pkg.TexType = _oe_texture_type;

					_textures_buffer.insert(std::make_pair(TextureName, pkg));

					SignTexture(TextureName, _oe_texture_type);
				}

				// We register this regardless
				_texture_set.insert(std::make_pair(TextureName, _oe_texture_type));
			}
		}
		
		DataBlock::Image2D CoreGeometryLoader::ReadTextureData(std::string _path)
		{
			// if the texture is embeded get that
			if (const aiTexture* embd_texture = s_Scene->GetEmbeddedTexture(_path.c_str()))
				return TextureLoader::OELoadImage(embd_texture);

			// If the texture is separted get that 
			std::string relative_texture_path = NameHandle::FilterPath(s_AbsPath) + _path.c_str();
			return TextureLoader::OELoadImage(relative_texture_path);
		}
		
		std::string CoreGeometryLoader::GetTextureName(std::string _path)
		{
			if (const aiTexture* embd_texture = s_Scene->GetEmbeddedTexture(_path.c_str()))
				return std::string(NameHandle::FilterFileNameExt(embd_texture->mFilename.C_Str()));

			return NameHandle::FilterFileNameExt(_path);
		}

		void CoreGeometryLoader::SignTexture(std::string _name, DataBlock::TextureType _type)
		{
			s_TextureSignature.insert(std::make_pair(_name, _type));
		}

		bool CoreGeometryLoader::HasBoneStructure(aiNode* _node)
		{
			for (unsigned int i = 0; i < _node->mNumMeshes; i++)
				if (s_Scene->mMeshes[_node->mMeshes[i]]->HasBones())
					return true;

			for (unsigned int i = 0; i < _node->mNumChildren; i++)
				if (HasBoneStructure(_node->mChildren[i]))
					return true;

			return false;
		}
		
		bool CoreGeometryLoader::IsTextureAlreadyLoaded(std::string _name)
		{
			return s_TextureSignature.find(_name) != s_TextureSignature.end();
		}
	}
}