#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>
#include <chrono>

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

bool bIsConnectedServer = false;
client::connection_ptr con;


// �����ر����� 
int closeConnect()
{
    int nRet = 0;
    try {
        if (con!= NULL && con->get_state() == websocketpp::session::state::value::open)
        {
            websocketpp::close::status::value cvValue = 0;
            std::string strReason = "";
            con->close(cvValue, strReason);
        }
    }
    catch (websocketpp::exception const & e)
    {
        nRet = -1;
    }
    return nRet;
}

// ������������
int sendTextData(char *pText)
{
    int nRet = 0;
    try {
        websocketpp::lib::error_code ec;
        ec = con->send(pText);
        if (ec) {
            std::cout << "Echo failed because: " << ec.message() << std::endl;
            nRet = -1;
        }
    }
    catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
        return -2;
    }

    return nRet;
}

int sendBinaryData(unsigned char *pData, int nSize)
{
    int nRet = 0;
    try {
        websocketpp::lib::error_code ec;
        ec = con->send(pData,nSize,websocketpp::frame::opcode::binary);
        if (ec) {
            std::cout << "Echo failed because: " << ec.message() << std::endl;
            nRet = -1;
        }
    }
    catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
        return -2;
    }

    return nRet;
}

// This message handler will be invoked once for each incoming message. It
// prints the message and then sends a copy of the message back to the server.
void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
        << " and message: " << msg->get_payload()
        << std::endl;

    websocketpp::lib::error_code ec;

    c->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}

//�����Ϸ��������ص��˺���
void on_open(client* c, websocketpp::connection_hdl hdl) {
    std::cout << "open handler" << std::endl;
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    //websocketpp::config::core_client::request_type requestClient = con->get_request();
    if (con->get_ec().value() != 0)
    {
        bIsConnectedServer = false;
    }
    else
    {
        bIsConnectedServer = true;
    }
}

//������Զ�̶Ͽ����ӣ��ص��˺���
void on_close(client* c, websocketpp::connection_hdl hdl)
{
    bIsConnectedServer = false;
    closeConnect();
}

//�޷������Ϸ�����ʱ���ص��˺�����socket���ڲ��ѹر��ϲ������ٹر�
void on_termination_handler(client* c, websocketpp::connection_hdl hdl)
{
    bIsConnectedServer = false;
    closeConnect();
}

int main(int argc, char* argv[]) {
    // Create a client endpoint
    client c;

    std::string uri = "ws://localhost:9002";

    if (argc == 2) {
        uri = argv[1];
    }

    try {
        // Set logging to be pretty verbose (everything except message payloads)
        c.set_access_channels(websocketpp::log::alevel::all);
        c.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize ASIO
        c.init_asio();
        c.set_reuse_addr(true);

        // Register our message handler
        c.set_message_handler(bind(&on_message, &c, ::_1, ::_2));
        c.set_open_handler(bind(&on_open, &c, ::_1));
        c.set_close_handler(bind(on_close, &c, ::_1));

        websocketpp::lib::error_code ec;
        con = c.get_connection(uri, ec);
        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return 0;
        }

        // Note that connect here only requests a connection. No network messages are
        // exchanged until the event loop starts running in the next line.
        c.connect(con);

        //�������ӶϿ�֪ͨhandler
        con->set_termination_handler(bind(on_termination_handler, &c, ::_1));

        // Start the ASIO io_service run loop
        // this will cause a single connection to be made to the server. c.run()
        // will exit when this connection is closed.
        //c.run();

        //�߳�ģʽ��ʹ��run_one��ģ���̴߳������£�
        int nWhileTimes = 10;
        while (nWhileTimes-- > 0)
        {
            if (bIsConnectedServer)
            {
                std::cout << "send txt aaaaa" << std::endl;
                //con->send("aaaaa");//�ı�����
                int nRet = sendTextData("aaaaa");
                std::cout << "send txt aaaaa end." << nRet << std::endl;
                //con->send("bbbbb", 5, websocketpp::frame::opcode::binary);//�ֽ���
            }

            c.run_one();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    catch (websocketpp::exception const & e) {
        std::cout << "ws::exception !!" << std::endl;
        std::cout << e.what() << std::endl;
    }
    c.stop();
}
