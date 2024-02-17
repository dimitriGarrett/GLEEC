#pragma once

#include "Config/Export.h"
#include "PP/PP.h"

#include <string_view>

#include <iostream>
#include <format>
#include <string>
#include <cassert>

namespace GLEEC::Internal
{
    enum LOG_TYPE
    {
        LOG_MESSAGE = 0,
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,
    };

    struct ConsoleColor
    {
        static constexpr const char* red = "\x1B[31m";
        static constexpr const char* green = "\x1B[32m";
        static constexpr const char* yellow = "\x1B[33m";
        static constexpr const char* blue = "\x1B[34m";
        static constexpr const char* magenta = "\x1B[35m";
        static constexpr const char* cyan = "\x1B[36m";
        static constexpr const char* white = "\x1B[37m";
    };

    struct log
    {
        virtual ~log() = default;
        virtual inline void write(LOG_TYPE type, std::string_view message) = 0;

        // mainly for the macros which log where the call is from
        virtual inline void write_origin(LOG_TYPE type, std::string_view origin, std::string_view message) = 0;
    };

    GLEEC_API_EXTERN log* defaultLog;

    struct stdlog final : log
    {
        static constexpr bool write_color = true;

        static std::ostream& get(LOG_TYPE type)
        {
            switch (type)
            {
            case LOG_MESSAGE:   return std::clog;
            case LOG_INFO:    return std::clog;
            case LOG_WARNING: return std::cout;
            case LOG_ERROR:   return std::cerr;
            default: return std::cout;
            }
        }

        static constexpr const char* getString(LOG_TYPE type)
        {
            switch (type)
            {
            case LOG_MESSAGE: return "MSG";
            case LOG_INFO:    return "INF";
            case LOG_WARNING: return "WRN";
            case LOG_ERROR:   return "ERR";
            default: return "UKN";
            }

            // why make them 3 letters long?
            // good question!
        }

        static void setColor(LOG_TYPE type)
        {
            switch (type)
            {
            case LOG_MESSAGE:   std::clog << ConsoleColor::white; break;
            case LOG_INFO:    std::clog << ConsoleColor::white; break;
            case LOG_WARNING: std::cout << ConsoleColor::yellow; break;
            case LOG_ERROR:   std::cerr << ConsoleColor::red; break;
            };
        }

        static std::string toString(unsigned int timeValue)
        {
            if (timeValue < 10)
                return "0" + std::to_string(timeValue);
            return std::to_string(timeValue);
        }

        void write(LOG_TYPE type, std::string_view message)
        {
            setColor(type);
            std::ostream& l = get(type);

            // TODO: include time?
            l << std::format("[{}:{}:{}] [{}]: \"{}\"\n", toString(0), toString(0), toString(0), getString(type), message);
            l << "\x1B[0m"; // reset color

#if GLEEC_DEBUG
            if (type == LOG_ERROR)
	    	assert(false);
#endif
        }

        void write_origin(LOG_TYPE type, std::string_view origin, std::string_view message)
        {
            setColor(type);
            std::ostream& l = get(type);

            // TODO: include time?
            l << std::format("[{}:{}:{}] [{}], [{}]: \"{}\"\n", toString(0), toString(0), toString(0), getString(type), origin, message);
            l << "\x1B[0m"; // reset color

#if GLEEC_DEBUG
            if (type == LOG_ERROR)
	    	assert(false);
#endif
        }
    };
}

// just to make it so i can log in release for example
#if GLEEC_DEBUG
#define GLEEC_LOG 1
#else
#define GLEEC_LOG 0
#endif

#if GLEEC_LOG
    #define LOG_HERE(s, msg, ...) ::GLEEC::Internal::defaultLog->write_origin(s, PP_CURRENT_FUNCTION, std::format(msg, ##__VA_ARGS__))
    #define LOG(s, msg, ...) ::GLEEC::Internal::defaultLog->write(s, std::format(msg, ##__VA_ARGS__))
#else
    #define LOG_HERE(s, msg, ...)
    #define LOG(s, msg, ...)
#endif

#define LOGMESSAGE ::GLEEC::Internal::LOG_MESSAGE
#define LOG_MESSAGE_HERE(msg, ...) LOG_HERE(LOGMESSAGE, msg, ##__VA_ARGS__)
#define LOG_MESSAGE(msg, ...) LOG(LOGMESSAGE, msg, ##__VA_ARGS__)

#define LOGINFO ::GLEEC::Internal::LOG_INFO
#define LOG_INFO_HERE(msg, ...) LOG_HERE(LOGINFO, msg, ##__VA_ARGS__)
#define LOG_INFO(msg, ...) LOG(LOGINFO, msg, ##__VA_ARGS__)

#define LOGWARNING ::GLEEC::Internal::LOG_WARNING
#define LOG_WARNING_HERE(msg, ...) LOG_HERE(LOGWARNING, msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) LOG(LOGWARNING, msg, ##__VA_ARGS__)

#define LOGERROR ::GLEEC::Internal::LOG_ERROR
#define LOG_ERROR_HERE(msg, ...) LOG_HERE(LOGERROR, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) LOG(LOGERROR, msg, ##__VA_ARGS__)
