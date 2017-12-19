#pragma once

#include <string>
#include <functional>
#include <sio_client.h>

class SocketMaster
{
public:
	SocketMaster() = delete;
	SocketMaster(const std::string & port);

	~SocketMaster();

	void Connect(const std::string & port);
	void CloseConnect();

	void SetHandler(const std::string & key, std::function<void(sio::event & e)> && handler);

	void Emit(const std::string & key);
	void Emit(const std::string & key, const std::string & msg);

	std::string GetSessionId() const;
	bool IsConnected() const;

private:
	sio::client m_client;
};
