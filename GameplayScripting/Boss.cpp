#include "pch.h"
#include "Boss.h"
#include "Texture.h"

Boss::Boss(const Vector2f& pos) : m_Position{ pos }, m_HitPoints{ 20 }, m_Speed{ 50.f },
m_pTexture{ new Texture{"Bosses/" + std::to_string(GetRandBoss()) + "/Walk.png"} }, m_AnimTime{ 0.f }, m_CurrFrame{ 1 }, 
m_FrameTime{ 0.3f }
{
}

Boss::~Boss()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Boss::Draw() const
{
	float width = m_pTexture->GetWidth() / m_NumFrames;
	float height = m_pTexture->GetHeight();
	Rectf srcRect = Rectf{ m_CurrFrame * width, 0.f, width, height };
	glPushMatrix();
	glTranslatef(m_Position.x + m_pTexture->GetWidth() / 2.f, m_Position.y + m_pTexture->GetHeight() / 2.f, 0.f);
	glScalef(-1.2f, 1.2f, 1.f);
	glTranslatef(-(m_Position.x + m_pTexture->GetWidth() / 2.f), -(m_Position.y + m_pTexture->GetHeight() / 2.f), 0.f);
	m_pTexture->Draw(m_Position, srcRect);
	glPopMatrix();
}

void Boss::Update(float elapsedSec)
{
	m_Position.x -= m_Speed * elapsedSec;
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= m_FrameTime)
	{
		m_AnimTime -= m_FrameTime;
		m_CurrFrame = (m_CurrFrame + 1) % m_NumFrames;
	}
}

int Boss::GetRandBoss()
{
	const int bossAmount{ 5 };
	int randNr = rand() % bossAmount + 1;

	switch (randNr)
	{
	case 1:
		m_NumFrames = 4;
		break;
	case 2:
		m_NumFrames = 6;
		break;
	case 3:
		m_NumFrames = 4;
		break;
	case 4:
		m_NumFrames = 6;
		break;
	case 5:
		m_NumFrames = 4;
		break;
	default:
		break;
	}
	return randNr;
}
