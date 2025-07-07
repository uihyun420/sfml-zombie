#pragma once
#include "Scene.h"

class Player;
class Zombie;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;

	std::list<Zombie*> zombieList; // 좀비 리스트

public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;


	void SpawnZombies(int count); // 좀비 생성 함수
};

