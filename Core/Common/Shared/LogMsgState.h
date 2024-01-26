#ifndef OE1_CORE_LOG_MSG_STATE_H_
#define OE1_CORE_LOG_MSG_STATE_H_

#include <string>
#include <chrono>

namespace OE1Core
{
	namespace OELog
	{
        enum LOG_MSG_STATE {
            CRITICAL,
            WARNING,
            INFO,
            DEBUG
        };

        struct LogMsgPkg {

            std::string Msg;
            LOG_MSG_STATE State;
            std::chrono::time_point<std::chrono::steady_clock> TimesStamp;
        };
	}
}
#endif // !OE1_CORE_LOG_MSG_STATE_H_
