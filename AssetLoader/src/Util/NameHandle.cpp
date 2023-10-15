#include "NameHandle.h"


namespace OE1Core
{
	namespace Loader
	{
		NameHandle::NameHandle()
		{

		}
		NameHandle::~NameHandle()
		{

		}


		std::string NameHandle::FilterFileName(std::string _path)
		{
			if (!PrimaryPathFilter(_path))
				return _path;

			return _path.substr(_path.find_last_of(s_CheckChar) + 1, (_path.find_last_of('.') - _path.find_last_of(s_CheckChar)) - 1);
		}
		std::string NameHandle::FilterFileNameExt(std::string _path)
		{
			if (!PrimaryPathFilter(_path))
				return _path;

			return _path.substr(_path.find_last_of(s_CheckChar) + 1, (_path.size() - _path.find_last_of(s_CheckChar)) - 1);
		}
		std::string NameHandle::FilterPath(std::string _path)
		{
			if (!PrimaryPathFilter(_path))
				return _path;
			return _path.substr(0, _path.find_last_of(s_CheckChar) + 1);
		}

		bool NameHandle::PrimaryPathFilter(std::string _path)
		{

			if (_path.empty())
				return false;

			size_t last_index = _path.size() - 1;

			if (_path[last_index] == '/')
				return false;

			if (_path.find('.') == std::string::npos)
				return false;

			if (_path.find('/') != std::string::npos)
			{
				s_CheckChar = '/';
				return true;
			}
			else if (_path.find('\\') != std::string::npos)
			{
				s_CheckChar = '\\';
				return true;
			}

			return false;
		}
	}
}