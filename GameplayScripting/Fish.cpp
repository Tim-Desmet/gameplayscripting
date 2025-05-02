#include "pch.h"
#include "Fish.h"

Fish::Fish() : m_pTexture{ new Texture{"Objects/Catch/1.png"} }
{
}

Fish::~Fish()
{
	delete m_pTexture;
}

void Fish::Draw()
{
	m_pTexture->Draw();
}
