#include "AudioSourceArrayComponent.h"


namespace OE1Core
{
	namespace Component
	{
		AudioSourceArrayComponent::AudioSourceArrayComponent()
		{

		}
		AudioSourceArrayComponent::~AudioSourceArrayComponent()
		{

		}

		void AudioSourceArrayComponent::UpdateArg(std::string _name)
		{
			m_Buffers[_name].UpdateArg();
		}
		void AudioSourceArrayComponent::UpdateSpatialSoundArg(std::string _name)
		{
			m_Buffers[_name].UpdateSpatialSoundArg();
		}
		void AudioSourceArrayComponent::Update(glm::vec3 _position)
		{
			m_Position = _position;
			for (auto iter : m_Buffers)
				iter.second.UpdatePosition(m_Position);
		}

		void AudioSourceArrayComponent::Play(std::string _name)
		{
			m_Buffers[_name].Play();
		}
		bool AudioSourceArrayComponent::IsPlaying(std::string _name)
		{
			return m_Buffers[_name].IsPlaying();
		}
		void AudioSourceArrayComponent::Pause(std::string _name)
		{
			m_Buffers[_name].Pause();
		}
		void AudioSourceArrayComponent::Continue(std::string _name)
		{
			m_Buffers[_name].Continue();
		}
		void AudioSourceArrayComponent::Stop(std::string _name)
		{
			m_Buffers[_name].Stop();
		}
		void AudioSourceArrayComponent::SetLoop(bool _val, std::string _name)
		{
			m_Buffers[_name].SetLoop(_val);
		}
		void AudioSourceArrayComponent::RegisterSound(ALuint _buffer, std::string _name)
		{
			if (m_Buffers.find(_name) != m_Buffers.end())
				return;

			AudioOrigin _origin;
			alGenSources(1, &_origin.m_Source);

			alSourcef(_origin.m_Source, AL_GAIN, _origin.m_Gain);
			alSourcef(_origin.m_Source, AL_PITCH, _origin.m_Pitch);
			alSource3f(_origin.m_Source, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);

			alSourcef(_origin.m_Source, AL_ROLLOFF_FACTOR, _origin.m_RolloffFactor);
			alSourcef(_origin.m_Source, AL_REFERENCE_DISTANCE, _origin.m_ReferenceDistance);
			alSourcef(_origin.m_Source, AL_MAX_DISTANCE, _origin.m_MaxDistance);

			m_Buffers.insert(std::make_pair(_name, _origin));
		}
		void AudioSourceArrayComponent::PurgeAudio(std::string _name)
		{
			if (m_Buffers.find(_name) == m_Buffers.end())
				return;

			if (m_Buffers[_name].IsPlaying())
				m_Buffers[_name].Stop();

			m_Buffers.erase(_name);
		}

		std::unordered_map<std::string, AudioOrigin>& AudioSourceArrayComponent::GetBuffers()
		{
			return m_Buffers;
		}
	}
}