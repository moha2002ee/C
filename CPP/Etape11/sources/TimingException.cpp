#include "TimingException.h"
namespace planning
{
    TimingException::TimingException():Exception()
    {
        code = INVALID_DAY;
    }
    TimingException::TimingException(const string& message, int code):Exception(message)
    {
        this->code = code; 
    }
    TimingException::TimingException(const Exception& e, const TimingException& te): Exception(e)
    {
        this->code = te.code;
    }
    int TimingException::getCode() const
    {
        return code;
    }
}