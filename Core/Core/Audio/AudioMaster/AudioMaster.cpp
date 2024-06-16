#include "AudioMaster.h"
#define DR_WAV_IMPLEMENTATION
#include "DrAudio/dr_wav.h"

namespace OE1Core
{
	namespace AudioEngine
	{
		AudioMaster::AudioMaster()
		{
			m_Device = alcOpenDevice(nullptr);
			if (!m_Device)
			{
				LOG_ERROR("Unable to initlize Audio device!");
				return;
			}

			m_Context = alcCreateContext(m_Device, nullptr);

			if (!m_Context || !alcMakeContextCurrent(m_Context))
			{
				LOG_ERROR("Unable to set Audio Context!");

				if (m_Context)
					alcDestroyContext(m_Context);

				alcCloseDevice(m_Device);
				return;
			}
			alDistanceModel(AL_LINEAR_DISTANCE);
			alGenSources(1, &m_DefaultSource);
		}
		AudioMaster::~AudioMaster()
		{

			for (auto iter = m_Buffers.begin(); iter != m_Buffers.end(); iter++)
				alDeleteBuffers(1, &iter->second);

			alcMakeContextCurrent(nullptr);
			alcDestroyContext(m_Context);
			alcCloseDevice(m_Device);
		}


		ALCdevice* AudioMaster::GetDevice() { return m_Device; }
		ALCcontext* AudioMaster::GetContext() { return m_Context; }


		ALuint AudioMaster::LoadAudio(std::string _path, std::string _name)
		{
			if (m_Buffers.find(_name) != m_Buffers.end())
			{
				LOG_ERROR("Audio with the same name already exist!");
				return 0;
			}
			

			// Load WAV
			drwav _source;
			bool _load_state = drwav_init_file(&_source, _path.c_str(), nullptr);

			if (!_load_state)
			{
				LOG_ERROR("Error Loading audio file! {0}", _path);
				return 0;
			}

			std::vector<uint8_t> _audio_core(_source.totalPCMFrameCount * _source.channels * sizeof(int16_t));
			drwav_read_pcm_frames_s16(&_source, _source.totalPCMFrameCount, reinterpret_cast<int16_t*>(_audio_core.data()));
			drwav_uninit(&_source);

			ALenum format;

			if (_source.channels == 1)
				format = AL_FORMAT_MONO16;
			else
				format = AL_FORMAT_STEREO16;


			m_Buffers.insert(std::make_pair(_name, 0));
			alGenBuffers(1, &m_Buffers[_name]);
			alBufferData(m_Buffers[_name], format, _audio_core.data(), static_cast<ALsizei>(_audio_core.size()), _source.sampleRate);

			drwav_uninit(&_source);



			std::string full_address = ORI_PROJECT_HOT_DIRECTORY + "\\" + _name + ".wav";
				
			std::ofstream file_texture(full_address, std::ios::out | std::ios::binary);
			file_texture.close();
			
			Command::CALL_ContentBrowserLayerNotifyCallback();

			return m_Buffers[_name];

		}
		bool AudioMaster::UnloadAudio(std::string _name)
		{


			return false;
		}
		void AudioMaster::SetDistanceModel(ALenum _model)
		{
			alDistanceModel(_model);
		}
		void AudioMaster::SetListenerPosition(glm::vec3 _pos)
		{
			alListener3f(AL_POSITION, _pos.x, _pos.y, _pos.z);
		}
		void AudioMaster::SetListenerVelocity(glm::vec3 _vel)
		{
			alListener3f(AL_VELOCITY, _vel.x, _vel.y, _vel.z);
		}
		ALuint AudioMaster::GetAudioBuffer(std::string _name)
		{
			if (m_Buffers.find(_name) == m_Buffers.end())
			{
				LOG_ERROR("No Audio file exist with a name {0}", _name);
				return 0;
			}

			return m_Buffers[_name];
		}

		void AudioMaster::PlayWithDefaultSource(std::string _name, bool _finish)
		{
			alSourceStop(m_DefaultSource);
			alSourcei(m_DefaultSource, AL_BUFFER, m_Buffers[_name]);
			alSourcePlay(m_DefaultSource);

			if (_finish)
			{
				ALint _source_state = AL_PLAYING;
				while (_source_state == AL_PLAYING)
					alGetSourcei(m_DefaultSource, AL_SOURCE_STATE, &_source_state);
			}
		}
		bool AudioMaster::IsPlaying(std::string _name)
		{
			ALint _source_state;
			alGetSourcei(m_DefaultSource, AL_SOURCE_STATE, &_source_state);
			return _source_state == AL_PLAYING;
		}
		void AudioMaster::Stop()
		{
			alSourceStop(m_DefaultSource);
		}
	}
}