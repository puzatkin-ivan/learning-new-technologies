#include "stdafx.h"
#include "sheet.h"
#include "Application.h"

using json = nlohmann::json;

namespace
{

	static const auto PORT = "https://127.0.0.1:3000";

}

Application::Application()
	:m_socketMaster(PORT)
{
	m_socketMaster.Emit("nickname", "Ghost");
	m_socketMaster.SetHandler("new_player", [&](sio::event & e) {
		ProcessInitMessage(e.get_message()->get_string());
	});

	m_socketMaster.SetHandler("update_data", [&](sio::event & e) {
		ProcessUpdateData(e.get_message()->get_string());
	});
}


void Application::ClearVectors()
{
	m_data.Clear();
}

void Application::ProcessInitMessage(const std::string & path)
{
	auto data = json::parse(path);
	for (auto& element : data["blocks"])
	{
		BlockForDraw block;
		block.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		m_data.m_vectorBlocks.push_back(block);
	}

	for (auto& element : data["players"])
	{
		PlayerForDraw player;
		player.position = sf::Vector2f(float(element["x"]), float(element["y"]));

		std::cout << player.position.x << " " << player.position.y << std::endl;
		player.health = element["health"];
		player.direction = element["direction"].get<std::string>();
		//player.nickname = element["nickname"].get<std::string>();
		player.nickname = "";
		player.playerId = element["playerId"].get<std::string>();
		m_data.m_vectorPlayers.push_back(player);
	}

	for (auto& element : data["bullets"])
	{
		BulletForDraw bullet;
		bullet.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		m_data.m_vectorBullets.push_back(bullet);
	}

	m_ipClient = data["id"].get<std::string>();
}

void Application::ProcessUpdateData(const std::string & path)
{
	auto data = json::parse(path);
	for (auto & element : data["bullets"])
	{
		BulletForDraw bullet;
		bullet.position = sf::Vector2f(float(element["x"]), float(element["y"]));
		m_data.m_vectorBullets.push_back(bullet);;
	}

	if (m_data.m_vectorPlayers.empty())
	{

		for (auto & element : data["playersForDraw"])
		{
			PlayerForDraw player;
			player.position = sf::Vector2f(float(element["x"]), float(element["y"]));
			player.health = element["health"];
			std::cout << player.position.x << " " << player.position.y << std::endl;
			player.direction = element["direction"].get<std::string>();
			//player.nickname = element["nickname"].get<std::string>();
			player.nickname = "";
			player.playerId = element["playerId"].get<std::string>();
			m_data.m_vectorPlayers.push_back(player);
		}
	}

	for (auto & element : data["playersForTable"])
	{
		(void)&element;
	}
}

void Application::SendKeyMap(const unsigned & keyCode, const bool & isPressed)
{
	json message;
	message["key"] = keyCode;
	message["isPressed"] = isPressed;
	m_socketMaster.Emit("keyMap", message.dump());
}
