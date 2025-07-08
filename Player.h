#pragma once
#include "GameObject.h"
#include "HitBox.h"

class SceneGame;
class Bullet;

class Player : public GameObject
{
protected:
	sf::Sprite body;
	std::string texId = "graphics/player.png";

	sf::Vector2f direction;
	sf::Vector2f look;

	float speed = 500.f;

	SceneGame* sceneGame = nullptr;

	HitBox hitBox;

	std::list<Bullet*> bulletList; // 총알 리스트
	std::list<Bullet*> bulletPool; // 총알 풀 (재사용을 위한)


	float shootInterval = 0.5f; // 총알 발사 간격
	float shootTimer = 0.f; // 총알 발사 타이머

	int hp = 0;
	int maxHp = 100;

	bool isAlive = true;


public:
	bool IsAlive()const { return hp > 0; }
	Player(const std::string& name = "");
	~Player() override = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;



	sf::FloatRect GetLocalBounds() const override 
	{
		return body.getLocalBounds();
	}

	sf::FloatRect GetGlobalBounds() const override
	{
		return body.getGlobalBounds();
	}


	const HitBox& GetHitBox() const
	{
		return hitBox;
	}

	void Shoot();


	void OnDamage(int damage);

};

