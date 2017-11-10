#pragma once
#include "GameContext.h"
#include "SocketMaster.h"
#include "DataOfServer.h"

class Application
{
public:
	Application();
	~Application() = default;

	void Update(GameContext & gameContext, sf::View & view);

private:
	void ProcessInitMessage(const std::string & path);
	void ProcessUpdateData(const std::string & path);
	void ClearVectors();

	DataOfServer m_data;
	SocketMaster m_socketMaster;
	std::string m_ipClient;
};
