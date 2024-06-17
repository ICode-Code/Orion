#ifndef OE1_RTS_INTIALIZER_H_
#define OE1_RTS_INTIALIZER_H_


#include "../Core/Command/CoreCommand/Commnad.h"
#include "PreDef.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace OE1Core
{
	class RTSIntializer
	{
	public:
		RTSIntializer();
		~RTSIntializer();

		static std::string CreateRTSTemplate(std::string _name);
		static void WriteSourceToFile(std::string _path, const std::string& _source);
		static std::string QuerySource(std::string _path);

		static std::string GetSourcePath(std::string _name);
	private:
		inline static std::unordered_map<std::string, std::string> s_Scripts;

	private: // util
		static void WriteBinary(std::ofstream& _file, std::string _data);
	};
}

#endif // !OE1_RTS_INTIALIZER_H_
