#ifndef OE1_AUDIO_SOURCE_COMPONENT_ARRAY_COMPONENT_H_
#define OE1_AUDIO_SOURCE_COMPONENT_ARRAY_COMPONENT_H_

#include "../AudioBaseComponent.h"
#include <unordered_map>

namespace OE1Core
{
	namespace Component
	{
		class AudioSourceArrayComponent : public AudioBaseComponent
		{
			friend class InspectorComponent;
		public:
			AudioSourceArrayComponent();
			~AudioSourceArrayComponent();

			void UpdateArg(std::string _name);
			void UpdateSpatialSoundArg(std::string _name);
			virtual void Update(glm::vec3 _position) override;

			void Play(std::string _name);
			bool IsPlaying(std::string _name);
			void Pause(std::string _name);
			void Continue(std::string _name);
			void Stop(std::string _name);
			void SetLoop(bool _val, std::string _name);
			void RegisterSound(ALuint _buffer, std::string _name);
			void PurgeAudio(std::string _name);

			std::unordered_map<std::string, AudioOrigin>& GetBuffers();

		protected:
			std::unordered_map<std::string, AudioOrigin> m_Buffers;
		};
	}
}

#endif // !OE1_AUDIO_SOURCE_COMPONENT_ARRAY_COMPONENT_H_
