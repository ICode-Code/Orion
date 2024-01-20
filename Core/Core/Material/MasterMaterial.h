#ifndef OE1_MASTER_MATERIAL_H_
#define OE1_MASTER_MATERIAL_H_

#include "ShaderGenerator/ShaderGenerator.h"
#include "../Core/Texture/Texture.h"
#include "UniformBuffer/UniformBlockManager.h"
#include "../../Common/Shared/UniformBlocks.h"
#include "ShaderManager/ShaderManager.h"
#include "../../Common/Shared/MaterialType.h"
#include "../../Common/Shared/PreDef.h"
#include "../Command/Commnad.h"
#include <glm/glm.hpp>

namespace OE1Core
{
	struct DynamicTextureReadbackBuffer
	{
		/// <summary>
		/// resize this buffer before use!!
		/// </summary>
		std::vector<GLbyte> BUFFER;
		int WIDTH;
		int HEIGHT;
		int CHANNEL = 4; // default
	};

	class MasterMaterial
	{
		friend class MaterialManager;
		friend class AssetParser;
		friend class ExecutionHandler;
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
		
		/// <summary>
		/// If the value you provide is more that the max supported by the drived it gone get rejected
		/// nothing will happen
		/// </summary>
		/// <param name="_val"></param>
		void SetAnisotropicLevel(int _val);
		int GetAnisotropicLevel() const;

		MaterialTextureAvailFlags GetTextureAvailFlags() const;
		MaterialTextureCount GetTextureLayerIndexs() const;
		

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
		MaterialTextureAvailFlags m_TextureAvailFlag;
		MaterialTextureCount m_MaterialTextureCount;

		/// <summary>
		/// Texture Arrays of color map
		/// we store all texture in array separating them color and non-color
		/// becouse of the gamma correction on load
		/// </summary>
		GLuint m_ColorTexture;
		GLuint m_NonColorTexture;
		int m_MaxAnisotropic = 2;
		int m_Offset;
		std::string m_Name;

		/// <summary>
		/// Shader it can be shared or uniqe based on the material structure
		/// </summary>
		Shader* m_Shader = nullptr;

		/// <summary>
		/// This is the material property like how rough a material look
		/// or how metalic you know it is the material prop
		/// </summary>
		Memory::MaterialProperties m_Parameter;

		/// <summary>
		/// We send this data to the shader so that when this material bind the shader know which texture 
		/// is which, it is the index for each texture
		/// </summary>
		Memory::TextureAccessIndex m_TAI;

	protected:
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterAlbedoMap(OE1Core::Texture* _texture);
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterNormalMap(OE1Core::Texture* _texture);
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterMetalMap(OE1Core::Texture* _texture);
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterRoughnessMap(OE1Core::Texture* _texture);
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterMetalRoughnessMap(OE1Core::Texture* _texture);
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterAlphaMap(OE1Core::Texture* _texture);
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterEmissionMap(OE1Core::Texture* _texture);
		/// <summary>
		/// Create or reaplce texture
		/// </summary>
		/// <param name="_texture"></param>
		/// <returns>Weather the process was sucessfull or not</returns>
		bool RegisterAOMap(OE1Core::Texture* _texture);

	private:
		std::vector<GLbyte> FetchTexturePixelData(OE1Core::Texture* _texture);
		void ApplyMapFilter();
		void ReallocateTexture2DArrayTextureBuffer(GLuint _bufferID, size_t _current_size, size_t _new_Size, bool _use_alpha);
		bool UpdateTextureCore(bool& _has_texture, int& _tai, bool& _has_req_map, GLuint* _texture_id, bool is_color, OE1Core::Texture* _texture);

	private: // some flags
		bool m_HasColorMap = false;
		bool m_HasNonColorMap = false;
		

	};
}

#endif // !OE1_MASTER_MATERIAL_H_
