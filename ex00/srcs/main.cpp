#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
#include "ScalarConverter.hpp"

#define PINK "\033[38;5;206m"
#define GREEN "\033[38;5;46m"
#define DEF "\033[0m"

void    ExeConvert(const std::string &str)
{
    std::cout << PINK << "input:   [" << str << "]" << DEF << std::endl;
    ScalarConverter::convert(str);
    std::cout << "==========================================" << std::endl;
}

void    testCharBoundaryValue()
{
    std::stringstream ss;

    int n = std::numeric_limits<char>::max();
    ss << n;
    ExeConvert(ss.str());
    ss.str("");
    ss.clear();

    n = std::numeric_limits<char>::max() + 1;
    ss << n;
    ExeConvert(ss.str());
    ss.str("");
    ss.clear();

    n = std::numeric_limits<char>::min();
    ss << n;
    ExeConvert(ss.str());
    ss.str("");
    ss.clear();

    n = (int)std::numeric_limits<char>::min() - 1;
    ss << n;
    ExeConvert(ss.str());
    ss.str("");
    ss.clear();
}

void    testCharPrintableBoundaryValue()
{
    std::stringstream ss;

    char arg[2];

    arg[1] = '\0';

    arg[0] = 32;
    ExeConvert(arg);

    arg[0] = 31;
    ExeConvert(arg);

    arg[0] = 126;
    ExeConvert(arg);

    arg[0] = 127;
    ExeConvert(arg);
}

void    exeTestInt(long n)
{
    std::stringstream ss;
    ss << n;
    ExeConvert(ss.str());
}

void    testIntBoundaryValue()
{

    exeTestInt(std::numeric_limits<int>::max());
    exeTestInt(std::numeric_limits<int>::max() + 1L);
    exeTestInt(std::numeric_limits<int>::min());
    exeTestInt(std::numeric_limits<int>::min() - 1L);
}

void    exeTestFloat(double d)
{
    std::stringstream ss;
    ss << d;
    ss << "f";
    ExeConvert(ss.str());
}

void    exeTestString(const std::string &str)
{
    ExeConvert(str);
}

void    testFloatBoundaryValue()
{

    exeTestFloat(std::numeric_limits<float>::max());
    exeTestFloat(std::numeric_limits<float>::min());
    exeTestString("nanf");
    exeTestString("+inff");
    exeTestString("-inff");
}

void    exeTestDouble(double d)
{
    std::stringstream ss;
    ss << d;
    ExeConvert(ss.str());
}

void    testDoubleBoundaryValue()
{

    exeTestDouble(std::numeric_limits<double>::max());
    exeTestDouble(std::numeric_limits<double>::min());
    exeTestString("2.22507e-309");
    exeTestString("2e+300");
    exeTestString("nan");
    exeTestString("+inf");
    exeTestString("-inf");
}

// https://www.jpcert.or.jp/sc-rules/c-flp34-c.html
// Q.double を float にキャストしていいのか 
// A.(inf が定義されている浮動小数点では overflow することはない)

// https://stackoverflow.com/questions/5605125/why-is-iostreameof-inside-a-loop-condition-i-e-while-stream-eof-cons
// sstream の挙動について

// grep 使うとテストしやすいです

int main(int argc, char **argv)
{
    testCharBoundaryValue();
    testCharPrintableBoundaryValue();
    testIntBoundaryValue();
    testFloatBoundaryValue();
    testDoubleBoundaryValue();
    for (int i = 1; i < argc; i++)
        ExeConvert(argv[i]);

    return (0);
}

