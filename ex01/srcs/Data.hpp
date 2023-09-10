#ifndef DATA_HPP
# define DATA_HPP

#include <string>

class Data
{
private:
    std::string _data;
public:
    Data();
    Data(const std::string &data);
    ~Data();
    Data(const Data &src);
    Data &operator=(const Data &rhs);

    const std::string &getData() const;
};

#endif