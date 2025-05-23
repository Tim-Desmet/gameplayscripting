#pragma once
#include "Texture.h"

class Animation
{
public:
    Animation(Texture* texture, int framesX, float frameTime, int row = 0);

    void Update(float elapsedSec);
    void Draw(const Vector2f& position, bool flip) const;
    void SetFrame(int frame);
    int GetCurrentFrame() const;

    void SetLooping(bool loop);
    bool IsFinished() const;

private:
    Texture* m_pTexture;
    int m_FramesX;
    int m_CurrentFrame;
    float m_AccumulatedTime;
    float m_FrameTime;
    int m_Row;
    bool m_Loop;
    bool m_IsFinished;
};