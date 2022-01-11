#include "Button.h"
#include "Cache.h"
#include "Options.h"

void Button::CreateFunctionCall(std::function<void()> onClick)noexcept
{
	//m_sound.play();
	Click = std::move(onClick);
}

void Button::processEvents(const sf::Event& e)noexcept
{
	sf::FloatRect rect;

	std::visit([&rect](auto&& args) { rect = args.getGlobalBounds(); }, m_shapes);

	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:
		if (rect.contains(static_cast<float>(e.mouseButton.x), static_cast<float>(e.mouseButton.y)))
		{
			if (!choose)
				changeDefaultColor(std::get<2>(col));
			else
				setTexture(std::get<2>(filepath));

			//m_sound.play();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (rect.contains(static_cast<float>(e.mouseButton.x), static_cast<float>(e.mouseButton.y)))
		{
			if (Click) {
				m_buffer.loadFromFile("../Ressources/son/Sound_FX/Menu/Selection.wav");
				m_sound.setBuffer(m_buffer);
				m_sound.setVolume(Options::volumeBruitages);
				m_sound.play();
				Click();
			}

			desactivate();
		}
		break;
	case sf::Event::MouseMoved:
		if (rect.contains(static_cast<float>(e.mouseMove.x), static_cast<float>(e.mouseMove.y)))
			select();
		else
			deselect();
		break;
	case sf::Event::JoystickButtonPressed:
		switch (e.joystickButton.button) {
		case 0:
			if (rect.contains(sf::Vector2f(sf::Mouse::getPosition()))) 
			{
				if (!choose)
					changeDefaultColor(std::get<2>(col));
				else
					setTexture(std::get<2>(filepath));

				//m_sound.play();
			}
			break;
		default:
			break;
		}
		break;
	case sf::Event::JoystickButtonReleased:
		switch (e.joystickButton.button) 
		{
		case 0:
			if (rect.contains(sf::Vector2f(sf::Mouse::getPosition()))) 
			{
				if (Click) {
					m_buffer.loadFromFile("../Ressources/son/Sound_FX/Menu/Selection.wav");
					m_sound.setBuffer(m_buffer);
					m_sound.setVolume(Options::volumeBruitages);
					m_sound.play();
					Click();
				}

				desactivate();
			}
			break;
		}
		break;
	default:
		break;
	}

	std::for_each(std::begin(getchild()), std::end(getchild()), [e](pair& h) {h.second.processEvents(e); });
}

void Button::select()noexcept
{
	if (!choose)
		changeDefaultColor(std::get<1>(col));
	else
		setTexture(std::get<1>(filepath));
}

void Button::deselect()noexcept
{
	if (!choose)
		changeDefaultColor(std::get<0>(col));
	else
		setTexture(std::get<0>(filepath));
}

void Button::activate()noexcept
{
	if (!choose)
		changeDefaultColor(std::get<2>(col));
	else
		setTexture(std::get<2>(filepath));
	if (Click) {
		m_buffer.loadFromFile("../Ressources/son/Sound_FX/Menu/Selection.wav");
		m_sound.setBuffer(m_buffer);
		m_sound.setVolume(Options::volumeBruitages);
		m_sound.play();
		Click();
	}
}

void Button::desactivate()noexcept
{
	if (!choose)
		changeDefaultColor(std::get<1>(col));
	else
		setTexture(std::get<1>(filepath));
}

void Button::draw(sf::RenderWindow& window)noexcept
{
	std::for_each(std::begin(getchild()), std::end(getchild()), [&window](pair& h) {h.second.draw(window); });

	std::visit([&window](auto&& args) { window.draw(args); }, m_shapes);

	window.draw(text);
}

Button& Button::setTexture(const sf::Texture& path)noexcept
{
	choose = true;
	CurrentTexture = sf::Vector2f(path.getSize());

	match(m_shapes,
		[&path](sf::RectangleShape& r) {r.setTexture(&path); },
		[&path](sf::CircleShape& c) {c.setTexture(&path); },
		[&path](sf::Sprite& s) {s.setTexture(path); },
		[&path](sf::ConvexShape& conv) {conv.setTexture(&path); }
	);
	return *this;
}

