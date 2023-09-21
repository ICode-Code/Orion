#ifndef OE1_MASTER_MATERIAL_H_
#define OE1_MASTER_MATERIAL_H_

#include "UniformBuffer/UniformBlockManager.h"
#include "../../Common/Shared/UniformBlocks.h"
#include "ShaderManager/ShaderManager.h"
#include "../../Common/Shared/MaterialType.h"
#include "../../Common/Shared/PreDef.h"
#include <glm/glm.hpp>

namespace OE1Core
{
	class MasterMaterial
	{
		friend class MaterialManager;
	public:
		MasterMaterial(Shader* _shade = nullptr, std::string _name = "Untitled", int _offset = 0);
		/// <summary>
		/// After copying make sure to update the offset
		/// </summary>
		/// <param name="_other"></param>
		MasterMaterial(const MasterMaterial& _other) = default;
		~MasterMaterial();

		void AssignShader(Shader* _shader);
		Shader* GetShader() const;
		
		/// <summary>
		/// This function won't attach the shader it assume it is already done
		/// </summary>
		void Attach();
		/// <summary>
		/// This function forces you to pass the shader explicitly and will attach the shader
		/// </summary>
		/// <param name="_shader"></param>
		void Attach(Shader* _shader);

		void Update();
		
		int GetOffset() const;
		void SetOffset(int _offset);


		std::string GetName() const;
		void SetName(std::string _name);

		GLuint GetColorTextures() const;
		GLuint GetNonColorTexture() const;

		void SetType(MaterialType _type);
		MaterialType GetType() const;

		Memory::MaterialProperties& GetParameter();
		Memory::TextureAccessIndex& GetTAI();

		bool HasColorMap();
		bool HasNonColorMap();

		void SetColorMapTexture(GLuint _color);
		void SetNonColorMapTexture(GLuint _non_color);

		void SetColorIndex(int _idx);
		void SetNormalIndex(int _idx);
		void SetMetalIndex(int _idx);
		void SetRoughnessIndex(int _idx);
		void SetRoughMetalIndex(int _idx);
		void SetEmissionIndex(int _idx);
		void SetAOIndex(int _idx);
		void SetAlphaMaskIndex(int _idx);

	protected:
		MaterialType m_Type;
		GLuint m_ColorTexture;
		GLuint m_NonColorTexture;
		int m_Offset;
		std::string m_Name;
		Shader* m_Shader = nullptr;
		Memory::MaterialProperties m_Parameter;
		Memory::TextureAccessIndex m_TAI;

	private: // some flags
		bool m_HasColorMap = false;
		bool m_HasNonColorMap = false;
		

	};
}

#endif // !OE1_MASTER_MATERIAL_H_
