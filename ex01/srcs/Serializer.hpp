#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <iostream>
# include <string>
# include <ctime>
# include "Data.hpp"

class Serializer
{
private:
    Serializer(void);
    Serializer(Serializer const &src);
    ~Serializer(void);
    Serializer &operator=(Serializer const &rhs);
public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif