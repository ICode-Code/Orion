#include "MasterMaterial.h"
#include "LogUI.h"

namespace OE1Core
{
	MasterMaterial::MasterMaterial(Shader* _shader, std::string _name, int _offset)
	{

		glGenTextures(1, &m_ColorTexture);
		glGenTextures(1, &m_NonColorTexture);
		m_Type = MaterialType::DEFAULT;
		SetName(_name);
		if (_shader)
			AssignShader(_shader);
		m_Offset = _offset;
	}
	MasterMaterial::~MasterMaterial()
	{
		glDeleteTextures(1, &m_ColorTexture);
		glDeleteTextures(1, &m_NonColorTexture);

		delete m_Shader;
	}

	void MasterMaterial::AssignShader(Shader* _shader)
	{
		m_Shader = _shader;
		m_Shader->RegisterTextureUnit("t_ColorMapTexture", 0);
		m_Shader->RegisterTextureUnit("t_NoneColorMapTexture", 1);
		m_Shader->AttachTextureUnit();

	}
	uint32_t MasterMaterial::GetOffset() const { return m_Offset; }
	void MasterMaterial::SetOffset(uint32_t _offset)
	{
		m_Offset = _offset;
	}
	std::string MasterMaterial::GetName() const { return m_Name; }
	void MasterMaterial::SetName(std::string _name)
	{
		m_Name.clear();
		//m_Name = ORI_MATERIAL_PREFIX;
		m_Name.append(_name);
	}
	GLuint& MasterMaterial::GetColorTextures() { return m_ColorTexture; };
	GLuint& MasterMaterial::GetNonColorTexture() { return m_NonColorTexture; };

	void MasterMaterial::SetType(MaterialType _type)
	{
		m_Type = _type;
	}
	MaterialTextureAvailFlags MasterMaterial::GetTextureAvailFlags() const { return m_TextureAvailFlag; };
	MaterialTextureCount MasterMaterial::GetTextureLayerIndexs() const { return m_MaterialTextureCount; };
	MaterialType MasterMaterial::GetType() const { return m_Type; }
	Memory::MaterialProperties& MasterMaterial::GetParameter() { return m_Parameter; }
	Memory::TextureAccessIndex& MasterMaterial::GetTAI() { return m_TAI; }

