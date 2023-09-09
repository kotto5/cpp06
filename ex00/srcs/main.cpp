#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
#include "ScalarConverter.hpp"

void    testCharBoundaryValue()
{
    std::cout << "test char boundary value ==================" << std::endl;
    std::stringstream ss;

    std::cout << "char test: " << (int)std::numeric_limits<char>::max() << std::endl;
    int n = std::numeric_limits<char>::max();
    ss << n;
    ScalarConverter::convert(ss.str());
    ss.str("");
    ss.clear();

    std::cout << "char test: " << (int)std::numeric_limits<char>::max() + 1 << std::endl;
    n = std::numeric_limits<char>::max() + 1;
    ss << n;
    ScalarConverter::convert(ss.str());
    ss.str("");
    ss.clear();

    std::cout << "char test: " << (int)std::numeric_limits<char>::min() << std::endl;
    n = std::numeric_limits<char>::min();
    ss << n;
    ScalarConverter::convert(ss.str());
    ss.str("");
    ss.clear();

    std::cout << "char test: " << (int)std::numeric_limits<char>::min() - 1 << std::endl;
    n = (int)std::numeric_limits<char>::min() - 1;
    ss << n;
    ScalarConverter::convert(ss.str());
    ss.str("");
    ss.clear();
}

void    testCharPrintableBoundaryValue()
{
    std::cout << "test char printable boundary value ==================" << std::endl;
    std::stringstream ss;

    char arg[2];

    arg[1] = '\0';

    std::cout << "char test: " << 32 << std::endl;
    arg[0] = 32;
    ScalarConverter::convert(arg);

    std::cout << "char test: " << 31 << std::endl;
    arg[0] = 31;
    ScalarConverter::convert(arg);

    std::cout << "char test: " << 126 << std::endl;
    arg[0] = 126;
    ScalarConverter::convert(arg);

    std::cout << "char test: " << 127 << std::endl;
    arg[0] = 127;
    ScalarConverter::convert(arg);
}

void    exeTestInt(long n)
{
    std::cout << "int boundary test: " << n << std::endl;
    std::stringstream ss;
    ss << n;
    ScalarConverter::convert(ss.str());
}

void    testIntBoundaryValue()
{
    std::cout << "test int boundary value ==================" << std::endl;

    exeTestInt(std::numeric_limits<int>::max());
    exeTestInt(std::numeric_limits<int>::max() + 1L);
    exeTestInt(std::numeric_limits<int>::min());
    exeTestInt(std::numeric_limits<int>::min() - 1L);
}

void    exeTestFloat(double d)
{
    std::cout << "float boundary test: " << d << std::endl;
    std::stringstream ss;
    ss << d;
    ss << "f";
    ScalarConverter::convert(ss.str());
}

void    exeTestString(const std::string &str)
{
    std::cout << "test: [" << str << "]" <<  std::endl;
    ScalarConverter::convert(str);
}

void    testFloatBoundaryValue()
{
    std::cout << "test float boundary value ==================" << std::endl;

    exeTestFloat(std::numeric_limits<float>::max());
    exeTestFloat(std::numeric_limits<float>::min());
    exeTestString("nanf");
    exeTestString("+inff");
    exeTestString("-inff");
}

void    exeTestDouble(double d)
{
    std::cout << "double boundary test: " << d << std::endl;
    std::stringstream ss;
    ss << d;
    ScalarConverter::convert(ss.str());
}

void    testDoubleBoundaryValue()
{
    std::cout << "test double boundary value ==================" << std::endl;

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
    for (int i = 1; i < argc; i++)
        ScalarConverter::convert(argv[i]);
    testCharBoundaryValue();
    testCharPrintableBoundaryValue();
    testIntBoundaryValue();
    testFloatBoundaryValue();
    testDoubleBoundaryValue();

    return (0);
}

