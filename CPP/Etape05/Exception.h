#ifndef EXCEPTION_H // Include guard start
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;

namespace planning
{
    class Exception
    {
    private:
        string message;

    public:
        Exception(const string m);
        const string getMessage() const;
        void setMessage(string m);
    };
}

#endif // EXCEPTION_H // Include guard end
