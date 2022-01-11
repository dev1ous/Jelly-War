#include "WindowManager.h"
#include "Functions.h"

void WindowManager::setup(const sf::VideoMode& size, const std::string& title, unsigned antialiasing, const std::string& pathIcon, unsigned widthIcon, unsigned heightIcon)
{
	m_size.x = size.height;
	m_size.y = size.width;
	m_title = title;
	m_isFullScreen = false;
	create(antialiasing, pathIcon, widthIcon, heightIcon);
	w.setMouseCursorVisible(false);
}

void WindowManager::create(unsigned antialiasing, const std::string& pathIcon, unsigned widthIcon, unsigned heightIcon)
{
	sf::Uint32 style = { m_isFullScreen ? static_cast<sf::Uint32>(sf::Style::Fullscreen) : sf::Style::Default };
	w.create({ sf::VideoMode::getDesktopMode() }, m_title, style, sf::ContextSettings{ 0,0,antialiasing,1,1,0,false });
	if (!icon.loadFromFile(pathIcon))
		return;
	w.setIcon(widthIcon, heightIcon, icon.getPixelsPtr());
}

WindowManager::WindowManager(const sf::VideoMode& size, const std::string& title, unsigned antialiasing, const std::string& pathIcon, unsigned widthIcon, unsigned heightIcon)
{
	setup(size, title, antialiasing, pathIcon, widthIcon, heightIcon);
}

void WindowManager::toggleFullScreen(unsigned antialiasing, const std::string& pathIcon, unsigned widthIcon, unsigned heightIcon)
{
	m_isFullScreen = !m_isFullScreen;
	close();
	create(antialiasing, pathIcon, widthIcon, heightIcon);
	w.setMouseCursorVisible(false);
}

void WindowManager::changeFullScreen(const sf::VideoMode& size, const std::string& title, const sf::Uint32& style)
{
	w.create(size, title, style);
	if (!icon.loadFromFile("../Ressources/pour_le_exe.png"))
		return;
	w.setIcon(64, 64, icon.getPixelsPtr());
	w.setMouseCursorVisible(false);
}

void WindowManager::FixedView()
{
	m_fixedView.reset(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	m_fixedView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	m_fixedView.setSize(1920.f, 1080.f);
	m_fixedView.setCenter({ 960.f,540.f });
	m_fixedView = sf::View({ 960.f,540.f }, sf::Vector2f(1920.f, 1080.f));
	w.setView(m_fixedView);
}

void WindowManager::MovingView()
{
	m_view.reset(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	m_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	m_view.setSize(1920.f, 1080.f);
	m_view = sf::View(sf::Vector2f(960.5f, 540.f), m_view.getSize());
	w.setView(m_view);
}

void WindowManager::TerritoryConquestView()
{
	m_tcView.reset(sf::FloatRect(0.f, 0.f, 1920.f, 1080.f));
	m_tcView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	m_tcView.setSize(1920.f, 1080.f);
	m_tcView = sf::View(sf::Vector2f(960.f, 540.f), m_tcView.getSize());
	w.setView(m_tcView);
}

