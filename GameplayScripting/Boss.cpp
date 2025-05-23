#include "pch.h"
#include "Boss.h"
#include "Texture.h"
#include "Animation.h"

Boss::Boss(const Vector2f& pos) : m_InitPos{ pos.x }, m_Position{ pos }, m_HitPoints{ 50 }, m_Speed{ 100.f }, m_BossNr{ GetRandBoss()},
m_IsHurt{ false }
{
	m_pWalkTexture = new Texture{"Bosses/" + std::to_string(m_BossNr) + "/Walk.png"};
	m_pWalkAnimation = new Animation{m_pWalkTexture, 4, 1.f};
	m_pHitTexture = new Texture{ "Bosses/" + std::to_string(m_BossNr) + "/Hurt.png" };
	m_pHitAnimation = new Animation{ m_pHitTexture, 2, 1.f };
}

Boss::~Boss()
{
	delete m_pWalkTexture;
	m_pWalkTexture = nullptr;
	delete m_pWalkAnimation;
	m_pWalkAnimation = nullptr;
	delete m_pHitTexture;
	m_pHitTexture = nullptr;
	delete m_pHitAnimation;
	m_pHitAnimation = nullptr;
}

void Boss::Draw() const
{
	if (m_IsHurt == true)
	{
		m_pHitAnimation->Draw(m_Position, true);
	}
	else {
		glPushMatrix();
		glScalef(2.f, 2.f, 1.f);
		m_pWalkAnimation->Draw(m_Position, true);
		glPopMatrix();
	}
}

void Boss::Update(float elapsedSec)
{
	m_Position.x -= m_Speed * elapsedSec;

	if (m_IsHurt == true)
	{
		m_pHitAnimation->Update(elapsedSec);
		if (m_pHitAnimation->IsFinished() == true)
		{
			m_IsHurt == false;
		}
	}
	else {
		m_pWalkAnimation->Update(elapsedSec);
	}
}

float Boss::GetXPos() const
{
	return m_Position.x;
}

void Boss::TakeDamage(int damage)
{
	m_IsHurt = true;
	m_HitPoints -= damage;
	if (m_HitPoints <= 0)
	{
		Die();
	}
}

void Boss::Die()
{
	m_HitPoints = 50;
	m_BossNr = GetRandBoss();
	delete m_pWalkTexture;
	m_pWalkTexture = new Texture{ "Bosses/" + std::to_string(m_BossNr) + "/Walk.png" };
	delete m_pHitTexture;
	m_pHitTexture = new Texture{ "Bosses/" + std::to_string(m_BossNr) + "/Hurt.png" };
	m_Position.x = m_InitPos;
}

int Boss::GetRandBoss()
{
	const int bossAmount{ 5 };
	int randNr = rand() % bossAmount + 1;
	return randNr;
}
