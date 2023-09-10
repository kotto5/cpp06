#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define PINK "\033[38;5;206m"
#define DEF "\033[0m"

Base *generate(void)
{
    std::srand( time(NULL) );
    int i = rand() % 3;
    if (i == 0)
    {
        std::cout << PINK << "Generated A" << DEF << std::endl;
        return new A();
    }
    else if (i == 1)
    {
        std::cout << PINK << "Generated B" << DEF << std::endl;
        return new B();
    }
    else
    {
        std::cout << PINK << "Generated C" << DEF << std::endl;
        return new C();
    }
}

void    Identify(Base *p)
{
    std::cout << "Identify from pointer: ";
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}

void    Identify(Base &p)
{
    std::cout << "Identify from reference: ";
    try
    {
        A &a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "A" << std::endl;
    }
    catch (std::bad_cast &e)
    {
        try
        {
            B &b = dynamic_cast<B&>(p);
            (void)b;
            std::cout << "B" << std::endl;
        }
        catch (std::bad_cast &e)
        {
            try
            {
                C &c = dynamic_cast<C&>(p);
                (void)c;
                std::cout << "C" << std::endl;
            }
            catch (std::bad_cast &e)
            {
                std::cout << "Unknown" << std::endl;
            }
        }
    }
}

void    testIdentify()
{
    std::cout << PINK << "Test Identify input is A:" << DEF << std::endl;
    A a;
    Identify(&a);
    Identify(a);

    std::cout << PINK << "Test Identify input is B:" << DEF << std::endl;
    B b;
    Identify(&b);
    Identify(b);

    std::cout << PINK << "Test Identify input is C:" << DEF << std::endl;
    C c;
    Identify(&c);
    Identify(c);
}

int main()
{
    Base *base = generate();
    Identify(base);
    Identify(*base);

    testIdentify();
    delete base;
    return 0;
}
