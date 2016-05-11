#include <string>

#ifndef TIME_H
#define TIME_H


class Time
{
public:
    Time();
    Time(unsigned int h, unsigned int m);
    ~Time();
    bool operator>(const Time t) const;
    bool operator==(Time t);
    bool operator!=(Time t);
    bool operator<(Time t);
    bool operator>=(Time t);
    bool operator<=(Time t);
    std::string toString();

private:
    unsigned int _m;
    unsigned int _h;
};

#endif // TIME_H
