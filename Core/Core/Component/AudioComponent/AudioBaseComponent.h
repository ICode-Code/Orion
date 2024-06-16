#ifndef OE1_AUDIO_BASE_COMPONENT_H_
#define OE1_AUDIO_BASE_COMPONENT_H_

#include "AudioOrigin/AudioOrigin.h"

namespace OE1Core
{
	namespace Component
	{
		class AudioBaseComponent
		{
			friend class InspectorComponent;
		public:
			AudioBaseComponent();
			virtual ~AudioBaseComponent();

			virtual void Update(glm::vec3 _position) = 0;

		protected:
			glm::vec3					m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3					m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
			AudioOrigin					m_AudioOrigin;
			
		};
	}
}




#endif // !OE1_AUDIO_BASE_COMPONENT_H_
