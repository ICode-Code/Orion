#ifndef OE1_AUDIO_SOURCE_COMPONENT_H_
#define OE1_AUDIO_SOURCE_COMPONENT_H_

#include "../AudioBaseComponent.h"

namespace OE1Core
{
	namespace Component
	{
		class AudioSourceComponent : public AudioBaseComponent
		{
			friend class InspectorComponent;
		public:
			AudioSourceComponent();
			AudioSourceComponent(const AudioSourceComponent& _other);
			virtual ~AudioSourceComponent();

			void UpdateArg();
			void UpdateSpatialSoundArg();
			virtual void Update(glm::vec3 _position) override;


			void Play();
			bool IsPlaying();
			void Pause();
			void Continue();
			void Stop();
			void SetLoop(bool _val);
			void SetSource(ALuint _buffer, std::string _name);

		protected:
			ALuint m_Buffers;
		};
	}
}

#endif // !OE1_AUDIO_SOURCE_COMPONENT_H_
