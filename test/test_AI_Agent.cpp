#include<AI_Agent.h>
#include<iostream>
int main() {
    try
    {
        Ai_Agent a("localhost","8888","123");
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}