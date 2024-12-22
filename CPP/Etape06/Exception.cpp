#include "Exception.h"
#include <string>
using namespace std;

namespace planning
{
    Exception::Exception(const string m)
    {
        setMessage(m);
    }

    const string Exception::getMessage() const
    {
        return message;
    }

    void Exception::setMessage(string m)
    {
        message = m;
    }
}
