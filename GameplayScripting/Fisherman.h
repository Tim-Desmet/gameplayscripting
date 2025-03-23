#pragma once

class Texture;
class Fisherman
{
public:
	enum class State {
		idle,
		hook,
		fishing,
	};

	Fisherman(const Vector2f& pos);
	~Fisherman();
	Fisherman(const Fisherman& other);
	Fisherman& operator=(const Fisherman& other);

	void Draw() const;
	void Update(float elapsedSec);
	State m_State;

private:
	Vector2f m_Pos;
	Texture* m_pTexture;
	int m_CurrFrame;
	int m_Cols;
	float m_AnimTime;
};

