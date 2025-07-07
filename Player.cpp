#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"

Player::Player(const std::string& name)
	: GameObject(name)
{

}

void Player::SetPosition(const sf::Vector2f& pos) // 플레이어의 위치를 설정하는 함수
{
	GameObject::SetPosition(pos); // GameObject의 SetPosition을 호출하여 기본 위치 설정
	body.setPosition(pos); // 플레이어의 몸체(body)의 위치를 설정
}

void Player::SetRotation(float rot) // 플레이어의 회전을 설정하는 함수
{
	GameObject::SetRotation(rot); // GameObject의 SetRotation을 호출하여 기본 회전 설정
	body.setRotation(rot); // 플레이어의 몸체(body)의 회전을 설정
}

void Player::SetScale(const sf::Vector2f& s) // 플레이어의 크기를 설정하는 함수
{
	GameObject::SetScale(s); // GameObject의 SetScale을 호출하여 기본 크기 설정
	body.setScale(s); // 플레이어의 몸체(body)의 크기를 설정
}

void Player::SetOrigin(const sf::Vector2f& o) // 플레이어의 원점을 설정하는 함수
{
	GameObject::SetOrigin(o); // GameObject의 SetOrigin을 호출하여 기본 원점 설정
	body.setOrigin(o); // 플레이어의 몸체(body)의 원점을 설정
}

void Player::SetOrigin(Origins preset) // 플레이어의 원점을 설정하는 함수 (오버로딩)
{
	GameObject::SetOrigin(preset); // GameObject의 SetOrigin을 호출하여 기본 원점 설정
	if (preset != Origins::Custom) // 만약 원점이 Custom이 아니라면
	{
		Utils::SetOrigin(body, preset); // 플레이어의 몸체(body)의 원점을 설정
	}
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground; // 플레이어의 정렬 레이어를 Foreground로 설정
	sortingOrder = 0; // 플레이어의 정렬 순서를 0으로 설정
	//SetOrigin(Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) // 현재 씬이 Game 씬인지 확인
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene(); // 현재 씬이 Game 씬이라면 SceneGame 포인터를 설정
	}
	else
	{
		sceneGame = nullptr; // 현재 씬이 Game 씬이 아니라면 SceneGame 포인터를 nullptr로 설정
	}

	body.setTexture(TEXTURE_MGR.Get(texId), true); 
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	direction = { 0.f, 0.f };
	look = { 1.0f, 0.f };
}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal); 
	direction.y = InputMgr::GetAxis(Axis::Vertical); 
	if (Utils::Magnitude(direction) > 1.f) // 만약 방향 벡터의 크기가 1보다 크다면
	{
		Utils::Normalize(direction); // 방향 벡터의 크기가 1보다 크면 정규화
	}
	SetPosition(position + direction * speed * dt); // 플레이어의 위치를 업데이트

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
