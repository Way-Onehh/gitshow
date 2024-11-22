/* author:wr */ 
#include <iostream>
#include "head.h"
/* print str */

auto print=[](const char * str=NULL)
{
    std::cout<<str;
};

int main()
{  
    int b,c;
    print("This is a add executive program.now , type two number please!\n");
    std::cin>>b>>c;
    int a = add(b,c);
    char buff[10];
    sprintf(buff,"%d",a);
    print(buff);
    return 0;
}
