#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::m_CoreLogger = nullptr;

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	m_CoreLogger = spdlog::stdout_color_mt("Core");
	m_CoreLogger->set_level(spdlog::level::trace);
}
