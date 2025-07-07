#pragma once
#include "GameObject.h"
class Player; // 전방 선언	



class Zombie : public GameObject
{
public:
	enum class Type
	{
		Bloater, // 좀비 종류들
		chaser, 
		Crawler,  
	};

	static const int TotalTypes = 3; // 총 좀비 종류 수

protected:
	Type type = Type::Bloater; // 좀비 종류


	sf::Sprite body;
	std::string texId;

	sf::Vector2f direction;// 방향

	int maxHp; // 최대 체력
	float speed; // 이동 속도	
	int damage; // 공격력
	float attackintervale; // 공격 간격


	int hp; // 현재 체력	

	Player* player = nullptr; // 플레이어 포인터


public:
	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

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





	void SetType(Type type);


};

