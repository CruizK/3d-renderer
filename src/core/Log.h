#pragma once
#include <spdlog/spdlog.h>

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return m_CoreLogger; }

private:
	static std::shared_ptr<spdlog::logger> m_CoreLogger;
};

#define CORE_ERROR(...) Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_INFO(...) Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_TRACE(...) Log::GetCoreLogger()->trace(__VA_ARGS__)

#define CORE_ASSERT(x, msg) \
	if (!(x))               \
	CORE_ERROR(msg)