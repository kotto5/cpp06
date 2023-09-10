#include "Data.hpp"

Data::Data(void) : _data("nop nop npo")
{
    return ;
}

Data::Data(const std::string &data) : _data(data)
{
    return ;
}

Data::~Data(void)
{
    return ;
}

Data::Data(const Data &src)
{
    *this = src;
    return ;
}

Data &Data::operator=(const Data &rhs)
{
    if (this != &rhs)
        this->_data = rhs._data;
    return (*this);
}

const std::string &Data::getData(void) const
{
    return (this->_data);
}