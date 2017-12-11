#include "stdafx.h"
#include "BulletView.h"

BulletView::BulletView(SAssets & assets, const sf::Vector2f & position)
	:m_assets(assets)
{
	m_body.setPosition(position - 0.5f * sf::Vector2f(m_assets.BULLET_TEXTURE.getSize()));
	SetTexture(m_assets.BULLET_TEXTURE);

	m_isDraw = true;
}

void BulletView::Update(float dt)
{
	(void)&dt;
}

void BulletView::Draw(sf::RenderWindow & window) const
{
	if (m_isDraw)
	{
		window.draw(m_body);
	}
}

void BulletView::SetOpportunityDrawing(bool isDraw)
{
	m_isDraw = isDraw;
}

bool BulletView::GetIsDraw() const
{
	return m_isDraw;
}

void BulletView::SetTexture(sf::Texture & texture)
{
	m_body.setTextureRect(sf::IntRect(0, 0, int(texture.getSize().x), int(texture.getSize().y)));
	m_body.setTexture(texture);
}

void BulletView::SetPosition(const sf::Vector2f & position)
{
	m_body.setPosition(position - 0.5f * sf::Vector2f(m_assets.BULLET_TEXTURE.getSize()));
}
