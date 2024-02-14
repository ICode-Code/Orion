#include "ExeHandleBase.h"


namespace OE1Core
{
	namespace CommandHnd
	{
		ExecutionHandleBase::ExecutionHandleBase(Scene* _scene)
		{
			m_Scene = _scene;
		}
		ExecutionHandleBase::~ExecutionHandleBase()
		{

		}

		void ExecutionHandleBase::SetScene(Scene* _scene) { m_Scene = _scene; }
		Scene* ExecutionHandleBase::GetScene() { return m_Scene; }
		void ExecutionHandleBase::WriteBinary(std::ofstream& _file, std::string _data)
		{
			_file.write(_data.c_str(), _data.size());
		}

	}
}