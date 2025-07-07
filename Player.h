#pragma once
#include "GameObject.h"

class SceneGame;

class Player : public GameObject // 게임 오브젝트를 상속받아 플레이어 클래스를 생성
{
protected:
	sf::Sprite body; // 플레이어를 그리기위한 객체
	std::string texId = "graphics/player.png"; // 플레이어의 텍스쳐 아이디

	sf::Vector2f direction; // 플레이어의 이동 방향
	sf::Vector2f look; // 플레이어가 바라보는 방향

	float speed = 500.f; // 플레이어의 이동 속도

	SceneGame* sceneGame = nullptr; // 플레이어가 속한 게임 씬

public:
	Player(const std::string& name = ""); // 생성자, 이름을 인자로 받음
	~Player() override = default;

	void SetPosition(const sf::Vector2f& pos) override; // 플레이어의 위치를 설정
	void SetRotation(float rot) override; // 플레이어의 회전 각도를 설정
	void SetScale(const sf::Vector2f& s) override; // 플레이어의 크기를 설정
	void SetOrigin(const sf::Vector2f& o) override; // 플레이어의 원점을 설정
	void SetOrigin(Origins preset) override; // 플레이어의 원점을 미리 정의된 값으로 설정

	void Init() override; // 초기화 함수, 플레이어의 텍스쳐를 로드하고 스프라이트를 설정
	void Release() override; // 리소스 해제 함수, 플레이어의 텍스쳐를 해제
	void Reset() override; // 플레이어의 상태를 초기화
	void Update(float dt) override; // 업데이트 함수, 플레이어의 이동 및 회전을 처리
	void Draw(sf::RenderWindow& window) override; // 그리기 함수, 플레이어의 스프라이트를 윈도우에 그린다
};

