#include <iostream>
#include <sstream>
#include <limits>

bool    isChar(const std::string &str)
{
    if (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]))
        return (true);
    return (false);
}

bool    isInt(const std::string &str)
{
    std::string sign;
    if (str[0] == '-' || str[0] == '+')
        sign = str[0];
    std::stringstream ss1(str);
    int n;
    ss1 >> n;
    std::stringstream ss2;
    ss2 << sign;
    ss2 << n;
    if (ss2.str() != str)
        return (false);
    return (true);
}

std::size_t count(const std::string &str, char c)
{
    std::size_t count = 0;
    std::string::const_iterator it = str.begin();
    for (; it != str.end(); it++)
    {
        if (*it == c)
            count++;
    }
    return (count);
}

bool    isFloatingLiteral(const std::string &str)
{
    std::string::const_iterator begin = str.begin();
    if (*begin == '-' || *begin == '+')
        begin++;
    std::string::const_iterator it = begin;
    if (count(str, '.') != 1 || *begin == '.' || *(str.end() - 1) == '.') // 唯一ある小数点の位置が正しいことを保証する
        return (false);
    for (; it != str.end(); it++)
    {
        if (std::isdigit(*it) == false && *it != '.')
            return (false);
    }
    return (true);
}

bool    isFloat(const std::string &str)
{
    if (str == "nanf" || str == "+inff" || str == "-inff")
        return (true);
    char suffix = *(str.end() - 1);
    if (suffix != 'f' && suffix != 'F')
        return (false);
    std::string strWithoutSuffix = str.substr(0, str.length() - 1);
    return (isFloatingLiteral(strWithoutSuffix));
}

bool    isDouble(const std::string &str)
{
    if (str == "nan" || str == "+inf" || str == "-inf")
        return (true);

    return (isFloatingLiteral(str));
}

void    testIsChar()
{
    std::cout << isChar("a") << std::endl;
    std::cout << isChar("0") << std::endl;
}

void    _testIsInt(std::string str)
{
    std::cout << str << " : " << isInt(str) << std::endl;
}

void    testIsInt()
{
    _testIsInt("0");
    _testIsInt("-0");
    _testIsInt("--0");
    _testIsInt("+0");
    _testIsInt("2147483647"); // INT_MAX
    _testIsInt("2147483648");
}

void    _testIsFloat(std::string str)
{
    std::cout << str << " : " << isFloat(str) << std::endl;
}

void    testIsFloat()
{
    std::cout << "test isFloat ==================" << std::endl;
    _testIsFloat("0.0f");
    _testIsFloat("+0.0f");
    _testIsFloat("++0.0f");
    _testIsFloat("-0.0f");
    _testIsFloat("-+0.0f");
    _testIsFloat("--0.0f");
    _testIsFloat("--1.f");
    _testIsFloat("0.06f");
    _testIsFloat("0.06f");
    _testIsFloat("0..06f");
    _testIsFloat("0.0.6f");
    _testIsFloat("+inff");
}


void    _testIsDouble(std::string str)
{
    std::cout << str << " : " << isDouble(str) << std::endl;
}

void    testIsDouble()
{
    std::cout << "test isDouble ==================" << std::endl;
    _testIsDouble("0");
    // _testIsDouble("-0");
    // _testIsDouble("--0");
    // _testIsDouble("+0");
    // _testIsDouble("2147483647"); // INT_MAX
    // _testIsDouble("2147483648");
    _testIsDouble("0.0");
    _testIsDouble("00.");
    _testIsDouble("0.06");
    _testIsDouble("0.060");
    _testIsDouble("0.06.0");
    _testIsDouble(".060");
    _testIsDouble(".");
    _testIsDouble("inf");
    _testIsDouble("+inf");
}

void    charPrinter(char c)
{
    if (std::isprint(c))
        std::cout << "char: '" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
}

void    intPrinter(int n)
{
    std::cout << "int: " << n << std::endl;
}

void    floatPrinter(float f)
{
    std::cout << "float: " << f << std::endl;
}

void    doublePrinter(double d)
{
    std::cout << "double: " << d << std::endl;
}

int convert(std::string str)
{
    if (isChar(str))
    {
        char c = str[0];
        charPrinter(c);
        intPrinter(static_cast<int>(c));
        floatPrinter(static_cast<float>(c));
        doublePrinter(static_cast<double>(c));
        return (0);
    }
    else if (isInt(str))
    {
        std::stringstream ss(str);
        int n;
        ss >> n;
        if (n < std::numeric_limits<char>::min() || n > std::numeric_limits<char>::max())
            std::cout << "char: impossible" << std::endl;
        else
            charPrinter(static_cast<char>(n));
        intPrinter(n);
        floatPrinter(static_cast<float>(n));
        doublePrinter(static_cast<double>(n));
        return (0);
    }
    else if (isFloat(str))
    {
        std::stringstream ss(str);
        float f;
        ss >> f;
        if (f < std::numeric_limits<char>::min() || f > std::numeric_limits<char>::max())
            std::cout << "char: impossible" << std::endl;
        else
            charPrinter(static_cast<char>(f));
        if (f < std::numeric_limits<int>::min() || f > std::numeric_limits<int>::max())
            std::cout << "int: impossible" << std::endl;
        else
            intPrinter(static_cast<int>(f));
        floatPrinter(f);
        doublePrinter(static_cast<double>(f));
        return (0);
    }
    else if (isDouble(str))
    {
        std::stringstream ss(str);
        double d;
        ss >> d;
        if (d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max())
            std::cout << "char: impossible" << std::endl;
        else
            charPrinter(static_cast<char>(d));
        if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
            std::cout << "int: impossible" << std::endl;
        else
            intPrinter(static_cast<int>(d));
        if (d < std::numeric_limits<float>::min() || d > std::numeric_limits<float>::max())
            std::cout << "float: impossible" << std::endl;
        else
            floatPrinter(static_cast<float>(d));
        doublePrinter(d);
        return (0);
    }
    else
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return (1);
    }
}

void    test()
{
    std::string a = "0.1e-1";
    // std::string a = "0.134";
    std::stringstream ss(a);
    double d;
    ss >> d;
    if (ss.fail())
        std::cout << "fail" << std::endl;
    else
        std::cout << "success" << d << std::endl;
}

int main()
{
    // testIsInt();
    // testIsFloat();
    // testIsDouble();
    // convert("0");
    test();
    return (0);
}