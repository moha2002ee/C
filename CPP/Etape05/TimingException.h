#include "Exception.h"
namespace planning
{
    class TimingException : public Exception
    {
    private:
        int code;

    public:
        static const int INVALID_DAY = 1;
        static const int NO_TIMING = 2;
        TimingException(const string &m, int c);
        void setCode(int c);
        const int getCode() const;
    };

}