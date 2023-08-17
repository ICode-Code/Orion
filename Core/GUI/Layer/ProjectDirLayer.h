#ifndef OE1_PROJECT_DIR_H_
#define OE1_PROJECT_DIR_H_


#include "LayerBase.h"


namespace OE1Core
{
	class ProjectDirLayer : public LayerBase
	{
	public:
		ProjectDirLayer();
		~ProjectDirLayer();


		virtual void Update() override;
		virtual void Render() override;
	};
}

#endif // !OE1_PROJECT_DIR_H_
