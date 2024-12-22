#ifndef TIMEEXCEPTION_H
#define TIMEEXCEPTION_H

#include "Exception.h"
#include <string>

namespace planning {

class TimeException : public Exception {
private:
    int code;

public:
    static const int INVALID_HOUR = 1;
    static const int INVALID_MINUTE = 2;
    static const int OVERFLOW = 3;

    // Constructeur avec une référence constante pour éviter les copies
    TimeException(const std::string& message, int c);

    int getCode() const;
    void setCode(int code);
};

} // namespace planning

#endif // TIMEEXCEPTION_H
