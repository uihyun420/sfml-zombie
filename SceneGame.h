#pragma once
#include "Scene.h"

class Player;
class Zombie;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;

	std::list<Zombie*> zombieList; // ���� ����Ʈ
	std::list<Zombie*> zombiePool; // �� ��° ���� ����Ʈ ��Ȱ��ȭ�� ���� Ǯ

	sf::Sprite cursor; // Ŀ�� ��������Ʈ

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SpawnZombies(int count); // ���� ���� �Լ�
};

