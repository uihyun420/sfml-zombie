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
	sortingLayer = SortingLayers::Foreground; //����	���̾� ���� ���� ���̾� �׻� ���� �ϱ�
	sortingOrder = 0; //���� ���� ����


	SetType(type); //���� Ÿ�� ����

}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");	// �÷��̾� ã��

	body.setTexture(TEXTURE_MGR.Get(texId)); //�ؽ��� �Ŵ������� �ؽ��� ��������	
	SetOrigin(Origins::MC); //������ ����
	SetPosition({ 0.f,0.f }); //�ʱ� ��ġ ����	
	SetRotation(0.f); //�ʱ� ȸ�� ����	
	SetScale({ 1.f,1.f }); //�ʱ� ������ ����	
}

void Zombie::Update(float dt)
{
	direction = Utils::GetNormal(player->GetPosition() - position); //�÷��̾� ���� ���ϱ�
	SetRotation(Utils::Angle(direction)); //�÷��̾� �������� ȸ��	
	SetPosition(GetPosition() + direction * speed * dt); //�÷��̾� �������� �̵�	

}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body); //���� �׸���
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
