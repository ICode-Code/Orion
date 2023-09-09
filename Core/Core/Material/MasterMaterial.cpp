#include "MasterMaterial.h"


namespace OE1Core
{
	MasterMaterial::MasterMaterial(Shader* _shader, std::string _name, int _offset)
	{

		m_Type = MaterialType::DEFAULT;
		SetName(_name);
		if (_shader)
			AssignShader(_shader);
		m_Offset = _offset;
	}
	MasterMaterial::~MasterMaterial()
	{
		if (glIsTexture(m_ColorTexture))
			glDeleteTextures(1, &m_ColorTexture);

		if (glIsTexture(m_NonColorTexture))
			glDeleteTextures(1, &m_NonColorTexture);

		delete m_Shader;
	}

	void MasterMaterial::AssignShader(Shader* _shader)
	{
		m_Shader = _shader;
		m_Shader->RegisterTextureUnit("t_ColorMapTexture", 0);
		m_Shader->RegisterTextureUnit("t_NonColorMapTexture", 1);
		m_Shader->AttachTextureUnit();

	}
	int MasterMaterial::GetOffset() const { return m_Offset; }
	void MasterMaterial::SetOffset(int _offset)
	{
		m_Offset = _offset;
	}
	std::string MasterMaterial::GetName() const { return m_Name; }
	void MasterMaterial::SetName(std::string _name)
	{
		m_Name.clear();
		m_Name = ORI_MATERIAL_PREFIX;
		m_Name.append(_name);
	}
	GLuint MasterMaterial::GetColorTextures() const { return m_ColorTexture; };
	GLuint MasterMaterial::GetNonColorTexture() const { return m_NonColorTexture; };

	void MasterMaterial::SetType(MaterialType _type)
	{
		m_Type = _type;
	}
	MaterialType MasterMaterial::GetType() { return m_Type; }
	Memory::MaterialProperties& MasterMaterial::GetParameter() { return m_Parameter; }
	Memory::TextureAccessIndex& MasterMaterial::GetTAI() { return m_TAI; }

	void MasterMaterial::SetColorMapTexture(GLuint _color)
	{
		m_ColorTexture = _color;
	}
	void MasterMaterial::SetNonColorMapTexture(GLuint _non_color)
	{
		m_NonColorTexture = _non_color;
	}
	Shader* MasterMaterial::GetShader() const
	{
		return m_Shader;
	}
	void MasterMaterial::SetColorIndex(int _idx) {			m_TAI.Color				= _idx; }
	void MasterMaterial::SetNormalIndex(int _idx) {			m_TAI.Normal			= _idx; }
	void MasterMaterial::SetMetalIndex(int _idx) {			m_TAI.Metal				= _idx; }
	void MasterMaterial::SetRoughnessIndex(int _idx) {		m_TAI.Roughness			= _idx; }
	void MasterMaterial::SetRoughMetalIndex(int _idx) {		m_TAI.RoughnessMetal	= _idx; }
	void MasterMaterial::SetEmissionIndex(int _idx) {		m_TAI.Emission			= _idx; }
	void MasterMaterial::SetAOIndex(int _idx) {				m_TAI.AmbientOcclusion	= _idx; }
	void MasterMaterial::SetAlphaMaskIndex(int _idx) {		m_TAI.AlphaMask			= _idx; }
	void MasterMaterial::Update()
	{
		Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::MATERIAL_REGISTRY)->Update(Memory::s_MaterialPropertiesBufferSize, m_Offset, &m_Parameter);
	}
	void MasterMaterial::Attach()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_ColorTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_NonColorTexture);
	}
	void MasterMaterial::Attach(Shader* _shader)
	{
		_shader->Attach();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_ColorTexture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_NonColorTexture);
	}
}