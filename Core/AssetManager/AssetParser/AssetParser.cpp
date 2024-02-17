#include "AssetParser.h"
#include <STBI/stb_image.h>

namespace OE1Core
{
	std::vector<std::string> AssetParser::ParseStaticGeometry(Loader::StaticGeometryLoader::MeshSet& _mesh_set, std::unordered_map<std::string, Loader::TexturePkg>& _texture_buffer)
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
				model_package.MeshList.push_back(ProcessGeometry(std::get<1>(iter.second)[i], _texture_buffer, model_package.PackageID, (uint32_t)i));
			
			ReadModelInfo(model_package);

			std::string reg_name = AssetManager::RegisterGeometry(model_package);
			packages_names.push_back(reg_name);
		}

		_mesh_set.clear();
		return packages_names;
	}
	//std::vector<std::string> AssetParser::ParseStaticGeometryI(Loader::StaticGeometryLoader::MeshSet& _mesh_set, DynamicAssetType _type)
	//{
	//	std::vector<std::string> packages_names;
	//	for (auto& iter : _mesh_set)
	//	{
	//		ModelPkg model_package;

	//		model_package.Name = std::get<0>(iter.second);
	//		model_package.PackageID = GetAssetID();

	//		// get geometry data
	//		auto& raw_geometry_data_list = std::get<1>(iter.second);

	//		//PreProcessGeometry(raw_geometry_data_list);

	//		for (size_t i = 0; i < raw_geometry_data_list.size(); i++)
	//			model_package.MeshList.push_back(ProcessGeometry(std::get<1>(iter.second)[i], model_package.PackageID, (uint32_t)i,  false));

	//		ReadModelInfo(model_package);

	//		AssetManager::RegisterGeometryI(model_package, _type);
	//		packages_names.push_back(model_package.Name);
	//	}

	//	_mesh_set.clear();
	//	return packages_names;
	//}
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
	CoreStaticMeshPkg AssetParser::ProcessGeometry(DataBlock::UnprocessedGeometry& _unprocessed_geometry, std::unordered_map<std::string, Loader::TexturePkg>& _texture_buffer, uint32_t _package_id, uint32_t _local_id, bool _load_mat)
	{
		CoreStaticMeshPkg core_mesh_package;
		core_mesh_package.LocalID = _local_id;
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


		BufferIntilization(core_mesh_package);


		if (_load_mat)
		{
			CreateMaterial(_unprocessed_geometry.Texture, _texture_buffer, core_mesh_package.Name, core_mesh_package.LocalID, core_mesh_package.PackageID);
		}
		
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
	void AssetParser::CreateMaterial(Loader::StaticGeometryLoader::TextureSet& _textures, std::unordered_map<std::string, Loader::TexturePkg>& _texture_buffer, std::string _mat_name, uint32_t _local_id, uint32_t _pkg_id)
	{

		// Which Texture exist which does not
		MaterialTextureAvailFlags texture_avial_flag;

		texture_avial_flag.HasColor				= s_AvialTextures.HasDiffuse				= HasTexture(DataBlock::TextureType::DIFFUSE,			_textures);
		texture_avial_flag.HasEmission			= s_AvialTextures.HasEmission				= HasTexture(DataBlock::TextureType::EMISSIVE,			_textures);
		texture_avial_flag.HasNormal			= s_AvialTextures.HasNormal					= HasTexture(DataBlock::TextureType::NORMAL,			_textures);
		texture_avial_flag.HasMetal				= s_AvialTextures.HasMetal					= HasTexture(DataBlock::TextureType::METAL,				_textures);
		texture_avial_flag.HasRoughness			= s_AvialTextures.HasRoughness				= HasTexture(DataBlock::TextureType::ROUGHNESS,			_textures);
		texture_avial_flag.HasMetalRoughness	= s_AvialTextures.HasRoughness_Metal		= HasTexture(DataBlock::TextureType::METAL_ROUGHNESS,	_textures);
		texture_avial_flag.HasAO				= s_AvialTextures.HasAo						= HasTexture(DataBlock::TextureType::AO,				_textures);
		texture_avial_flag.HasAlpha				= s_AvialTextures.HasAlphaMask				= HasTexture(DataBlock::TextureType::OPACITY,			_textures);

		// Build Texture Map
		std::unordered_map<DataBlock::TextureType, DataBlock::Image2D> Textures;

		if(texture_avial_flag.HasColor)
			FetchTexture(GetTextureName(DataBlock::TextureType::DIFFUSE, _textures), DataBlock::TextureType::DIFFUSE,		_texture_buffer, Textures);
		if(texture_avial_flag.HasEmission)
			FetchTexture(GetTextureName(DataBlock::TextureType::EMISSIVE, _textures), DataBlock::TextureType::EMISSIVE,			_texture_buffer, Textures);
		if(texture_avial_flag.HasNormal)
			FetchTexture(GetTextureName(DataBlock::TextureType::NORMAL, _textures), DataBlock::TextureType::NORMAL,			_texture_buffer, Textures);
		if(texture_avial_flag.HasMetal)
			FetchTexture(GetTextureName(DataBlock::TextureType::METAL, _textures), DataBlock::TextureType::METAL,				_texture_buffer, Textures);
		if(texture_avial_flag.HasRoughness)
			FetchTexture(GetTextureName(DataBlock::TextureType::ROUGHNESS, _textures), DataBlock::TextureType::ROUGHNESS,				_texture_buffer, Textures);
		if(texture_avial_flag.HasMetalRoughness)
			FetchTexture(GetTextureName(DataBlock::TextureType::METAL_ROUGHNESS, _textures), DataBlock::TextureType::METAL_ROUGHNESS,			_texture_buffer, Textures);
		if(texture_avial_flag.HasAO)
			FetchTexture(GetTextureName(DataBlock::TextureType::AO, _textures), DataBlock::TextureType::AO,	_texture_buffer, Textures);
		if(texture_avial_flag.HasAlpha)
			FetchTexture(GetTextureName(DataBlock::TextureType::OPACITY, _textures), DataBlock::TextureType::OPACITY,			_texture_buffer, Textures);

		
		CommandDef::MaterialCreationCommandDef command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));

		command.TargetMeshID = _pkg_id;
		command.LocalSubMeshID = _local_id;

		command.AvialTextures = s_AvialTextures;
		command.MaterialName = _mat_name;
		command.TextureFlag = texture_avial_flag;
		command.TextureCount.CountAvialTexture(texture_avial_flag);
		command.Textuers = Textures;
		
		Command::PushMaterialCreationCommand(command);
	}
	void AssetParser::ReadTextureData(DataBlock::Image2D& _image, int _layer, std::string _mat_name)
	{
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, _layer, _image.Width, _image.Height, 1, GL_RGBA, GL_UNSIGNED_BYTE, _image.Data);
		Texture2DFilter();
		// Clean memory
		Command::PushTextureLoadCommand(_image);
	}
	bool AssetParser::FetchTexture(std::string _name, DataBlock::TextureType _type, std::unordered_map<std::string, Loader::TexturePkg>& _buffer, std::unordered_map<DataBlock::TextureType, DataBlock::Image2D>& _dest)
	{
		for (auto iter = _buffer.begin(); iter != _buffer.end(); iter++)
		{
			if (iter->second.TexData.Name == _name)
			{
				_dest.insert(std::make_pair(iter->second.TexType, iter->second.TexData));
				return true;
			}
		}

		return false;
	}
	bool AssetParser::HasTexture(DataBlock::TextureType _type, Loader::StaticGeometryLoader::TextureSet& _buff)
	{
		for (auto iter = _buff.begin(); iter != _buff.end(); iter++)
			if (iter->second == _type)
				return true;

		return false;
	}
	std::string AssetParser::GetTextureName(DataBlock::TextureType _type, Loader::StaticGeometryLoader::TextureSet& _buff)
	{
		for (auto iter = _buff.begin(); iter != _buff.end(); iter++)
			if (iter->second == _type)
				return iter->first;

		return std::string("%%NO_TEXTURE_FOUND%%");
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