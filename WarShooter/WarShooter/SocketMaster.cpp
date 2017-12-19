#include "stdafx.h"

#include "SocketMaster.h"

SocketMaster::SocketMaster(const std::string & port)
{
	m_client.connect(port);
	m_client.socket()->on_error([&](const sio::message::ptr & msg) {
		std::cerr << "ERROR: " << std::endl << msg->get_string() << std::endl;
	});
}

SocketMaster::~SocketMaster()
{
	m_client.sync_close();
}

void SocketMaster::Connect(const std::string & port)
{
	m_client.connect(port);
}

void SocketMaster::CloseConnect()
{
	m_client.sync_close();
}

void SocketMaster::SetHandler(const std::string & key, std::function<void(sio::event & e)> && handler)
{
	m_client.socket()->on(key, handler);
}

void SocketMaster::Emit(const std::string & key)
{
	m_client.socket()->emit(key);
}

void SocketMaster::Emit(const std::string & key, const std::string & msg)
{
	m_client.socket()->emit(key, msg);
}

std::string SocketMaster::GetSessionId() const
{
	return std::string(m_client.get_sessionid());
}

bool SocketMaster::IsConnected() const
{
	return m_client.opened();
}
