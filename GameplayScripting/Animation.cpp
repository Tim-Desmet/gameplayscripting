#include "pch.h"
#include "Animation.h"
#include "utils.h"

Animation::Animation(Texture* texture, int framesX, float frameTime, int row)
	: m_pTexture{ texture }, m_FramesX{ framesX }, m_CurrentFrame{ 0 }, m_AccumulatedTime{ 0.f },
	m_FrameTime{ frameTime }, m_Row{ row }, m_Loop{ true }, m_IsFinished{ false }
{
}

void Animation::Update(float elapsedSec)
{
	if (m_IsFinished) return;

	m_AccumulatedTime += elapsedSec;
	if (m_AccumulatedTime >= m_FrameTime)
	{
		++m_CurrentFrame;
		m_AccumulatedTime -= m_FrameTime;

		if (m_CurrentFrame >= m_FramesX)
		{
			if (m_Loop)
			{
				m_CurrentFrame = 0;
			}
			else
			{
				m_CurrentFrame = m_FramesX - 1;
				m_IsFinished = true;
			}
		}
	}
}

void Animation::Draw(const Vector2f& position, bool flip) const
{
	float frameWidth = m_pTexture->GetWidth() / m_FramesX;
	float frameHeight = m_pTexture->GetHeight();

	Rectf srcRect{ m_CurrentFrame * frameWidth, m_pTexture->GetHeight() - frameHeight * (m_Row + 1), frameWidth, frameHeight };
	Rectf dstRect{ position.x, position.y, frameWidth / 2, frameHeight / 2 };

	glPushMatrix();
	if (flip)
	{
		glTranslatef(dstRect.left + dstRect.width / 2.f, dstRect.bottom + dstRect.height / 2.f, 0.f);
		glScalef(-1.f, 1.f, 1.f);
		glTranslatef(-(dstRect.left + dstRect.width / 2.f), -(dstRect.bottom + dstRect.height / 2.f), 0.f);
	}
	m_pTexture->Draw(dstRect, srcRect);
	glPopMatrix();
}

void Animation::SetFrame(int frame)
{
	m_CurrentFrame = frame;
	m_AccumulatedTime = 0.f;
	m_IsFinished = false;
}

int Animation::GetCurrentFrame() const
{
	return m_CurrentFrame;
}

void Animation::SetLooping(bool loop)
{
	m_Loop = loop;
	m_IsFinished = false;
}

bool Animation::IsFinished() const
{
	return m_IsFinished;
}
