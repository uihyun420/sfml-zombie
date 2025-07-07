#pragma once
#include "GameObject.h"
class Player; // ���� ����	



class Zombie : public GameObject
{
public:
	enum class Type
	{
		Bloater, // ���� ������
		chaser, 
		Crawler,  
	};

	static const int TotalTypes = 3; // �� ���� ���� ��

protected:
	Type type = Type::Bloater; // ���� ����


	sf::Sprite body;
	std::string texId;

	sf::Vector2f direction;// ����

	int maxHp; // �ִ� ü��
	float speed; // �̵� �ӵ�	
	int damage; // ���ݷ�
	float attackintervale; // ���� ����


	int hp; // ���� ü��	

	Player* player = nullptr; // �÷��̾� ������


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

