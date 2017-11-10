#pragma once

#include <string>
#include <cstdarg>
#include <iostream>
#include <functional>
#include <sio_client.h>

class SocketMaster
{
public:
	SocketMaster() = delete;
	SocketMaster(const std::string & port)
	{
		m_client.connect(port);

		m_client.socket()->on_error([&](const sio::message::ptr & msg) {
			std::cerr << "ERROR: " << std::endl << msg->get_string() << std::endl;
		});
	}

	void SetHandler(const std::string & key, std::function<void(sio::event & e)> && handler)
	{
		m_client.socket()->on(key, handler);
	}

	void Emit(const std::string & key)
	{
		m_client.socket()->emit(key);
	}

	void Emit(const std::string & key, const std::string & msg)
	{
		m_client.socket()->emit(key, msg);
	}

	~SocketMaster()
	{
		m_client.close();
	}

private:
	sio::client m_client;
};
