#include "time.hh"
#include <iostream>

Time::Time()
{

}

Time::Time(unsigned int h, unsigned int m) : _h{h}, _m{m}
{

}

Time::~Time()
{

}

bool Time::operator>(const Time t) const
{
    return this->_h > t._h || (this->_h == t._h && this->_m > t._m);
}

bool Time::operator==(Time t)
{
    return this->_m == t._m && this->_h == t._h;
}

bool Time::operator!=(Time t)
{
    return !(*this == t);
}

bool Time::operator<(Time t)
{
    return !(*this > t || *this == t);
}

bool Time::operator>=(Time t)
{
    return !(*this < t);
}

bool Time::operator<=(Time t)
{
    return !(*this > t);
}

std::string Time::toString()
{
    std::string h = std::to_string(_h);
    std::string m = std::to_string(_m);
    if (_h < 10) {
        h = "0" + h;
    }
    if (_m < 10) {
        m = "0" + m;
    }
    return h + ":" + m;
}

