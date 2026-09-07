#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>

class VgsServer {
public:
    VgsServer(boost::asio::io_context& io_context, int port) 
        : acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
        std::cout << "Server started on port " << port << "..." << std::endl;
        start_accept();
    }

private:
    void start_accept() {
        // Create a socket for the new connection
        auto socket = std::make_shared<boost::asio::ip::tcp::socket>(acceptor_.get_executor());

        acceptor_.async_accept(*socket, 
            [this, socket](boost::system::error_code ec) {
                if (!ec) {
                    std::cout << "Client connected from: " << socket->remote_endpoint() << std::endl;
                    
                    // Prepare a message to send to the client
                    auto message = std::make_shared<std::string>("Hello from VgsServer!\n");
                    
                    // Send the message asynchronously
                    boost::asio::async_write(*socket, boost::asio::buffer(*message),
                        [socket, message](boost::system::error_code ec, std::size_t /*length*/) {
                            if (!ec) {
                                std::cout << "Welcome message sent successfully." << std::endl;
                            }
                        }
                    );
                }
                start_accept(); // Keep listening for the next client
            }
        );
    }

    boost::asio::ip::tcp::acceptor acceptor_;
};

int main() {
    try {
        boost::asio::io_context io;
        VgsServer server(io, 8080);
        io.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}