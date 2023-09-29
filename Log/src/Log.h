#ifndef OE1_LOG_H_
#define OE1_LOG_H_


#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>


namespace OE1Core
{
	class Log
	{
	public:
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetFileLogger() { return s_FileLogger; }
		static void Init();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_FileLogger;
	}; 
}

#define LOG_INFO(...)   \
do {\
		::OE1Core::Log::GetCoreLogger()->info(__VA_ARGS__); \
		::OE1Core::Log::GetFileLogger()->info(__VA_ARGS__); \
   } while(0) 

#define LOG_FATAL(...) \
do { \
		::OE1Core::Log::GetCoreLogger()->fatal(__VA_ARGS__); \
		::OE1Core::Log::GetFileLogger()->fatal(__VA_ARGS__); \
} while (0)

#define LOG_TRACE(...) \
do { \
		::OE1Core::Log::GetCoreLogger()->trace(__VA_ARGS__); \
		::OE1Core::Log::GetFileLogger()->trace(__VA_ARGS__); \
} while (0)

#define LOG_WARRNING(...) \
do { \
		::OE1Core::Log::GetCoreLogger()->warn(__VA_ARGS__); \
		::OE1Core::Log::GetFileLogger()->warn(__VA_ARGS__); \
} while (0)

#define LOG_ERROR(...)  \
do { \
		::OE1Core::Log::GetCoreLogger()->error(__VA_ARGS__); \
		::OE1Core::Log::GetFileLogger()->error(__VA_ARGS__); \
} while (0)


#endif // !OE1_LOG_H_
