#include<AI_Agent.h>
#include<iostream>
using tcp=boost::asio::ip::tcp;
namespace ip=boost::asio::ip;
namespace asio=boost::asio;

Ai_Agent::Ai_Agent(std::string url,std::string port,std::string key) {
    __history = "你是一个人工助手";
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(url, port);
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    boost::asio::async_write(
        socket, boost::asio::buffer(__history),
        [this, &socket](const boost::system::error_code& ec, std::size_t /*length*/) {
            if (!ec) {
                __read(socket);
            } else {
                std::cerr << "Write failed: " << ec.message() << std::endl;
            }
        });

    io_context.run();
}

void Ai_Agent::__read(boost::asio::ip::tcp::socket& socket) {
    std::string buf;
    socket.async_read_some(
        boost::asio::buffer(buf),
        [this, &socket,&buf](const boost::system::error_code& ec, std::size_t length) {
            if (!ec) {
                std::cout << buf.substr(0, length) << std::endl;
                __chat(socket);
            } else {
                std::cerr << "Read failed: " << ec.message() << std::endl;
            }
        });
}

void Ai_Agent::__chat(boost::asio::ip::tcp::socket& socket) {
    std::string buf;
    std::cin>>buf;
    boost::asio::async_write(
        socket, boost::asio::buffer(buf),
        [this, &socket](const boost::system::error_code& ec, std::size_t /*length*/) {
            if (!ec) {
                __read(socket);
            } else {
                std::cerr << "Write failed: " << ec.message() << std::endl;
            }
        });
}