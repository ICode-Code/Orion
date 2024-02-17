#include "CommandMasterOperationExecutionHandler.h"
#include "LogUI.h"
#include "../GUI/Viewport/DynamicViewportManager/DynamicViewportManager.h"

namespace OE1Core
{
	namespace CommandHnd
	{
		CommandMasterOperationExecutionHandle::CommandMasterOperationExecutionHandle(Scene* _scene)
			: ExecutionHandleBase{_scene}
		{

		}
		CommandMasterOperationExecutionHandle::~CommandMasterOperationExecutionHandle() {  }


		void CommandMasterOperationExecutionHandle::ProcessQueue()
		{
			ProcessAssetLoadCommands();
			ProcessPurgeDynamicViewportCommand();
			ProcessMaterialCreationCommand();

		}


		// Process
		void CommandMasterOperationExecutionHandle::ProcessPurgeDynamicViewportCommand()
		{
			while (!Command::s_DyanmicViewportPurgeCommands.empty())
			{
				auto& commandX = Command::s_DyanmicViewportPurgeCommands.front();
				DynamicViewportManager::PurgeDynamicViewport(commandX.Name);
				Command::s_DyanmicViewportPurgeCommands.pop();
			}
		}
		void CommandMasterOperationExecutionHandle::ProcessAssetLoadCommands()
		{
			while (!Command::s_Load3DAssetCommands.empty())
			{
				Command::s_ThreadInfoLayerNotifyCallback(true);
				auto commandX = Command::s_Load3DAssetCommands.front();
				
				Loader::GeometryLoader::LoadGeometry(commandX);

				Command::s_Load3DAssetCommands.pop();

				std::this_thread::sleep_for(0.5s);
			}
		}
		void CommandMasterOperationExecutionHandle::ProcessMaterialCreationCommand()
		{
			// Get the initial count of material creation commands
			const size_t command_count = Command::s_MaterialCreationCommands.size();
			size_t visited_commands = 0;

			// Process material creation commands until the queue is empty
			while (!Command::s_MaterialCreationCommands.empty())
			{
				// Increment the visited commands count
				visited_commands++;

				// Retrieve the next material creation command
				auto& commandX = Command::s_MaterialCreationCommands.front();

				// Skip commands that are not ready
				if (!commandX.Lock)
				{
					// If all commands have been visited and none are ready, exit the loop
					if (visited_commands >= command_count)
						break;
					continue;
				}

				// Query the target mesh
				ModelPkg* TARGET_MESH = AssetManager::GetGeometry(commandX.TargetMeshID);

				if (TARGET_MESH)
				{
					bool same_material_found = false;

					// Check if a material with the same texture exists
					if (commandX.TextureFlag.HasColor)
					{
						MasterMaterial* _same_Master_material = nullptr;
						Texture* query_texture = AssetManager::GetTexture(commandX.Textuers[DataBlock::TextureType::DIFFUSE].Name);
						if (query_texture)
						{
							auto& associate_material_offset = query_texture->AssociateMaterialOffset();
							for (size_t i = 0; i < associate_material_offset.size(); i++)
							{
								_same_Master_material = MaterialManager::GetMaterial(associate_material_offset[i]);
								if (_same_Master_material)
									break;
							}

							if (_same_Master_material)
							{
								same_material_found = true;
								AssignMaterial(TARGET_MESH, _same_Master_material, commandX.LocalSubMeshID);
							}
						}
					}

					if (!same_material_found)
					{
						// Identify material type based on available textures
						MaterialType MATERIAL_TYPE = commandX.AvialTextures.GetMaterialType();

						// Prepare shaders based on the material type
						std::string VERTEX_SHADER = ShaderGenerator::GetStandardVertexShader();
						std::string VERTEX_SHADER_PROXY = ShaderGenerator::GetStandardProxyVertexShader();
						std::string FRAGMENT_SHADER = ShaderGenerator::GetForwardPixelShader(commandX.AvialTextures);

						// Create Master Material
						MasterMaterial* MASTER_MATERIAL = MaterialManager::RegisterMaterial(
							commandX.MaterialName, new Shader(VERTEX_SHADER.c_str(), FRAGMENT_SHADER.c_str(), VERTEX_SHADER_PROXY.c_str())
						);

						// Assign textures to the material and update it
						if (MATERIAL_TYPE == MaterialType::DEFAULT)
						{
							MASTER_MATERIAL->Update();
							AssignMaterial(TARGET_MESH, MASTER_MATERIAL, commandX.LocalSubMeshID);
						}
						else
						{
							// Register and assign textures based on flags
							if (commandX.TextureFlag.HasColor)
								MASTER_MATERIAL->RegisterAlbedoMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::DIFFUSE]));
							if (commandX.TextureFlag.HasNormal)
								MASTER_MATERIAL->RegisterNormalMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::NORMAL]));
							if (commandX.TextureFlag.HasMetalRoughness)
								MASTER_MATERIAL->RegisterMetalRoughnessMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::METAL_ROUGHNESS]));
							else
							{
								if (commandX.TextureFlag.HasRoughness)
									MASTER_MATERIAL->RegisterRoughnessMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::ROUGHNESS]));
								if (commandX.TextureFlag.HasMetal)
									MASTER_MATERIAL->RegisterMetalMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::METAL]));
							}
							if (commandX.TextureFlag.HasAO)
								MASTER_MATERIAL->RegisterAOMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::AO]));
							if (commandX.TextureFlag.HasEmission)
								MASTER_MATERIAL->RegisterEmissionMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::EMISSIVE]));
							if (commandX.TextureFlag.HasAlpha)
								MASTER_MATERIAL->RegisterAlphaMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::OPACITY]));

							// Update the material and assign it to the mesh
							MASTER_MATERIAL->Update();
							AssignMaterial(TARGET_MESH, MASTER_MATERIAL, commandX.LocalSubMeshID);

						}

						// Push material snapshot command
						CommandDef::MaterialSnapShotCommandDefs _command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
						_command.Material = MASTER_MATERIAL;
						_command.Lock = true;
						_command.Name = MASTER_MATERIAL->GetName();
						_command.Offset = MASTER_MATERIAL->GetOffset();
						Command::PushMaterialSnapshotCommand(_command);

						Loader::StaticGeometryLoader::PROGRESS_INFO = "Creating Material ... " + _command.Name;
					}

					// Remove the processed command from the queue
					Command::s_MaterialCreationCommands.pop();

					// Since the material is ready we can have model preview 
					if (Command::s_MaterialCreationCommands.empty())
					{
						Command::LockCommand<CommandDef::ModelPreviewRenderCommandDef>(Command::s_ModelPreviewRenderCommands);
						Loader::StaticGeometryLoader::PROGRESS_INFO = "Creating Preview....";
					}
				}
				else
				{
					Command::s_ThreadInfoLayerNotifyCallback(false);
					LOG_ERROR(LogLayer::Pipe("The Queryed Mesh Returned NULL! Which isn't suppost to happen! Material creation command ignored!", OELog::CRITICAL));
					Command::s_MaterialCreationCommands.pop();
				}
			}
		}
		Renderer::CheckMatPreviewTexture CommandMasterOperationExecutionHandle::FilterMaterialTexture(MasterMaterial* _material)
		{
			Renderer::CheckMatPreviewTexture data;

			Memory::TextureAccessIndex texture_idx = _material->GetTAI();

			if (texture_idx.Color != -1)
				data.HasColor = true;

			if (texture_idx.Emission != -1)
				data.HasEmission = true;

			if (texture_idx.Normal != -1)
				data.HasNormal = true;

			if (texture_idx.Roughness != -1)
				data.HasRoughness = true;

			if (texture_idx.Metal != -1)
				data.HasMetal = true;

			if (texture_idx.RoughnessMetal != -1)
				data.HasMetalRougness = true;

			if (texture_idx.AmbientOcclusion != -1)
				data.HasAO = true;

			if (texture_idx.AlphaMask != -1)
				data.HasAlpha = true;

			return data;
		}
		bool CommandMasterOperationExecutionHandle::AssignMaterial(ModelPkg* _mesh, MasterMaterial* _material, uint32_t _sub_mesh_id)
		{
			bool _positive_return = false;
			for (size_t i = 0; i < _mesh->MeshList.size(); i++)
			{
				if (_mesh->MeshList[i].LocalID == _sub_mesh_id)
				{
					_mesh->MeshList[i].Material = _material;
					_mesh->MeshList[i].MaterialID = _material->GetOffset();
					_positive_return = true;
					break;
				}
			}

			return _positive_return;
		}
	}
}