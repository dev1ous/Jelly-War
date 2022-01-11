#include "Cases.h"

Cases::Cases(sf::Texture& texture, sf::Vector2f pos, sf::IntRect rect, int id, int index)
	:m_texture(&texture), m_rect(rect), m_id(id), m_TextureIndex(index)
{
	m_shape.setTexture(texture);
	m_shape.setTextureRect(rect);
	setCasesPos(pos);
}

void Cases::setCasesPos(const sf::Vector2f& p)
{
	setPosition(p);
}


void Cases::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	states.transform *= getTransform();
	states.texture = m_texture;
	target.draw(m_shape, states);
}
