#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneGame;

class Bullet : public GameObject
{
protected:
	sf::Sprite body; // 총알의 스프라이트
	std::string texId = "graphics/bullet.png"; // 총알의 텍스처 ID

	sf::Vector2f direction; // 총알의 방향 벡터
	float speed = 0.f;
	int damage = 0;

	HitBox hitBox; // 총알의 히트박스

	SceneGame* sceneGame = nullptr;

public:
	Bullet(const std::string& name = "");
	virtual ~Bullet() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override; // 오리진 설정
	void SetOrigin(Origins preset) override; 

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetLocalBounds() const override // 로컬 좌표계에서의 경계 사각형을 반환
	{
		return body.getLocalBounds(); 
	}

	sf::FloatRect GetGlobalBounds() const override // 전역 좌표계에서의 경계 사각형을 반환
	{
		return body.getGlobalBounds();
	}

	void Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d);
};