Button& Button::setColorState(sf::Color noMouseOn, sf::Color mouseMovedOn, sf::Color mouseClickedOn)noexcept
{
	choose = false;
	std::get<0>(col) = noMouseOn;
	std::get<1>(col) = mouseMovedOn;
	std::get<2>(col) = mouseClickedOn;
	return *this;
}

Button& Button::setTextureState(const std::string& noMouseOn, const std::string& mouseMovedOn, const std::string& mouseClickedOn) noexcept
{
	choose = true;
	std::get<0>(filepath) = Cache::GetRessources<sf::Texture>(noMouseOn);
	std::get<1>(filepath) = Cache::GetRessources<sf::Texture>(mouseMovedOn);
	std::get<2>(filepath) = Cache::GetRessources<sf::Texture>(mouseClickedOn);
	return *this;
}

Button& Button::Resize() noexcept
{
	if (choose)
	{
		match(m_shapes,
			[this](sf::RectangleShape& r) {r.setSize(CurrentTexture); },
			[this](sf::CircleShape& c) {c.setRadius(CurrentTexture.x); },
			[this](sf::Sprite& s) {s.setTextureRect(sf::IntRect(0, 0, CurrentTexture.x, CurrentTexture.y )); },
			[this](sf::ConvexShape& conv) {conv.setTextureRect(sf::IntRect(0, 0, CurrentTexture.x, CurrentTexture.y )); }
		);
	}

	return *this;
}

Button& Button::changeDefaultColor(sf::Color col)noexcept
{
	choose = false;

	match(m_shapes,
		[color = std::move(col)](sf::RectangleShape& r) mutable {r.setFillColor(std::move(color)); },
		[color = std::move(col)](sf::CircleShape& c) mutable {c.setFillColor(std::move(color)); },
		[color = std::move(col)](sf::Sprite& s)mutable {s.setColor(std::move(color)); },
		[color = std::move(col)](sf::ConvexShape& conv)mutable{conv.setFillColor(std::move(color)); }
	);
	return *this;
}

Button& Button::setPosition(sf::Vector2f pos)noexcept
{
	std::visit([pos](auto&& args) { args.setPosition(pos); }, m_shapes);
	return *this;
}

Button& Button::setOrigin() noexcept
{
	std::visit([](auto&& args) { args.setOrigin(args.getGlobalBounds().width / 2.f, args.getGlobalBounds().height / 2.f); }, m_shapes);

	return *this;
}

Button& Button::setRotation(float rota) noexcept
{
	std::visit([rota](auto&& args) { args.setRotation(rota); }, m_shapes);

	return *this;
}

Button& Button::setString(const std::string& str) noexcept
{
	text.setString(str);

	return *this;
}

sf::Vector2f Button::Get_Position()noexcept
{
	sf::Vector2f Pos;

	std::visit([&Pos](auto&& args) { Pos = args.getPosition(); }, m_shapes);

	return Pos;
}

bool Button::MouseInButton(sf::RenderWindow& window)noexcept
{
	bool find{ false };

	std::visit([&window, &find](auto&& args) { find = args.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))); }, m_shapes);

	return find;
}

sf::FloatRect Button::GlobalBounds()noexcept
{
	sf::FloatRect Rect;

	std::visit([&Rect](auto&& args) {Rect = args.getGlobalBounds(); }, m_shapes);

	return Rect;
}

void Button::ForceHover()
{
	select();
}

void Button::DesactivateHover()
{
	deselect();
}

void Button::ForceActivation()
{
	if (Click) {
		m_buffer.loadFromFile("../Ressources/son/Sound_FX/Menu/Selection.wav");
		m_sound.setBuffer(m_buffer);
		m_sound.setVolume(Options::volumeBruitages);
		m_sound.play();
		Click();
	}

	desactivate();
}

void Button::CenterText()noexcept
{
	sf::FloatRect rect = text.getLocalBounds();

	std::visit([this, &rect](auto&& args) { text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
	text.setPosition(args.getPosition()); }, m_shapes);
}
