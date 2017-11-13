#pragma once

#include "GameContext.h"
#include "SocketMaster.h"
#include "DataOfServer.h"

class Application
{
public:
	Application();

	void Update(GameContext & gameContext, sf::View & view);
	void SendKeyMap(const unsigned & keyCode, const bool & isPressed);

	bool IsConnected() const
	{
		return m_socketMaster.IsConnected();
	}

private:
	void ProcessInitMessage(const std::string & path);
	void ProcessUpdateData(const std::string & path);
	void ClearVectors();

	DataOfServer m_data;
	SocketMaster m_socketMaster;
	std::string m_ipClient;
};
