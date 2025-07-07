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
		RemoveGameObject(zombie); // ���� ����
	}
	zombieList.clear(); // ���� ����Ʈ �ʱ�ȭ
	Scene::Exit();	// �� ����� ȣ��Ǵ� �Լ�
}

void SceneGame::Update(float dt)
{
	
	Scene::Update(dt);
	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SpawnZombies(10); // ���� 10���� ����
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game); // ���� ������ ����
	}
}

void SceneGame::SpawnZombies(int count)
{
	for (int i = 0; i < 10; ++i)
	{
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie()); // ���� ����
		zombie->Init(); // ���� �ʱ�ȭ

		zombie->SetType((Zombie::Type)Utils::RandomRange(0, Zombie::TotalTypes)); // ���� Ÿ�� ����

		zombie->Reset(); // ���� �ʱ�ȭ �������� �����ؼ� ���� �������� init�� Reset�� ȣ���ؾ� ��	
 		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f); // ���� ��ġ ����
		zombieList.push_back(zombie); // ���� ����Ʈ�� �߰�

	}
}
