#include "AudioOrigin.h"


namespace OE1Core
{
	namespace Component
	{
		AudioOrigin::AudioOrigin()
		{
			alGenSources(1, &m_Source);
		}
		AudioOrigin::~AudioOrigin()
		{
			alDeleteSources(1, &m_Source);
		}
		void AudioOrigin::UpdateArg()
		{
			alSourcef(m_Source, AL_GAIN, m_Gain);
			alSourcef(m_Source, AL_PITCH, m_Pitch);
		}
		void AudioOrigin::UpdateSpatialSoundArg()
		{
			alSourcef(m_Source, AL_ROLLOFF_FACTOR, m_RolloffFactor);
			alSourcef(m_Source, AL_REFERENCE_DISTANCE, m_ReferenceDistance);
			alSourcef(m_Source, AL_MAX_DISTANCE, m_MaxDistance);
		}
		void AudioOrigin::UpdatePosition(glm::vec3 _pos)
		{
			alSource3f(m_Source, AL_POSITION, _pos.x, _pos.y, _pos.z);

		}
		void AudioOrigin::UpdateVelocity(glm::vec3 _vel)
		{
			alSource3f(m_Source, AL_VELOCITY, _vel.x, _vel.y, _vel.z);
		}
		void AudioOrigin::Play()
		{
			Stop();
			alSourcePlay(m_Source);
		}
		bool AudioOrigin::IsPlaying()
		{
			ALint _state;
			alGetSourcei(m_Source, AL_SOURCE_STATE, &_state);
			return _state == AL_PLAYING;
		}
		void AudioOrigin::Pause()
		{
			alSourcePause(m_Source);
		}
		void AudioOrigin::Continue()
		{
			alSourcePlay(m_Source);
		}
		void AudioOrigin::Stop()
		{
			alSourceStop(m_Source);
		}
		void AudioOrigin::SetLoop(bool _val)
		{
			m_Loop = _val;
			alSourcei(m_Source, AL_LOOPING, m_Loop ? AL_TRUE : AL_FALSE);
		}

	}
}