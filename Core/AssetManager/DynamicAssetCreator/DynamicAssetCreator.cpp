#include "DynamicAssetCreator.h"


namespace OE1Core
{
	ModelPkg DAC::GeometryCreator::GetSphere()
	{
		std::vector<glm::vec3> Position;
		std::vector<glm::vec3> Normal;
		std::vector<glm::vec2> UV;
		std::vector<unsigned int> Indices;

		const unsigned int X_SEGMENTS = 64;
		const unsigned int Y_SEGMENTS = 64;
		const float PI = 3.14159265359f;

		for (unsigned int x = 0; x < X_SEGMENTS; x++)
		{
			for (unsigned int y = 0; y < Y_SEGMENTS; y++)
			{
				float xSegment = (float)x / (float)X_SEGMENTS;
				float ySegment = (float)y / (float)Y_SEGMENTS;

				float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
				float yPos = std::cos(ySegment * PI);
				float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

				Position.push_back(glm::vec3(xPos, yPos, zPos));
				UV.push_back(glm::vec2(xSegment, ySegment));
				Normal.push_back(glm::vec3(xPos, yPos, zPos));
			}
		}

		bool oddRow = false;
		for (unsigned int y = 0; y < Y_SEGMENTS; y++)
		{
			if (!oddRow)
			{
				for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
				{
					Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					Indices.push_back(y * (X_SEGMENTS + 1) + x);
				}
			}
			else
			{
				// investigate here which when x is unsigned int it stuck in the loop
				for (int x = X_SEGMENTS; x >= 0; --x)
				{
					Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					Indices.push_back(y * (X_SEGMENTS + 1) + x);
				}
			}
			oddRow = !oddRow;
		}

		ModelPkg _model;

		_model.PackageID = GetPackageID();
		_model.IndicesCount = (int)Indices.size();
		_model.Name = "DGA_SPHERE_ORI";
		_model.SubMeshCount = 1;
		_model.TriangleCount = (int)_model.IndicesCount / 3;
		_model.VertexCount = (int)Position.size();

		CoreStaticMeshPkg mesh_pkg;
		mesh_pkg.VertexCount = 0;
		mesh_pkg.IndiceData = Indices;
		mesh_pkg.IndiceCount = (int)Indices.size();
		mesh_pkg.Name = "DGA_SPHERE_ORI";
		mesh_pkg.PackageID = GetPackageID();

		for (size_t i = 0; i < Position.size(); i++)
		{
			DataBlock::Vertex Vert;

			Vert.Position = Position[i];
			Vert.Normal = Normal[i];
			Vert.TextureCoordinate = UV[i];
			Vert.Color = glm::vec3(1.0f); // White
			
			Vert.Tangent = glm::vec3(1.0f);
			Vert.Bitangent = glm::vec3(1.0f);


			mesh_pkg.VertexCount++;
			mesh_pkg.VertexData.push_back(Vert);
		}

		InitGLBuffer(mesh_pkg);
		_model.MeshList.push_back(mesh_pkg);

		return _model;
	}
	int DAC::GeometryCreator::GetPackageID()
	{
		return ++s_DynamicAssetID;
	}
	void DAC::GeometryCreator::InitGLBuffer(CoreStaticMeshPkg& _core_mesh)
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
}