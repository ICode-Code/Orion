#include "AudioSourceComponent.h"


namespace OE1Core
{
	namespace Component
	{
		AudioSourceComponent::AudioSourceComponent()
		{
			alSourcef(m_AudioOrigin.m_Source, AL_GAIN, m_AudioOrigin.m_Gain);
			alSourcef(m_AudioOrigin.m_Source, AL_PITCH, m_AudioOrigin.m_Pitch);
			alSource3f(m_AudioOrigin.m_Source, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);

		}
		AudioSourceComponent::AudioSourceComponent(const AudioSourceComponent& _other)
		{
			ALuint my_source = m_AudioOrigin.m_Source;
			*this = _other;
			m_AudioOrigin.m_Source = my_source;
			SetSource(_other.m_Buffers, _other.m_AudioOrigin.m_Name);
		}
		AudioSourceComponent::~AudioSourceComponent()
		{

		}
		void AudioSourceComponent::UpdateArg()
		{
			m_AudioOrigin.UpdateArg();
		}
		void AudioSourceComponent::UpdateSpatialSoundArg()
		{
			m_AudioOrigin.UpdateSpatialSoundArg();
		}
		void AudioSourceComponent::Update(glm::vec3 _position)
		{
			m_Position = _position;
			m_AudioOrigin.UpdatePosition(m_Position);
		}
		void AudioSourceComponent::Play()
		{
			Stop();
			alSourcePlay(m_AudioOrigin.m_Source);
		}
		bool AudioSourceComponent::IsPlaying()
		{
			ALint _state;
			alGetSourcei(m_AudioOrigin.m_Source, AL_SOURCE_STATE, &_state);
			return _state == AL_PLAYING;
		}
		void AudioSourceComponent::Pause()
		{
			alSourcePause(m_AudioOrigin.m_Source);
		}
		void AudioSourceComponent::Continue()
		{
			alSourcePlay(m_AudioOrigin.m_Source);
		}
		void AudioSourceComponent::Stop()
		{
			alSourceStop(m_AudioOrigin.m_Source);
		}
		void AudioSourceComponent::SetLoop(bool _val)
		{
			Stop();
			m_AudioOrigin.m_Loop = _val;
			alSourcei(m_AudioOrigin.m_Source, AL_LOOPING, m_AudioOrigin.m_Loop ? AL_TRUE : AL_FALSE);
			Play();
		}
		void AudioSourceComponent::SetSource(ALuint _buffer, std::string _name)
		{
			Stop();
			m_Buffers = _buffer;
			m_AudioOrigin.m_Name = _name;
			alSourcei(m_AudioOrigin.m_Source, AL_BUFFER, m_Buffers);
		}
	}
}