#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame() 
	: Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");
	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/chaser.png");

	AddGameObject(new TileMap("TileMap"));

	player = (Player*)AddGameObject(new Player("Player"));

	Scene::Init();
}

void SceneGame::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});
	 
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	Scene::Enter();
}

void SceneGame::Exit()
{
	for (Zombie* zombie : zombieList)
	{
		RemoveGameObject(zombie); // 좀비 제거
	}
	zombieList.clear(); // 좀비 리스트 초기화
	Scene::Exit();	// 씬 종료시 호출되는 함수
}

void SceneGame::Update(float dt)
{
	
	Scene::Update(dt);
	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(10); // 좀비 10마리 생성
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game); // 게임 씬으로 변경
	}
}

void SceneGame::SpawnZombies(int count)
{
	for (int i = 0; i < 10; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie()); // 좀비 생성
		zombie->Init(); // 좀비 초기화

		zombie->SetType((Zombie::Type)Utils::RandomRange(0, Zombie::TotalTypes)); // 좀비 타입 설정

		zombie->Reset(); // 좀비 초기화 동적으로 생성해서 씬에 넣을때는 init와 Reset을 호출해야 함	
 		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f); // 좀비 위치 설정
		zombieList.push_back(zombie); // 좀비 리스트에 추가

	}
}
