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
	Zombie* zombie = (Zombie*)AddGameObject(new Zombie()); // 좀비 생성
	zombie->SetActive(false); // 좀비 비활성화	
	zombiePool.push_back(zombie); // 좀비 풀에 추가	
	}


	Scene::Init();
}

void SceneGame::Enter()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(false); // 마우스 커서 숨김

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({0.f, 0.f});
	 
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC); // 원점 설정
	
}

void SceneGame::Exit()
{
	FRAMEWORK.GetWindow().setMouseCursorVisible(true); // 마우스 커서 생김

	for (Zombie* zombie : zombieList)
	{
		zombie->SetActive(false); // 좀비 비활성화
		zombiePool.push_back(zombie); // 좀비 풀에 추가
	}
	zombieList.clear(); // 좀비 리스트 초기화


	Scene::Exit();	// 씬 종료시 호출되는 함수
}

void SceneGame::Update(float dt)
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition())); // 커서 위치 업데이트




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


void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window); // 씬의 기본 그리기 함수 호출

	window.setView(uiView); // UI 뷰 설정
	window.draw(cursor); // 커서 그리기

}



void SceneGame::SpawnZombies(int count)
{
	Zombie* zombie = nullptr; // 좀비 포인터 초기화	
	for (int i = 0; i < 10; ++i)
	{
		if (zombiePool.empty()) // 좀비 풀에 남은 좀비가 없으면
		{
			zombie = (Zombie*)AddGameObject(new Zombie()); // 새로 좀비 생성
			zombie->Init(); // 좀비 초기화
		}
		else
		{
			zombie = zombiePool.front(); // 좀비 풀에서 좀비 가져오기	
			zombiePool.pop_front(); // 좀비 풀에서 제거	
			zombie->SetActive(true); // 좀비 활성화	
		}


		Zombie* zombie = (Zombie*)AddGameObject(new Zombie()); // 좀비 생성
		zombie->Init(); // 좀비 초기화

		zombie->SetType((Zombie::Type)Utils::RandomRange(0, Zombie::TotalTypes)); // 좀비 타입 설정

		zombie->Reset(); // 좀비 초기화 동적으로 생성해서 씬에 넣을때는 init와 Reset을 호출해야 함	
 		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f); // 좀비 위치 설정
		zombieList.push_back(zombie); // 좀비 리스트에 추가

	}
}
