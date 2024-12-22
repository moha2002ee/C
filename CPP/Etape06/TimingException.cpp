#include "TimingException.h"
namespace planning
{
    TimingException::TimingException(const string &m, int c) : Exception(m), code(c)
    {
    }
    void TimingException::setCode(int c)
    {
        code = c;
    }
    const int TimingException::getCode() const
    {
        return code;
    }
}