#ifndef BUTTON_H
#define BUTTON_H

#include "Container.h"
#include <functional>
#include "Overload.h"
#include <array>
#include "SFML/Audio.hpp"

class Button : public Container<Button>
{
public:
	using ShapeS = std::variant < sf::CircleShape, sf::RectangleShape, sf::Sprite, sf::ConvexShape >;
	using CI_button = Container<Button>;

	template<typename B1, typename B2 = sf::Text>
	requires std::is_convertible_v<B1, ShapeS>
		Button(Button* parent, B1&& _shapes, B2&& _text = sf::Text())noexcept :CI_button(parent), m_shapes(std::forward<B1>(_shapes)), text(std::forward<B2>(_text)) {

		m_buffer.loadFromFile("../Ressources/son/Sound_FX/Menu/Selection.wav");
		m_sound.setBuffer(m_buffer);
		m_sound.setVolume(100.f);
	}
	~Button() = default;

	void CreateFunctionCall(std::function<void()>)noexcept;
	void processEvents(const sf::Event&)noexcept;
	void draw(sf::RenderWindow&)noexcept;
	Button& setTexture(const sf::Texture&)noexcept;
	Button& setColorState(sf::Color, sf::Color, sf::Color)noexcept;
	Button& setTextureState(const std::string&, const std::string&, const std::string&)noexcept;
	Button& Resize()noexcept;
	void CenterText()noexcept;
	Button& changeDefaultColor(sf::Color)noexcept;
	Button& setPosition(sf::Vector2f)noexcept;
	Button& setOrigin()noexcept;
	Button& setRotation(float)noexcept;
	Button& setString(const std::string&)noexcept;
	sf::Vector2f Get_Position()noexcept;
	bool MouseInButton(sf::RenderWindow&)noexcept;
	sf::FloatRect GlobalBounds()noexcept;

	void ForceHover();
	void DesactivateHover();

	void ForceActivation();

private:
	void select()noexcept;
	void deselect()noexcept;
	void activate()noexcept;
	void desactivate()noexcept;

	ShapeS m_shapes{};
	sf::Text text{};
	std::function<void()>Click{};
	std::array<sf::Color, 3> col{};
	std::array<sf::Texture, 3> filepath{};
	sf::Vector2f CurrentTexture;
	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;

	bool toggle{ false };
	bool choose{ false };
};
#endif



