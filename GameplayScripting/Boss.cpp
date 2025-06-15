#include "pch.h"
#include "Boss.h"
#include "Texture.h"
#include "Animation.h"
#include "utils.h"

Boss::Boss(const Vector2f& pos) : m_InitPos{ pos.x }, m_Position{ pos }, m_HitPoints{ 50 }, m_Speed{ 10.f }, m_BossNr{ GetRandBoss() },
m_State{ State::walk }
{
	LoadTextures();
}

Boss::~Boss()
{
	delete m_pWalkTexture;
	m_pWalkTexture = nullptr;
	delete m_pWalkAnimation;
	m_pWalkAnimation = nullptr;
	delete m_pHurtTexture;
	m_pHurtTexture = nullptr;
	delete m_pHurtAnimation;
	m_pHurtAnimation = nullptr;
	delete m_pDamageTexture;
	m_pDamageTexture = nullptr;
}

void Boss::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, 0.f);
	glScalef(3.f, 3.f, 1.f);
	switch (m_State)
	{
	case Boss::State::walk:
		m_pWalkAnimation->Draw(Vector2f{ 0.f, 0.f }, true);
		break;
	case Boss::State::hurt:
		m_pHurtAnimation->Draw(Vector2f{ 0.f, 0.f }, true);
		break;
	case Boss::State::dead:
		break;
	default:
		break;
	}
	glPopMatrix();
	utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 0.75f });
	utils::FillRect(m_HPBar);
	m_pDamageTexture->Draw(Vector2f{ m_HPBar.left + GetWidth() / 2, m_HPBar.bottom + 10.f });
}

void Boss::Update(float elapsedSec)
{
	m_Position.x -= m_Speed * elapsedSec;
	m_HPBar = Rectf{ m_Position.x + GetWidth() / 2, m_Position.y + GetHeight() + 20.f, 5.f * m_HitPoints, 15.f};

	switch (m_State)
	{
	case Boss::State::walk:
		m_pWalkAnimation->Update(elapsedSec);
		break;
	case Boss::State::hurt:
		m_pHurtAnimation->Update(elapsedSec);
		if (m_pHurtAnimation->IsFinished() == true)
		{
			m_State = State::walk;
			m_pHurtAnimation->SetFrame(0);
		}
		break;
	case Boss::State::dead:
		break;
	default:
		break;
	}
}

float Boss::GetXPos() const
{
	return m_Position.x;
}

void Boss::TakeDamage(int damage)
{
	m_State = State::hurt;
	m_HitPoints -= damage;
	delete m_pDamageTexture;
	m_pDamageTexture = new Texture("-" + std::to_string(damage), "Font.ttf", 30, Color4f{1.f, 0.f, 0.f, 1.f});
	if (m_HitPoints <= 0)
	{
		delete m_pDamageTexture;
		Die();
	}
}

void Boss::Die()
{
	m_BossNr = GetRandBoss();
	delete m_pWalkTexture;
	delete m_pWalkAnimation;
	delete m_pHurtTexture;
	delete m_pHurtAnimation;
	LoadTextures();
	m_Position.x = m_InitPos;
}

void Boss::LoadTextures()
{
	switch (m_BossNr)
	{
	case 1:
		m_Frames = 4;
		m_Speed = 15;
		m_HitPoints = 30;
		break;
	case 2:
		m_Frames = 6;
		m_Speed = 25;
		m_HitPoints = 20;
		break;
	case 3:
		m_Frames = 4;
		m_Speed = 30;
		m_HitPoints = 15;
		break;
	case 4:
		m_Frames = 6;
		m_Speed = 10;
		m_HitPoints = 40;
		break;
	case 5:
		m_Frames = 4;
		m_Speed = 50;
		m_HitPoints = 10;
		break;
	default:
		break;
	}
	m_pWalkTexture = new Texture{ "Bosses/" + std::to_string(m_BossNr) + "/Walk.png" };
	m_pWalkAnimation = new Animation{ m_pWalkTexture, m_Frames, 0.2f };
	m_pHurtTexture = new Texture{ "Bosses/" + std::to_string(m_BossNr) + "/Hurt.png" };
	m_pHurtAnimation = new Animation{ m_pHurtTexture, 2, 0.2f };
	m_pHurtAnimation->SetLooping(false);
	m_pDamageTexture = new Texture(" ", "Font.ttf", 30, Color4f{1.f, 0.f, 0.f, 1.f});
}

int Boss::GetRandBoss()
{
	const int bossAmount{ 5 };
	int randNr = rand() % bossAmount + 1;
	return randNr;
}

float Boss::GetWidth() const
{
	return m_pWalkTexture->GetWidth() / m_Frames;
}

float Boss::GetHeight() const
{
	return m_pWalkTexture->GetHeight();
}
