#include "Log.h"

namespace OE1Core
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_FileLogger;
	void Log::Init()
	{

		spdlog::set_pattern("%^[%T] %n: %v%$"); 

		s_CoreLogger = spdlog::stdout_color_mt("[ORI_CORE] ");
		s_FileLogger = spdlog::basic_logger_mt("[ECHO] ", "ORI_log.txt", true);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_FileLogger->set_level(spdlog::level::trace);
	}
}