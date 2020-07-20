#ifndef QWIRKLE_EXCEPTION
#define QWIRKLE_EXCEPTION

#include <exception>

struct QwirkleException : public std::exception
{
    const char *what() const throw()
    {
        return "QWIRKLE!!!";
    }
};

#endif // QWIRKLE_EXCEPTION