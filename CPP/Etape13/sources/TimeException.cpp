#include "TimeException.h"
namespace planning
{
    TimeException::TimeException():Exception()
    {
        code = INVALID_HOUR;
    }
    TimeException::TimeException(const string& message, int code):Exception(message)
    {
        this->code = code; 
    }
    TimeException::TimeException(const Exception& e, const TimeException& te): Exception(e)
    {
        this->code = te.code;
    }
    int TimeException::getCode() const
    {
        return code;
    }
}
