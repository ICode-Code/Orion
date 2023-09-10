#include "AssetParser.h"
#include <STBI/stb_image.h>

namespace OE1Core
{
	std::vector<std::string> AssetParser::ParseStaticGeometry(Loader::StaticGeometryLoader::MeshSet& _mesh_set)
	{
		std::vector<std::string> packages_names;
		for (auto& iter : _mesh_set)
		{
			ModelPkg model_package;

			model_package.Name = std::get<0>(iter.second);
			model_package.PackageID = GetAssetID();

			// get geometry data
			auto& raw_geometry_data_list = std::get<1>(iter.second);

			//PreProcessGeometry(raw_geometry_data_list);
			
			for (size_t i = 0; i < raw_geometry_data_list.size(); i++)
				model_package.MeshList.push_back(ProcessGeometry(std::get<1>(iter.second)[i], model_package.PackageID));
			
			ReadModelInfo(model_package);

			AssetManager::RegisterGeometry(model_package);
			packages_names.push_back(model_package.Name);
		}

		_mesh_set.clear();
		return packages_names;
	}
	void AssetParser::ParseDynamicGeometry()
	{

	}
	void AssetParser::ReadModelInfo(ModelPkg& model_package)
	{
		glm::vec3 min_point = glm::vec3(std::numeric_limits<float>::max());
		glm::vec3 max_point = glm::vec3(std::numeric_limits<float>::lowest());

		for (size_t i = 0; i < model_package.MeshList.size(); i++)
		{
			model_package.VertexCount += model_package.MeshList[i].VertexCount;
			model_package.IndicesCount += model_package.MeshList[i].IndiceCount;
			model_package.TriangleCount += model_package.MeshList[i].TriangleCount;

			min_point.x = std::min(min_point.x, model_package.MeshList[i].MinPoint.x);
			min_point.y = std::min(min_point.y, model_package.MeshList[i].MinPoint.y);
			min_point.z = std::min(min_point.z, model_package.MeshList[i].MinPoint.z);

			max_point.x = std::max(max_point.x, model_package.MeshList[i].MaxPoint.x);
			max_point.y = std::max(max_point.y, model_package.MeshList[i].MaxPoint.y);
			max_point.z = std::max(max_point.z, model_package.MeshList[i].MaxPoint.z);
		}

		glm::vec3 center = (min_point * 0.5f) + (max_point * 0.5f);
		model_package.Extents = glm::vec3(max_point.x - center.x, max_point.y - center.y, max_point.z - center.z);
		if (model_package.Extents.y == 0.0f)
			model_package.Extents.y = 0.01f;
		model_package.SubMeshCount = (int)model_package.MeshList.size();
	}
	CoreStaticMeshPkg AssetParser::ProcessGeometry(DataBlock::UnprocessedGeometry& _unprocessed_geometry, uint32_t _package_id, bool _load_mat)
	{
		CoreStaticMeshPkg core_mesh_package;
		core_mesh_package.MaterialID = 0;
		core_mesh_package.Name = _unprocessed_geometry.Name;
		core_mesh_package.VertexData = _unprocessed_geometry.VertexData;
		core_mesh_package.IndiceData = _unprocessed_geometry.Indices;
		core_mesh_package.MaxPoint = _unprocessed_geometry.MaxPoint;
		core_mesh_package.MinPoint = _unprocessed_geometry.MinPoint;
		core_mesh_package.IndiceCount = (int)_unprocessed_geometry.Indices.size();
		core_mesh_package.TriangleCount = (int)(_unprocessed_geometry.Indices.size() / 3);
		core_mesh_package.VertexCount = (int)_unprocessed_geometry.VertexData.size();
		core_mesh_package.PackageID = _package_id;

		if (_load_mat)
			core_mesh_package.MaterialID = CreateMaterial(_unprocessed_geometry.Texture, core_mesh_package.Name);

		BufferIntilization(core_mesh_package);

		return core_mesh_package;
	}
	void AssetParser::PreProcessGeometry(std::vector<DataBlock::UnprocessedGeometry>& _unprocessed_geometres)
	{
		glm::vec3 average = glm::vec3(0.0f);
		int total_vertex = 0;
		for (size_t i = 0; i < _unprocessed_geometres.size(); i++)
		{
			DataBlock::UnprocessedGeometry& single_mesh = _unprocessed_geometres[i];
			total_vertex += (int)single_mesh.VertexData.size();
			
			for (size_t j = 0; j < single_mesh.VertexData.size(); j++)
				average += single_mesh.VertexData[j].Position;
		}
		average /= total_vertex;


		for (size_t i = 0; i < _unprocessed_geometres.size(); i++)
		{
			DataBlock::UnprocessedGeometry& single_mesh = _unprocessed_geometres[i];
			for (size_t j = 0; j < single_mesh.VertexData.size(); j++)
				single_mesh.VertexData[j].Position -= average;
		}


		for (size_t i = 0; i < _unprocessed_geometres.size(); i++)
		{
			DataBlock::UnprocessedGeometry& single_mesh = _unprocessed_geometres[i];
			for (size_t j = 0; j < single_mesh.Indices.size(); i++)
			{

			}
		}

	}
	uint32_t AssetParser::CreateMaterial(Loader::StaticGeometryLoader::TextureSet& _texture_set, std::string _mat_name)
	{

		// Which Texture exist which does not

		s_AvialTextures.HasDiffuse				= _texture_set.find(DataBlock::TextureType::DIFFUSE)			!= _texture_set.end();
		s_AvialTextures.HasNormal				= _texture_set.find(DataBlock::TextureType::NORMAL)				!= _texture_set.end();
		s_AvialTextures.HasRoughness			= _texture_set.find(DataBlock::TextureType::ROUGHNESS)			!= _texture_set.end();
		s_AvialTextures.HasMetal				= _texture_set.find(DataBlock::TextureType::METAL)				!= _texture_set.end();
		s_AvialTextures.HasRoughness_Metal		= _texture_set.find(DataBlock::TextureType::METAL_ROUGHNESS)	!= _texture_set.end();
		s_AvialTextures.HasAlphaMask			= _texture_set.find(DataBlock::TextureType::OPACITY)			!= _texture_set.end();
		s_AvialTextures.HasEmission				= _texture_set.find(DataBlock::TextureType::EMISSIVE)			!= _texture_set.end();
		s_AvialTextures.HasAo					= _texture_set.find(DataBlock::TextureType::AO)					!= _texture_set.end();


		// Decide Material type based on the provided texture
		MaterialType material_type = s_AvialTextures.GetMaterialType();


		// Generate Shader Code based on the provided texture
		std::string vertex_shader = ShaderGenerator::GetStandardVertexShader();
		std::string fragment_shader = ShaderGenerator::GetForwardPixelShader(s_AvialTextures);

		// Generate the Material
		// This alloacted shader is managed by the material, so it will delete it, no need to worry
		MasterMaterial* master_material = MaterialManager::RegisterMaterial(_mat_name, new Shader(vertex_shader, fragment_shader));


		// if the material type is default which means there is no texture we can return here
		if(material_type == MaterialType::DEFAULT)
			return master_material->GetOffset();

		// other wise we can start processing textures

		int available_texture_count = (int)_texture_set.size();

		GLuint color_map_texture;
		GLuint non_color_map_texture;

		if (s_AvialTextures.HasDiffuse || s_AvialTextures.HasEmission)
		{
			glGenTextures(1, &color_map_texture);
			master_material->SetColorMapTexture(color_map_texture);
		}
		

		Memory::TextureAccessIndex& taidx = master_material->GetTAI();


		///////////////////////// COLOR MAPS

		if (s_AvialTextures.HasDiffuse && s_AvialTextures.HasEmission)
		{
			auto& diffuse_texture = std::get<1>(_texture_set[DataBlock::TextureType::DIFFUSE]);
			
			// Allocate memory
			glBindTexture(GL_TEXTURE_2D_ARRAY, color_map_texture);
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_SRGB_ALPHA, diffuse_texture.Width, diffuse_texture.Height, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			available_texture_count--;
			ReadTextureData(diffuse_texture, 0, _mat_name);
			taidx.Color = 0;

			available_texture_count--;
			ReadTextureData(std::get<1>(_texture_set[DataBlock::TextureType::EMISSIVE]), 1, _mat_name);
			taidx.Emission = 1;
		}
		else if (s_AvialTextures.HasDiffuse && !s_AvialTextures.HasEmission)
		{
			auto& diffuse_texture = std::get<1>(_texture_set[DataBlock::TextureType::DIFFUSE]);
			// Allocate memory
			glBindTexture(GL_TEXTURE_2D_ARRAY, color_map_texture);
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_SRGB_ALPHA, diffuse_texture.Width, diffuse_texture.Height, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			available_texture_count--;
			ReadTextureData(diffuse_texture, 0, _mat_name);
			taidx.Color = 0;

		}
		else if (s_AvialTextures.HasEmission)
		{
			auto& emissive_texture = std::get<1>(_texture_set[DataBlock::TextureType::EMISSIVE]);
			// Allocate memory
			glBindTexture(GL_TEXTURE_2D_ARRAY, color_map_texture);
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_SRGB_ALPHA, emissive_texture.Width, emissive_texture.Height, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			available_texture_count--;
			ReadTextureData(emissive_texture, 0, _mat_name);
			taidx.Color = 0;
		}



		/////////////////////////////////////////////////////// NON-COLOR

		if (available_texture_count > 0)
		{
			glGenTextures(1, &non_color_map_texture);
			master_material->SetNonColorMapTexture(non_color_map_texture);

			int non_color_texture_index = 0;

			glm::vec2 texture_size = GrabTextureSize(_texture_set);

			glBindTexture(GL_TEXTURE_2D_ARRAY, non_color_map_texture);
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, (GLsizei)texture_size.x, (GLsizei)texture_size.y, (GLsizei)available_texture_count, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			if (s_AvialTextures.HasNormal)
			{
				ReadTextureData(std::get<1>(_texture_set[DataBlock::TextureType::NORMAL]), non_color_texture_index, _mat_name);
				taidx.Normal = non_color_texture_index++;
			}
			if (s_AvialTextures.HasRoughness_Metal)
			{
				ReadTextureData(std::get<1>(_texture_set[DataBlock::TextureType::METAL_ROUGHNESS]), non_color_texture_index, _mat_name);
				taidx.RoughnessMetal = non_color_texture_index++;
			}
			else
			{
				if (s_AvialTextures.HasRoughness)
				{
					ReadTextureData(std::get<1>(_texture_set[DataBlock::TextureType::ROUGHNESS]), non_color_texture_index, _mat_name);
					taidx.Roughness = non_color_texture_index++;
				}
				if (s_AvialTextures.HasMetal)
				{
					ReadTextureData(std::get<1>(_texture_set[DataBlock::TextureType::METAL]), non_color_texture_index, _mat_name);
					taidx.Metal = non_color_texture_index++;
				}
			}

			if (s_AvialTextures.HasAlphaMask)
			{
				ReadTextureData(std::get<1>(_texture_set[DataBlock::TextureType::OPACITY]), non_color_texture_index, _mat_name);
				taidx.AlphaMask = non_color_texture_index++;
			}
			if (s_AvialTextures.HasAo)
			{
				ReadTextureData(std::get<1>(_texture_set[DataBlock::TextureType::AO]), non_color_texture_index, _mat_name);
				taidx.AmbientOcclusion = non_color_texture_index++;
			}
		}


		return master_material->GetOffset();
	}
	void AssetParser::ReadTextureData(const DataBlock::Image2D& _image, int _layer, std::string _mat_name)
	{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, _layer, _image.Width, _image.Height, 1, GL_RGBA, GL_UNSIGNED_BYTE, _image.Data);
		Texture2DFilter();
		// Clean memory
		stbi_image_free(_image.Data);
	}
	glm::vec2 AssetParser::GrabTextureSize(Loader::StaticGeometryLoader::TextureSet& _texture_set)
	{
		if (s_AvialTextures.HasNormal)
		{
			auto& _texture = std::get<1>(_texture_set[DataBlock::TextureType::NORMAL]);
			return glm::vec2(_texture.Width, _texture.Height);
		}
		if (s_AvialTextures.HasRoughness_Metal)
		{
			auto& _texture = std::get<1>(_texture_set[DataBlock::TextureType::METAL_ROUGHNESS]);
			return glm::vec2(_texture.Width, _texture.Height);
		}
		else
		{
			if (s_AvialTextures.HasMetal)
			{
				auto& _texture = std::get<1>(_texture_set[DataBlock::TextureType::METAL]);
				return glm::vec2(_texture.Width, _texture.Height);
			}
			if (s_AvialTextures.HasRoughness)
			{
				auto& _texture = std::get<1>(_texture_set[DataBlock::TextureType::ROUGHNESS]);
				return glm::vec2(_texture.Width, _texture.Height);
			}
		}
		if (s_AvialTextures.HasAlphaMask)
		{
			auto& _texture = std::get<1>(_texture_set[DataBlock::TextureType::OPACITY]);
			return glm::vec2(_texture.Width, _texture.Height);
		}
		if (s_AvialTextures.HasAo)
		{
			auto& _texture = std::get<1>(_texture_set[DataBlock::TextureType::AO]);
			return glm::vec2(_texture.Width, _texture.Height);
		}

		return glm::vec2(0.0f, 0.0f);
	}
	void AssetParser::Texture2DFilter()
	{
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY, 2);
	}
	void AssetParser::BufferIntilization(CoreStaticMeshPkg& _core_mesh)
	{
		glGenVertexArrays(1, &_core_mesh.VAO);
		glBindVertexArray(_core_mesh.VAO);

		glGenBuffers(1, &_core_mesh.VBO);
		glGenBuffers(1, &_core_mesh.EBO);
		glGenBuffers(1, &_core_mesh.IBO);


		glBindBuffer(GL_ARRAY_BUFFER, _core_mesh.VBO);
		glBufferData(GL_ARRAY_BUFFER, _core_mesh.VertexData.size() * sizeof(OE1Core::DataBlock::Vertex), &_core_mesh.VertexData[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _core_mesh.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _core_mesh.IndiceData.size() * sizeof(uint32_t), &_core_mesh.IndiceData[0], GL_STATIC_DRAW);


		// Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OE1Core::DataBlock::Vertex), (void*)0);

		// Color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(OE1Core::DataBlock::Vertex), (void*)offsetof(DataBlock::Vertex, DataBlock::Vertex::Color));

		// Normal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(OE1Core::DataBlock::Vertex), (void*)offsetof(DataBlock::Vertex, DataBlock::Vertex::Normal));

		// Texture Coordinate
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(OE1Core::DataBlock::Vertex), (void*)offsetof(DataBlock::Vertex, DataBlock::Vertex::TextureCoordinate));

		// Tangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(OE1Core::DataBlock::Vertex), (void*)offsetof(DataBlock::Vertex, DataBlock::Vertex::Tangent));

		// Bi-Tangent
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(OE1Core::DataBlock::Vertex), (void*)offsetof(DataBlock::Vertex, DataBlock::Vertex::Bitangent));

		glBindBuffer(GL_ARRAY_BUFFER, _core_mesh.IBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(StaticMeshInstancePkg) * ORI_MAX_INSTANCE_PER_MESH, NULL, GL_STATIC_DRAW);



		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(StaticMeshInstancePkg), (void*)0);
		glEnableVertexAttribArray(7);
		glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(StaticMeshInstancePkg), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(8);
		glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(StaticMeshInstancePkg), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(9);
		glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(StaticMeshInstancePkg), (void*)(3 * sizeof(glm::vec4)));


		glEnableVertexAttribArray(10);
		glVertexAttribIPointer(10, 1, GL_INT, sizeof(StaticMeshInstancePkg), (void*)offsetof(StaticMeshInstancePkg, StaticMeshInstancePkg::RenderID));

		glEnableVertexAttribArray(11);
		glVertexAttribIPointer(11, 1, GL_INT, sizeof(StaticMeshInstancePkg), (void*)offsetof(StaticMeshInstancePkg, StaticMeshInstancePkg::MaterialID));
	

		glVertexAttribDivisor(6, 1); //
		glVertexAttribDivisor(7, 1); // Instance Materix
		glVertexAttribDivisor(8, 1); //
		glVertexAttribDivisor(9, 1); //

		glVertexAttribDivisor(10, 1); // Render ID
		glVertexAttribDivisor(11, 1); // Material ID


		glBindVertexArray(0);
	}
	uint32_t AssetParser::GetAssetID() { return ++s_ASSET_ID; };
}