#include "XmlFileSerializerException.h"
namespace planning
{

    XmlFileSerializerException::XmlFileSerializerException(const string& message, int code):Exception(message)
    {
        this->code = code; 
    }
    XmlFileSerializerException::XmlFileSerializerException(const XmlFileSerializerException& xmlException): Exception(xmlException)
    {
        this->code = xmlException.code;
    }
    int XmlFileSerializerException::getCode() const
    {
        return code;
    }
}
