//
//  sio_test_sample.cpp
//
//  Created by Melo Yao on 3/24/15.
//

#include <sio_client.h>

#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#include <windows.h>

#define BIT_MASK_PUSHED_KEY 0x8000
#define SOCKET_IO_SERVER "http://localhost:3000"


#ifdef WIN32
#define HIGHLIGHT(__O__) std::cout<<__O__<<std::endl
#define EM(__O__) std::cout<<__O__<<std::endl

#include <stdio.h>
#include <tchar.h>
#define MAIN_FUNC int _tmain(int argc, _TCHAR* argv[])
#else
#define HIGHLIGHT(__O__) std::cout<<"[1;31m:"<<__O__<<":[0m"<<std::endl
#define EM(__O__) std::cout<<"[1;30;1m:"<<__O__<<":[0m"<<std::endl

#define MAIN_FUNC int main(int argc ,const char* args[])
#endif

using namespace sio;
using namespace std;
std::mutex _lock;

std::condition_variable_any _cond;
bool connect_finish = false;

class connection_listener
{
	sio::client &handler;

public:

	connection_listener(sio::client& h) :
		handler(h)
	{
	}


	void on_connected()
	{
		_lock.lock();
		_cond.notify_all();
		connect_finish = true;
		_lock.unlock();
	}
	void on_close(client::close_reason const& reason)
	{
		std::cout << "sio closed " << std::endl;
		exit(0);
	}

	void on_fail()
	{
		std::cout << "sio failed " << std::endl;
		exit(0);
	}
};

socket::ptr current_socket;

void bind_events(socket::ptr &socket)
{
	current_socket->on("disconnect", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck, message::list &ack_resp)
	{
		_lock.lock();
		exit(0);
		_lock.unlock();
	}));
	/*
	current_socket->on("news", sio::socket::event_listener_aux([&](string const& name, message::ptr const& data, bool isAck, message::list &ack_resp)
	{
		_lock.lock();
		処理を書く
		_lock.unlock();
	}));
	*/
}

MAIN_FUNC {
	sio::client h;
	connection_listener l(h);

	h.set_open_listener(std::bind(&connection_listener::on_connected, &l));
	h.set_close_listener(std::bind(&connection_listener::on_close, &l,std::placeholders::_1));
	h.set_fail_listener(std::bind(&connection_listener::on_fail, &l));
	h.connect(SOCKET_IO_SERVER);
	_lock.lock();
	if (!connect_finish)
	{
		_cond.wait(_lock);
	}
	_lock.unlock();
	current_socket = h.socket();

	bind_events(current_socket);

	// 起動している間は打鍵を監視し続ける
	std::string line("user id");
	while (true) {
		// キーボードの打鍵を検知する
		for (int i = 'A'; i <= 'Z'; i++) {
			// キーが押されると最上位ビットが1になる
			// NOTE:GetAsyncKeyStateにすれば、割り込みで検知可能かもしれない
			if (GetKeyState(i) & BIT_MASK_PUSHED_KEY) {
				current_socket->emit("typedKeyboad", line);
			}
		}
		Sleep(50);
	}

	HIGHLIGHT("Closing...");
	h.sync_close();
	h.clear_con_listeners();

	return 0;
}

