/* author:wr */  
/* create time nov 23 */ 

//这是个线程版hello-world，虽然这个场景不适合多线程。
//用lambda函数来，启动线程，减少全局变量，与函数。

#include <condition_variable>
#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

int main()
{
    //字符队列 锁 条件变量 的初始化
    using THstr=std::string; 
    auto print=[](THstr str)
    {
        std::cout<<str;
    };
    std::deque<THstr> taskmap;
    std::mutex mt;
    std::condition_variable cv; 
    std::unique_lock<std::mutex> ul(mt);
    //打印线程
    std::thread printth
    (
        [&cv,&taskmap,&ul,&print]()
        {
             while(true)
             {
                cv.wait(ul);

                for(auto a: taskmap)
                {
                     print(a);
                }  
                taskmap.clear();
                cv.notify_one();
              } 
        }
    );
    //主循环 接受标准输入流里的 一串字符串，以end结尾；
    while(true)
    {
        
        std::string buf;
        std::cin>>buf;
        if(buf=="end")
        {
            cv.notify_all();
            cv.wait(ul);
        }else{
        taskmap.push_back(buf);
        } 
    }

    return 0;
}
