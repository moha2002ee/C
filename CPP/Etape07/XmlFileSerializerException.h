#ifndef XMLFILESERIALIZEREXCEPTION_H
#define XMLFILESERIALIZEREXCEPTION_H
#include <iostream>
#include <stdio.h>
#include "Exception.h"

using namespace std;
namespace planning
{

  class XmlFileSerializerException:public Exception
  {
  private:
    int code;
  public:
    static const int NOT_ALLOWED = 1;
    static const int FILE_NOT_FOUND = 2;
    static const int END_OF_FILE = 3;

    XmlFileSerializerException(const string& message, int code);
    XmlFileSerializerException(const XmlFileSerializerException& xmlException);
    virtual ~XmlFileSerializerException() = default;
    int getCode() const;
  };
}

#endif