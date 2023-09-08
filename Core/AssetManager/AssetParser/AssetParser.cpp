#include "AssetParser.h"


namespace OE1Core
{
	void AssetParser::ParseStaticGeometry(Loader::StaticGeometryLoader::MeshSet& _mesh_set)
	{

		for (auto& iter : _mesh_set)
		{
			ModelPkg model_package;

			model_package.Name = std::get<0>(iter.second);
			model_package.PackageID = GetAssetID();

			// get geometry data
			auto& raw_geometry_data_list = std::get<1>(iter.second);

			for (size_t i = 0; i < raw_geometry_data_list.size(); i++)
				model_package.MeshList.push_back(ProcessGeometry(std::get<1>(iter.second)[i], model_package.PackageID));

		}

	}
	void AssetParser::ParseDynamicGeometry()
	{

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
		core_mesh_package.TriangleCount = (int)(_unprocessed_geometry.Indices.size() / 3);
		core_mesh_package.VertexCount = (int)_unprocessed_geometry.VertexData.size();
		core_mesh_package.PackageID = _package_id;

		if (_load_mat)
			core_mesh_package.MaterialID = CreateMaterial(_unprocessed_geometry.Texture);

		BufferIntilization(core_mesh_package);

		return core_mesh_package;
	}
	uint32_t AssetParser::CreateMaterial(Loader::StaticGeometryLoader::TextureSet& _texture_set)
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


		// Now we can generate the nessary textures
		




		return 0;
	}
	void AssetParser::Texture2DFilter()
	{

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