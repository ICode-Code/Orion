#ifndef OE1_AUDIO_MASTER_H_
#define OE1_AUDIO_MASTER_H_

#include <AL/al.h>
#include <AL/alc.h>

#include <glm/glm.hpp>

#include <Log.h>

#include <unordered_map>
#include <string>

#include "PreDef.h"
#include <fstream>

#include "../Core/Command/CoreCommand/Commnad.h"

namespace OE1Core
{
	namespace AudioEngine
	{
		class AudioMaster
		{
		public:
			AudioMaster();
			~AudioMaster();

			ALuint LoadAudio(std::string _path, std::string _name);
			bool UnloadAudio(std::string _name);
			ALuint GetAudioBuffer(std::string _name);
			void SetDistanceModel(ALenum _model);

			void SetListenerPosition(glm::vec3 _pos);
			void SetListenerVelocity(glm::vec3 _vel);

			void PlayWithDefaultSource(std::string _name, bool _finish = true);
			bool IsPlaying(std::string _name);
			void Stop();

			ALCdevice* GetDevice();
			ALCcontext* GetContext();

		private:
			std::unordered_map<std::string, ALuint> m_Buffers;
			ALCdevice* m_Device = nullptr;
			ALCcontext* m_Context = nullptr;
			ALuint m_DefaultSource = 0;
			
		};
	}
}

#endif // !OE1_AUDIO_MASTER_H_
