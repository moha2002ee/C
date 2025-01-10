#include "Exception.h"
namespace planning
{

    Exception::Exception()
    {
        this->message = "---";
    }
    Exception::Exception(const string& message)
    {
    	this->message = message;
    }
    Exception::Exception(const Exception& e)
    {
        this->message = e.message;
    }

    string Exception::getMessage() const
    {
        return message;
    }
}
