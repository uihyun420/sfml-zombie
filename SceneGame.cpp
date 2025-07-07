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
	texIds.push_back("graphics/crosshair.png");


	AddGameObject(new TileMap("TileMap"));

	player = (Player*)AddGameObject(new Player("Player"));

	for (int i = 0; i < 100; ++i)
	{
	Zombie* zombie = (Zombie*)AddGameObject(new Zombie()); // ���� ����
	zombie->SetActive(false); // ���� ��Ȱ��ȭ	
	zombiePool.push_back(zombie); // ���� Ǯ�� �߰�	
	}


	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false); // ���콺 Ŀ�� ����

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});
	 
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC); // ���� ����
	
}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true); // ���콺 Ŀ�� ����

	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false); // ���� ��Ȱ��ȭ
		zombiePool.push_back(zombie); // ���� Ǯ�� �߰�
	}
	zombieList.clear(); // ���� ����Ʈ �ʱ�ȭ


	Scene::Exit();	// �� ����� ȣ��Ǵ� �Լ�
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition())); // Ŀ�� ��ġ ������Ʈ




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


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window); // ���� �⺻ �׸��� �Լ� ȣ��

	window.setView(uiView); // UI �� ����
	window.draw(cursor); // Ŀ�� �׸���

}



void SceneGame::SpawnZombies(int count)
{
	Zombie* zombie = nullptr; // ���� ������ �ʱ�ȭ	
	for (int i = 0; i < 10; ++i)
	{
		if (zombiePool.empty()) // ���� Ǯ�� ���� ���� ������
		{
			zombie = (Zombie*)AddGameObject(new Zombie()); // ���� ���� ����
			zombie->Init(); // ���� �ʱ�ȭ
		}
		else
		{
			zombie = zombiePool.front(); // ���� Ǯ���� ���� ��������	
			zombiePool.pop_front(); // ���� Ǯ���� ����	
			zombie->SetActive(true); // ���� Ȱ��ȭ	
		}


		Zombie* zombie = (Zombie*)AddGameObject(new Zombie()); // ���� ����
		zombie->Init(); // ���� �ʱ�ȭ

		zombie->SetType((Zombie::Type)Utils::RandomRange(0, Zombie::TotalTypes)); // ���� Ÿ�� ����

		zombie->Reset(); // ���� �ʱ�ȭ �������� �����ؼ� ���� �������� init�� Reset�� ȣ���ؾ� ��	
 		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f); // ���� ��ġ ����
		zombieList.push_back(zombie); // ���� ����Ʈ�� �߰�

	}
}
