#include "stdafx.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "Zombie.h"


Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Bullet::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Bullet::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Bullet::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Bullet::Release()
{
}

void Bullet::Reset() // 총알 초기화 함수
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene()); // 현재 씬을 게임 씬으로 캐스팅
	body.setTexture(TEXTURE_MGR.Get(texId), true); 
	SetOrigin(Origins::ML);

	SetPosition(sf::Vector2f(0, 0));
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });

	direction = { 0.1,0.f };
	speed = 0.f;
	damage = 0;
}

void Bullet::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	hitBox.UpdateTransform(body, GetLocalBounds()); // 히트박스 업데이트

	//충돌처리
	const auto& list = sceneGame->GetZombies();
	for(auto& zombie : list)
	{
		if (Utils::CheckCollision(hitBox.rect, zombie->GetHitBox().rect))
		{
			SetActive(false); // 총알 비활성화
			zombie->OnDamage(damage); // 좀비에게 데미지 적용
			break; // 충돌이 발생하면 루프를 종료
		}
		
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);   // 히트박스 그리기

}

void Bullet::Fire(const sf::Vector2f& pos, const sf::Vector2f& dir, float s, int d) 
{
	SetPosition(pos);
	direction = dir;
	speed = s;
	damage = d;

	SetRotation(Utils::Angle(direction));
}

