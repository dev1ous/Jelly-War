#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "SFML/Graphics.hpp"

class WindowManager
{
	sf::RenderWindow w;
	sf::View m_view;
	sf::View m_fixedView;
	sf::View m_tcView;
	std::string m_title;
	sf::Vector2u m_size;
	sf::Image icon;
	unsigned size{ 200 };
	bool m_isFullScreen;

	void create(unsigned, const std::string&, unsigned, unsigned);
	void setup(const sf::VideoMode& size, const std::string&, unsigned, const std::string&, unsigned, unsigned);

public:

	explicit WindowManager(const sf::VideoMode& size, const std::string& title, unsigned antialiasing, const std::string& pathIcon, unsigned widthIcon, unsigned heightIcon);
	~WindowManager() = default;

	bool pollEvent(sf::Event& e) { return w.pollEvent(e); }
	bool isOpen()const { return w.isOpen(); }
	bool hasFocus()const { return w.hasFocus(); }
	bool setActive(bool active = true) { return w.setActive(active); }

	sf::RenderWindow& getRenderWindow() { return w; }

	sf::View& getFixedView() { return m_fixedView; }
	sf::View& getMovingView() { return m_view; }
	sf::View& getTCView() { return m_tcView; }
	const sf::View& getDefaultView()const { return w.getDefaultView(); }

	sf::Vector2i getPosition()const { return w.getPosition(); }
	sf::Vector2u getSize() const { return w.getSize(); }

	const sf::FloatRect& getMovingViewport()const { return m_view.getViewport(); }
	const sf::FloatRect& getFixedViewport()const { return m_fixedView.getViewport(); }

	const sf::Vector2f& getMovingViewSize()const { return m_view.getSize(); }
	const sf::Vector2f& getFixedViewSize()const { return m_fixedView.getSize(); }

	const sf::Vector2f& getMovingViewCenter()const { return m_view.getCenter(); }
	const sf::Vector2f& getFixedViewCenter()const { return m_fixedView.getCenter(); }

	void clear() { w.clear(sf::Color::Black); }
	void display() { w.display(); }
	void toggleFullScreen(unsigned antialiasing, const std::string& pathIcon, unsigned widthIcon, unsigned heightIcon);
	void changeFullScreen(const sf::VideoMode& size, const std::string& title, const sf::Uint32& style);
	void draw(sf::Drawable& l_drawable) { w.draw(l_drawable); }
	void FixedView();
	void MovingView();
	void setDefaultView() { setView(getDefaultView()); }
	void close() { w.close(); }
	void setFramerateLimit(unsigned limit) { w.setFramerateLimit(limit); }
	void setMouseCursorVisible(bool visible) { w.setMouseCursorVisible(visible); }
	void setMouseCursorGrabbed(bool grabbed) { w.setMouseCursorGrabbed(grabbed); }
	void setVerticalSyncEnabled(bool enabled) { w.setVerticalSyncEnabled(enabled); }
	void setPosition(const sf::Vector2i& pos) { w.setPosition(pos); }
	void setSize(const sf::Vector2u& size) { w.setSize(size); }
	void setView(const sf::View& view) { w.setView(view); }
	void setVisible(bool visible) { w.setVisible(visible); }
	void requestFocus() { w.requestFocus(); }
	void TerritoryConquestView();
};
#endif


