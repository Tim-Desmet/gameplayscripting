#pragma once
#include "Texture.h"

class Fish
{
public:
	Fish();
	~Fish();
	void Draw();
	void Update(float elapsedSec);
private:
	Texture* m_pTexture;
};

