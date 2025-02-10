#pragma once
#include<boost/asio.hpp>

class Ai_Agent
{
public:
    Ai_Agent(std::string url ,std::string port , std::string key);
private:
    void __chat(boost::asio::ip::tcp::socket &socket);
    void __read(boost::asio::ip::tcp::socket &socket);
    std::string __url;
    std::string __key;
    std::string __history;
 };