#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground; //솔팅	레이어 설정 솔팅 레이어 항상 설정 하기
	sortingOrder = 0; //솔팅 오더 설정


	SetType(type); //좀비 타입 설정

}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");	// 플레이어 찾기

	body.setTexture(TEXTURE_MGR.Get(texId)); //텍스쳐 매니저에서 텍스쳐 가져오기	
	SetOrigin(Origins::MC); //오리진 설정
	SetPosition({ 0.f,0.f }); //초기 위치 설정	
	SetRotation(0.f); //초기 회전 설정	
	SetScale({ 1.f,1.f }); //초기 스케일 설정	
}

void Zombie::Update(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - position); //플레이어 방향 구하기
	SetRotation(Utils::Angle(direction)); //플레이어 방향으로 회전	
	SetPosition(GetPosition() + direction * speed * dt); //플레이어 방향으로 이동	

}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body); //좀비 그리기
}

void Zombie::SetType(Type type)
{
	this->type = type;
	switch (this->type)
	{
		case Type::Bloater:
			texId = "graphics/bloater.png";
			maxHp = 100;
			speed = 100.f;
			damage = 100.f;
			attackintervale = 1.f;
			break;
		case Type::chaser:
			texId = "graphics/chaser.png";
			maxHp = 50;
			speed = 200.f;
			damage = 50.f;
			attackintervale = 1.f;
			break;
		case Type::Crawler:
			texId = "graphics/crawler.png";
			maxHp = 50;
			speed = 50.f;
			damage = 50.f;
			attackintervale = 1.f;
			break;
	}
}
