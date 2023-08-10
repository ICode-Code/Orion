#ifndef OE1_LOG_H_
#define OE1_LOG_H_


#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


namespace OE1Core
{
	class Log
	{
	public:
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static void Init();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	}; 
}

#define LOG_INFO(...)         ::OE1Core::Log::GetCoreLogger()->info(__VA_ARGS__);
#define LOG_FATAL(...)        ::OE1Core::Log::GetCoreLogger()->fatal(__VA_ARGS__);
#define LOG_TRACE(...)        ::OE1Core::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define LOG_WARRNING(...)     ::OE1Core::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define LOG_ERROR(...)        ::OE1Core::Log::GetCoreLogger()->error(__VA_ARGS__);

#endif // !OE1_LOG_H_
