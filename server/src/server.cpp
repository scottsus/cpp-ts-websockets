#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(server *s, websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    cout << "Received message: " << msg->get_payload() << endl;
}

void broadcast_fake_data(server *s, set<websocketpp::connection_hdl, owner_less<websocketpp::connection_hdl>> *connections)
{
    srand(time(0)); // Seed for random number generation
    while (true)
    {
        this_thread::sleep_for(chrono::seconds(1));
        double lat = 37.7749 + (rand() % 1000) / 10000.0;   // Generate random latitude
        double lon = -122.4194 + (rand() % 1000) / 10000.0; // Generate random longitude
        string fake_data = "lat: " + to_string(lat) + ", long: " + to_string(lon);
        for (auto it = connections->begin(); it != connections->end(); ++it)
        {
            s->send(*it, fake_data, websocketpp::frame::opcode::text);
        }
    }
}

void on_open(server *s, websocketpp::connection_hdl hdl, set<websocketpp::connection_hdl, owner_less<websocketpp::connection_hdl>> *connections)
{
    connections->insert(hdl);
}

void on_close(server *s, websocketpp::connection_hdl hdl, set<websocketpp::connection_hdl, owner_less<websocketpp::connection_hdl>> *connections)
{
    connections->erase(hdl);
}

int main()
{
    server ws_server;
    set<websocketpp::connection_hdl, owner_less<websocketpp::connection_hdl>> connections;

    ws_server.set_message_handler(bind(&on_message, &ws_server, placeholders::_1, placeholders::_2));
    ws_server.set_open_handler(bind(&on_open, &ws_server, placeholders::_1, &connections));
    ws_server.set_close_handler(bind(&on_close, &ws_server, placeholders::_1, &connections));

    ws_server.init_asio();
    ws_server.listen(9002);
    ws_server.start_accept();

    thread broadcast_thread(broadcast_fake_data, &ws_server, &connections);

    ws_server.run();
    broadcast_thread.join();

    return 0;
}
