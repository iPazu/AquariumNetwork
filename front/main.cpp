#include "include/Application.hpp"

#include <stdexcept>
#include <iostream>

int main()
{
    Application app { 1800, 1600 };

    try{
        app.run();
        
    } catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}