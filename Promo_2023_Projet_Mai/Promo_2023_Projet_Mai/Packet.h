#pragma once
#include "SFML/Network/Packet.hpp"
#include "SFML/System/Vector2.hpp"
#include <type_traits>

enum class PacketType
{
	SERVER_FULL = -1,
	NEW_CONNECTION = 1,
	EXISTING_CONNECTION,
	CLIENT_DISCONNECTED,
	YOUR_CONNECTION,

	WAITING_PACKET,

	MAP_PACKET,
	UPDATE_PACKET,
	NODE_PACKET,
	WON_PACKET,
	REMOVE_TRAP,

	BR_UPDATE,
	BR_PROJECTILE,
	TC_UPDATE,
	AT_UPDATE,
	AT_BUMP,
	SwitchMiniGame,
	SpawnBonus,
};

inline sf::Packet& operator <<(sf::Packet& packet, const PacketType type) {
	return packet << static_cast<std::underlying_type_t<PacketType>>(type);
}

inline sf::Packet& operator >>(sf::Packet& packet, PacketType& type) {
	int _type;
	packet >> _type;
	type = static_cast<PacketType>(_type);
	return packet;
}


inline sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos)
{
	return packet << pos.x << pos.y;
}

inline sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos)
{
	return packet >> pos.x >> pos.y;
}

inline sf::Packet& operator <<(sf::Packet& packet, const sf::IntRect& rect)
{
	return packet << rect.left << rect.top << rect.width << rect.height;
}

inline sf::Packet& operator >>(sf::Packet& packet, sf::IntRect& rect)
{
	return packet >> rect.left >> rect.top >> rect.width >> rect.height;
}
inline sf::Packet& operator >>(sf::Packet& packet, sf::Color& color)
{
	return packet >> color.r >> color.g >> color.b >> color.a;
}
inline sf::Packet& operator <<(sf::Packet& packet, sf::Color& color)
{
	return packet << color.r << color.g << color.b << color.a;
}