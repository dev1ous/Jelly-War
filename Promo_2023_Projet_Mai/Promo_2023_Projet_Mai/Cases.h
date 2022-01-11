#ifndef CASES_H
#define CASES_H

#include "SFML/Graphics.hpp"

class Cases final : public sf::Drawable, public sf::Transformable
{
public:
	Cases(sf::Texture& texture, sf::Vector2f pos, sf::IntRect rect, int id, int index);
	Cases(sf::Texture& texture) :Cases(texture, { 0, 0 }, { 0,0, 0,0 }, 0, 0) {};
	~Cases() = default;
	sf::IntRect& GetRect() { return m_rect; }
	sf::Sprite& GetSprite() { return m_shape; }
	sf::Texture& GetTexture() { return *m_texture; }
	void setTexture(sf::Texture* texture) { m_texture = texture; }
	void setCasesPos(const sf::Vector2f& p);
	int GetId() const { return m_id; };
	int GetTextureIndex() const { return m_TextureIndex; }

	bool operator==(const sf::Texture& other) { return (this->m_texture == &other); }
	bool operator!=(Cases const& c)const { return getPosition() != c.getPosition(); }
	bool operator==(Cases const& c)const { return getPosition() == c.getPosition(); }
	bool operator<(Cases const& c)const { return getPosition().x < c.getPosition().x&& getPosition().y < c.getPosition().y; }

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const final;
	std::string* m_textureName;
	sf::IntRect m_rect;
	sf::Sprite m_shape;
	sf::Texture* m_texture = nullptr;
	int m_TextureIndex{ 0 };
	int m_id;
};
#endif


