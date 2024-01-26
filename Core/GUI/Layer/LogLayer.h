#ifndef OE1_LOG_LAYER_H_
#define OE1_LOG_LAYER_H_


#include "LayerBase.h"
#include "LogMsgState.h"

#include <vector>

#include <chrono>

namespace OE1Core
{
	
	class LogLayer : public LayerBase
	{
	public:
		LogLayer();
		~LogLayer();

		static std::string Pipe(std::string _msg, OE1Core::OELog::LOG_MSG_STATE _state);

		virtual void Update() override;
		virtual void Render() override;

	protected:
		inline static std::vector<OE1Core::OELog::LogMsgPkg> m_CriticalError;
		inline static std::vector<OE1Core::OELog::LogMsgPkg> m_Info;
		inline static std::vector<OE1Core::OELog::LogMsgPkg> m_Debug;
		inline static std::vector<OE1Core::OELog::LogMsgPkg> m_Warn;

		inline static OE1Core::OELog::LogMsgPkg m_TopMsg;

	private:
		inline static bool m_ShowLog = false;
		inline static const char* s_LogIcon = ICON_FA_BUG;
		inline static ImVec4 s_LogColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	private:
		static void InitLogData(OE1Core::OELog::LogMsgPkg& _data);
		static bool IsPassedSec(std::chrono::steady_clock::time_point _since, std::chrono::seconds _sec);
	};
}


#endif // !OE1_LOG_LAYEr_H_