	bool MasterMaterial::HasColorMap()
	{
		return m_HasColorMap;
	}
	bool MasterMaterial::HasNonColorMap()
	{
		return m_HasNonColorMap;
	}
	void MasterMaterial::FlipDirtyFlag()
	{
		m_Dirty = !m_Dirty;
	}
	GLuint& MasterMaterial::GetPreviewRef() { return m_Preview; }
	bool MasterMaterial::IsDirty() const { return m_Dirty; }
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
		Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::MATERIAL_REGISTRY)->Update(Memory::s_MaterialPropertiesBufferSize, m_Offset * Memory::s_MaterialPropertiesBufferSize, &m_Parameter);
		Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::TAI_REGISTRY)->Update(Memory::s_TextureAccessIndexBufferSize, m_Offset * Memory::s_TextureAccessIndexBufferSize, &m_TAI);
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

	void MasterMaterial::SetAnisotropicLevel(int _val)
	{
		if (_val > 0 && _val <= 4)
			m_MaxAnisotropic = _val;
	}
	int MasterMaterial::GetAnisotropicLevel() const { return m_MaxAnisotropic; }

	std::vector<GLbyte> MasterMaterial::FetchTexturePixelData(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return std::vector<GLbyte>();

		std::vector<GLbyte> _texture_pixel_data(_texture->GetWidth() * _texture->GetHeight() * 4);
		glBindTexture(GL_TEXTURE_2D, _texture->GetTexture());
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texture_pixel_data.data());

		return _texture_pixel_data;
	}

	void MasterMaterial::ApplyMapFilter()
	{
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY, m_MaxAnisotropic);
	}
	void MasterMaterial::ReallocateTexture2DArrayTextureBuffer(GLuint _texture_buffer_id, size_t _current_size, size_t _new_Size, bool _use_alpha)
	{
		// Improvising for OPENGL

		std::vector<DynamicTextureReadbackBuffer> _image_buffer;

		glBindTexture(GL_TEXTURE_2D_ARRAY, _texture_buffer_id);
		for (int i = 0; i < _current_size; i++)
		{
			DynamicTextureReadbackBuffer readBackBuf;

			// Query Texture Size
			glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, i, GL_TEXTURE_WIDTH, &readBackBuf.WIDTH);
			glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, i, GL_TEXTURE_HEIGHT, &readBackBuf.HEIGHT);

			// Resize the vector
			readBackBuf.BUFFER.resize(readBackBuf.WIDTH * readBackBuf.HEIGHT * readBackBuf.HEIGHT);

			// Read image
			glGetTexImage(GL_TEXTURE_2D_ARRAY, i, GL_RGBA, GL_UNSIGNED_BYTE, readBackBuf.BUFFER.data());

			// Push back
			_image_buffer.push_back(readBackBuf);
		}


		// if this vector is empty something is not right/ meaning this function shouldn't be called at the first time
		if (_image_buffer.empty())
		{
			LOG_ERROR(LogLayer::Pipe("Texture readback buffer is empty!", OELog::CRITICAL));
		}

		// Set the first image width and hight as the layer size
		int layer_width = _image_buffer[0].WIDTH;
		int layer_height = _image_buffer[0].HEIGHT;

		// Select if it is color ot not
		GLint INTERNAL_FORMAT = _use_alpha ? GL_SRGB_ALPHA : GL_RGBA;


		// Resize the original texture buffer
		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, INTERNAL_FORMAT, layer_width, layer_height, (GLsizei)_new_Size, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		// After allocating read back the prev image in there order
		for(size_t i = 0; i < _image_buffer.size(); i++)
		{
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, (GLint)i, (GLsizei)_image_buffer[i].WIDTH, (GLsizei)_image_buffer[i].HEIGHT, 1, GL_RGBA, GL_UNSIGNED_BYTE, _image_buffer[i].BUFFER.data());
			ApplyMapFilter();
		}
	}
	bool MasterMaterial::UpdateTextureCore(bool& _has_texture, int& _tai, bool& _has_req_map, GLuint* _texture_id, bool is_color, OE1Core::Texture* _texture)
	{
		_texture->RegisterAssociateMaterialOffset(m_Offset);
		// This function purpose is to reduce the code repition and stuff

		bool default_return = false;

		// Get Texture Pixel Data
		auto TexturePixel = FetchTexturePixelData(_texture);

		
		if (_has_req_map)
		{
			if (_has_texture)
			{
				glBindTexture(GL_TEXTURE_2D_ARRAY, *_texture_id);
				// Update texture
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, _tai, _texture->GetWidth(), _texture->GetHeight(), 1, GL_RGBA, GL_UNSIGNED_BYTE, TexturePixel.data());

				// Apply Filter
				this->ApplyMapFilter();

				// Done
				default_return = true; // easy pizzy
			}
			else
			{
				// If the code reach here the tricky part
				// we have other non-color texture it could be rouhgness or metal or whatever we have some non color material
				// and we need to apped this normal map

				// let's get the number of non color texture, At least we know that :)
				int AvialTextureCount = is_color ? m_MaterialTextureCount.GetColorTextureCount() : m_MaterialTextureCount.GetNonColorTextureCount();

				// ScaleUp texture buffer
				ReallocateTexture2DArrayTextureBuffer(*_texture_id, AvialTextureCount, AvialTextureCount + 1, is_color);

				// Get Index for normal map 
				// Which is basically (CurrentNumberOfNonColorTextureCount + 1) but we do it in the correct way I think
				int MapIdx = is_color ? m_MaterialTextureCount.GetNextColorIndex() : m_MaterialTextureCount.GetNextNonColorIndex();

				//Register Index for callback
				_tai = MapIdx; 
				_has_texture = true;

				// And Finally Write
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, _tai, _texture->GetWidth(), _texture->GetHeight(), 1, GL_RGBA, GL_UNSIGNED_BYTE, TexturePixel.data());
				this->ApplyMapFilter();

				// we that we are done
				default_return = true;
			}
		}
		else
		{

			glBindTexture(GL_TEXTURE_2D_ARRAY, *_texture_id);


			_has_req_map = true;

			// After getting initial texture buffer
			GLint INTERNAL_FORMAT = is_color ? GL_SRGB_ALPHA : GL_RGBA;
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, INTERNAL_FORMAT, _texture->GetWidth(), _texture->GetHeight(), 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


			int MapIdx = is_color ? m_MaterialTextureCount.GetNextColorIndex() : m_MaterialTextureCount.GetNextNonColorIndex();

			_tai = MapIdx; 
			_has_texture = true;

			// we can write our data
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, _tai, _texture->GetWidth(), _texture->GetHeight(), 1, GL_RGBA, GL_UNSIGNED_BYTE, TexturePixel.data());
			this->ApplyMapFilter();

			default_return = true;
		}

		this->Update();

		m_AvailableTexture = AvailTexture(m_TextureAvailFlag);
		m_Type = m_AvailableTexture.GetMaterialType();

		return default_return;
	}

	bool MasterMaterial::RegisterAlbedoMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasColor;

		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasColor,
			m_TAI.Color,
			m_HasColorMap,
			&m_ColorTexture,
			true,
			_texture

		);

		// if the texture is new update shader
		m_Dirty = _need_Shader_update && _state;


		return _state;
		
	}
	bool MasterMaterial::RegisterEmissionMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasEmission;

		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasEmission,
			m_TAI.Emission,
			m_HasColorMap,
			&m_ColorTexture,
			true,
			_texture
		);

		m_Dirty = _need_Shader_update && _state;;
		return _state;
	}
	bool MasterMaterial::RegisterNormalMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasNormal;

		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasNormal, 
			m_TAI.Normal, 
			m_HasNonColorMap,
			&m_NonColorTexture,
			false,
			_texture

		);

		m_Dirty = _need_Shader_update && _state;;
		return _state;
	}

	bool MasterMaterial::RegisterMetalMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasMetal;

		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasMetal,
			m_TAI.Metal,
			m_HasNonColorMap,
			&m_NonColorTexture,
			false,
			_texture

		);

		m_Dirty = _need_Shader_update && _state;;
		return _state;
	}
	bool MasterMaterial::RegisterRoughnessMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasMetalRoughness;

		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasMetalRoughness,
			m_TAI.RoughnessMetal,
			m_HasNonColorMap,
			&m_NonColorTexture,
			false,
			_texture

		);

		m_Dirty = _need_Shader_update && _state;;
		return _state;
	}
	bool MasterMaterial::RegisterMetalRoughnessMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasRoughness;

		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasRoughness,
			m_TAI.Roughness,
			m_HasNonColorMap,
			&m_NonColorTexture,
			false,
			_texture

		);
		m_Dirty = _need_Shader_update && _state;;
		return _state;
	}
	bool MasterMaterial::RegisterAlphaMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasAlpha;
		
		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasAlpha,
			m_TAI.AlphaMask,
			m_HasNonColorMap,
			&m_NonColorTexture,
			false,
			_texture

		);

		m_Dirty = _need_Shader_update && _state;;
		return _state;
	}
	bool MasterMaterial::RegisterAOMap(OE1Core::Texture* _texture)
	{
		if (!_texture)
			return false;

		bool _need_Shader_update = !m_TextureAvailFlag.HasAO;
		

		bool _state = UpdateTextureCore(

			m_TextureAvailFlag.HasAO,
			m_TAI.AmbientOcclusion,
			m_HasNonColorMap,
			&m_NonColorTexture,
			false,
			_texture

		);

		m_Dirty = _need_Shader_update && _state;;
		return _state;
	}
}