#include "LogLayer.h"


namespace OE1Core
{
	LogLayer::LogLayer()
	{

	}
	LogLayer::~LogLayer() 
	{

	}
	void LogLayer::InitLogData(OE1Core::OELog::LogMsgPkg& _data)
	{
		switch (_data.State)
		{
		case OE1Core::OELog::CRITICAL:
			s_LogIcon = ICON_FA_TRIANGLE_EXCLAMATION;
			s_LogColor = ImVec4(1.0f, 0.121568627f, 0.352941176f, 1.0f);
			break;
		case OE1Core::OELog::WARNING:
			s_LogIcon = ICON_FA_CIRCLE_EXCLAMATION;
			s_LogColor = ImVec4(1.0f, 0.839215686f, 0.082352941f, 1.0f);
			break;
		case OE1Core::OELog::INFO:
			s_LogIcon = ICON_FA_HAND_POINTER;
			break;
		case OE1Core::OELog::DEBUG:
			s_LogIcon = ICON_FA_BUG;
			s_LogColor = ImVec4(0.039215686f, 0.749019608f, 0.325490196f, 1.0f);
			break;
		default:
			break;
		}
	}
	bool LogLayer::IsPassedSec(std::chrono::steady_clock::time_point _since, std::chrono::seconds _sec)
	{
		return (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _since) > _sec);
	}
	std::string LogLayer::Pipe(std::string _msg, OE1Core::OELog::LOG_MSG_STATE _state)
	{
		switch (_state)
		{
		case OE1Core::OELog::CRITICAL:
			m_TopMsg.Msg = _msg;
			m_TopMsg.State = OE1Core::OELog::CRITICAL;
			m_TopMsg.TimesStamp = std::chrono::steady_clock::now();
			m_ShowLog = true;

			m_CriticalError.push_back(m_TopMsg);
			break;
		case OE1Core::OELog::WARNING:
			m_TopMsg.Msg = _msg;
			m_TopMsg.State = OE1Core::OELog::WARNING;
			m_TopMsg.TimesStamp = std::chrono::steady_clock::now();
			m_ShowLog = true;

			m_Warn.push_back(m_TopMsg);
			break;
		case OE1Core::OELog::INFO:
			m_TopMsg.Msg = _msg;
			m_TopMsg.State = OE1Core::OELog::INFO;
			m_TopMsg.TimesStamp = std::chrono::steady_clock::now();
			m_ShowLog = true;

			m_Info.push_back(m_TopMsg);
			break;
		case OE1Core::OELog::DEBUG:
			m_TopMsg.Msg = _msg;
			m_TopMsg.State = OE1Core::OELog::DEBUG;
			m_TopMsg.TimesStamp = std::chrono::steady_clock::now();
			m_ShowLog = true;

			m_Debug.push_back(m_TopMsg);
			break;
		default:
			break;
		}

		return _msg;
	}

	void LogLayer::Update()
	{

	}
	void LogLayer::Render()
	{
		ImGui::Begin("Log");
		if (m_ShowLog)
		{
			InitLogData(m_TopMsg);

			ImGui::PushStyleColor(ImGuiCol_Text, s_LogColor);
			ImGui::Text("%s %s", s_LogIcon, m_TopMsg.Msg.c_str());
			ImGui::PopStyleColor();

			if (IsPassedSec(m_TopMsg.TimesStamp, 10s))
				m_ShowLog = false;
		}

		ImGui::End();
	}
}