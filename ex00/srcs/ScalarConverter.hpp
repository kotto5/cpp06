#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <sstream>
# include <limits>
# include <iomanip>

class ScalarConverter
{
private:
enum e_type
{
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
};

    ScalarConverter();
    ~ScalarConverter();
    ScalarConverter(const ScalarConverter &src);
    ScalarConverter &operator=(const ScalarConverter &rhs);
    static bool    isChar(const std::string &str);
    static bool    isInt(const std::string &str);
    static bool    isDouble(const std::string &str);
    static bool    isFloat(const std::string &str);
    static bool    isInfOrNan(const std::string &str);
    static void    charPrinter(char c);
    static void    intPrinter(int n);
    static void    floatPrinter(float f);
    static void    doublePrinter(double d);
    static void    errorPrinter(e_type type);
    static void    nanPrinter(float f);
    static void    nanPrinter(double d);

public:
    static void convert(const std::string &str);
};

#endif