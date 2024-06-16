#ifndef OE1_AUDIO_ORIGIN_H_
#define OE1_AUDIO_ORIGIN_H_


#include <glm/glm.hpp>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>

#include <string>

namespace OE1Core
{
	namespace Component
	{
		class AudioOrigin
		{
			friend class InspectorComponent;
			friend class AudioSourceComponent;
			friend class AudioSourceArrayComponent;
		public:
			AudioOrigin();
			~AudioOrigin();

			void UpdateArg();
			void UpdateSpatialSoundArg();
			void UpdatePosition(glm::vec3 _pos);
			void UpdateVelocity(glm::vec3 _vel);
			void Play();
			bool IsPlaying();
			void Pause();
			void Continue();
			void Stop();
			void SetLoop(bool _val);

		protected:
			ALuint				m_Source = 0;
			std::string			m_Name = "##";
			float				m_RolloffFactor = 1.0f;
			float				m_ReferenceDistance = 5.0f;
			float				m_MaxDistance = 15.0f;
			bool				m_Loop = false;
			bool				m_SpatialSound = false;
			float				m_Gain = 1.0f;
			float				m_Pitch = 1.0f;
		};
	}
}

#endif // !OE1_AUDIO_ORIGIN_H_
