#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::~ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &src) {*this = src;}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs) {
    if (this != &rhs) {
    }
    return (*this);
}

void    ScalarConverter::convert(const std::string &str)
{
    if (isChar(str))
    {
        char c = str[0];
        charPrinter(c);
        intPrinter(static_cast<int>(c));
        floatPrinter(static_cast<float>(c));
        doublePrinter(static_cast<double>(c));
    }
    else if (isInt(str))
    {
        std::stringstream ss(str);
        int n;
        ss >> n;
        if (n < std::numeric_limits<char>::min() || n > std::numeric_limits<char>::max())
            errorPrinter(CHAR);
        else
            charPrinter(static_cast<char>(n));
        intPrinter(n);
        floatPrinter(static_cast<float>(n));
        doublePrinter(static_cast<double>(n));
    }
    else if (isFloat(str))
    {
        float f;
        if (str == "nanf")
            return nanPrinter(std::numeric_limits<float>::quiet_NaN());
        else if (str == "-inff")
            f = -std::numeric_limits<float>::infinity();
        else if (str == "+inff")
            f = std::numeric_limits<float>::infinity();
        else
        {
            std::stringstream ss(str);
            ss >> f;
        }
        if (f < std::numeric_limits<char>::min() || f > std::numeric_limits<char>::max())
            errorPrinter(CHAR);
        else
            charPrinter(static_cast<char>(f));
        if (f < std::numeric_limits<int>::min() || f > std::numeric_limits<int>::max())
            errorPrinter(INT);
        else
            intPrinter(static_cast<int>(f));
        floatPrinter(f);
        doublePrinter(static_cast<double>(f));
    }
    else if (isDouble(str))
    {
        double d;
        if (str == "nan")
            return nanPrinter(std::numeric_limits<double>::quiet_NaN());
        else if (str == "-inf")
            d = -std::numeric_limits<double>::infinity();
        else if (str == "+inf")
            d = std::numeric_limits<double>::infinity();
        else
        {
            std::stringstream ss(str);
            ss >> d;
        }
        if (d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max())
            errorPrinter(CHAR);
        else
            charPrinter(static_cast<char>(d));
        if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
            errorPrinter(INT);
        else
            intPrinter(static_cast<int>(d));
        floatPrinter(static_cast<float>(d));
        doublePrinter(d);
    }
    else
    {
        errorPrinter(CHAR);
        errorPrinter(INT);
        errorPrinter(FLOAT);
        errorPrinter(DOUBLE);
    }
}

bool    ScalarConverter::isChar(const std::string &str)
{
    if (str.length() == 1 && !std::isdigit(str[0]))
        return (true);
    return (false);
}

bool    ScalarConverter::isInt(const std::string &str)
{
    std::stringstream ss(str);
    int n;
    ss >> n;
    return  (ss.fail() == false && ss.eof() == true);
}

bool    ScalarConverter::isDouble(const std::string &str)
{
    if (str == "nan" || str == "+inf" || str == "-inf")
        return (true);
    std::stringstream ss(str);
    double d;
    ss >> d;
    return  (ss.fail() == false && ss.eof() == true);
}

bool    ScalarConverter::isFloat(const std::string &str)
{
    if (str == "nanf" || str == "+inff" || str == "-inff")
        return (true);
    if (str.end()[-1] != 'f')
        return (false);
    std::stringstream ss(str.substr(0, str.length() - 1));
    float f;
    ss >> f;
    return  (ss.fail() == false && ss.eof() == true);
}

bool    ScalarConverter::isInfOrNan(const std::string &str)
{
    if (str == "nan" || str == "inf" || 
        str == "+inf" || str == "-inf" || 
        str == "nanf" || str == "inff" || 
        str == "+inff" || str == "-inff")
        return (true);
    return (false);
}

void  ScalarConverter::charPrinter(char c)
{
    if (std::isprint(c))
        std::cout << "char:   '" << c << "'" << std::endl;
    else
        std::cout << "char:   Non displayable" << std::endl;
}

void ScalarConverter::intPrinter(int n)
{
    std::cout << "int:    " << n << std::endl;
}

void   ScalarConverter::floatPrinter(float f)
{
    #ifdef DEBUG
        std::cout << "float:  " << f << "f" << std::endl;
    #endif
    #ifndef DEBUG
        std::cout << std::fixed << std::setprecision(1) << "float:  " << f << "f" << std::endl;
    #endif
    std::cout.unsetf(std::ios_base::floatfield);
}

void    ScalarConverter::doublePrinter(double d)
{
    #ifdef DEBUG
        std::cout << "double:  " << d << std::endl;
    #endif
    #ifndef DEBUG
        std::cout << std::fixed << std::setprecision(1) << "double: " << d << std::endl;
    #endif
    std::cout.unsetf(std::ios_base::floatfield);
}

void    ScalarConverter::nanPrinter(float f)
{
    errorPrinter(CHAR);
    errorPrinter(INT);
    floatPrinter(f);
    doublePrinter(static_cast<double>(f));
}

void    ScalarConverter::nanPrinter(double d)
{
    errorPrinter(CHAR);
    errorPrinter(INT);
    floatPrinter(static_cast<float>(d));
    doublePrinter(d);
}


void    ScalarConverter::errorPrinter(e_type type)
{
    if (type == CHAR)
        std::cout << "char: impossible" << std::endl;
    else if (type == INT)
        std::cout << "int: impossible" << std::endl;
    else if (type == FLOAT)
        std::cout << "float: impossible" << std::endl;
    else if (type == DOUBLE)
        std::cout << "double: impossible" << std::endl;
}