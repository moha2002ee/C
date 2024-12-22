#include "TimeException.h"

namespace planning
{

    TimeException::TimeException(const std::string &message, int code)
        : Exception(message), code(code)
    {
    }

    int TimeException::getCode() const
    {
        return code;
    }

    void TimeException::setCode(int c)
    {
        code = c;
    }

}
