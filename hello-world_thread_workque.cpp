/* author:wr */  
/* create time nov 23 */ 

//这是个线程版hello-world，虽然这个场景不适合多线程。
//用lambda函数来，启动线程，减少全局变量，与函数。

#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <thread>

int main()
{
    //字符队列 锁 条件变量 的初始化
    using THstr=std::string; 
    auto print=[](THstr str)
    {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout<<str<<std::endl;
    };
    std::deque<THstr> taskmap;
    std::condition_variable cv; 
    std::mutex mt;
    
    //打印线程
    auto threadf=[&cv,&taskmap,&mt,&print]()
    {
         while(true)
         {
            decltype (taskmap) this_map;
            {
            std::unique_lock<std::mutex> ul(mt);
            cv.wait(ul);
            while(!taskmap.empty())
            {
                this_map.push_back(taskmap.front());
                taskmap.pop_front();
            }
            }
            for(auto a: this_map)
            {
               print(a);
            }  
            this_map.clear();
          } 
    };
    std::unique_ptr<std::thread>  PrintThs[4];
    for(auto &elem : PrintThs)
    {
        elem.reset(new std::thread(threadf));
    }

    //主循环 接受标准输入流里的 一串字符串，以end结尾；
    while(true)
    {
        
        std::string buf;
        std::cin>>buf;
        if(buf=="end")
        {
            cv.notify_one();
        }else{
        mt.lock();
        taskmap.push_back(buf);
        mt.unlock();
        } 
    }

    return 0;
}
