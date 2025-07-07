#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"

Player::Player(const std::string& name)
	: GameObject(name)
{

}

void Player::SetPosition(const sf::Vector2f& pos) // �÷��̾��� ��ġ�� �����ϴ� �Լ�
{
	GameObject::SetPosition(pos); // GameObject�� SetPosition�� ȣ���Ͽ� �⺻ ��ġ ����
	body.setPosition(pos); // �÷��̾��� ��ü(body)�� ��ġ�� ����
}

void Player::SetRotation(float rot) // �÷��̾��� ȸ���� �����ϴ� �Լ�
{
	GameObject::SetRotation(rot); // GameObject�� SetRotation�� ȣ���Ͽ� �⺻ ȸ�� ����
	body.setRotation(rot); // �÷��̾��� ��ü(body)�� ȸ���� ����
}

void Player::SetScale(const sf::Vector2f& s) // �÷��̾��� ũ�⸦ �����ϴ� �Լ�
{
	GameObject::SetScale(s); // GameObject�� SetScale�� ȣ���Ͽ� �⺻ ũ�� ����
	body.setScale(s); // �÷��̾��� ��ü(body)�� ũ�⸦ ����
}

void Player::SetOrigin(const sf::Vector2f& o) // �÷��̾��� ������ �����ϴ� �Լ�
{
	GameObject::SetOrigin(o); // GameObject�� SetOrigin�� ȣ���Ͽ� �⺻ ���� ����
	body.setOrigin(o); // �÷��̾��� ��ü(body)�� ������ ����
}

void Player::SetOrigin(Origins preset) // �÷��̾��� ������ �����ϴ� �Լ� (�����ε�)
{
	GameObject::SetOrigin(preset); // GameObject�� SetOrigin�� ȣ���Ͽ� �⺻ ���� ����
	if (preset != Origins::Custom) // ���� ������ Custom�� �ƴ϶��
	{
		Utils::SetOrigin(body, preset); // �÷��̾��� ��ü(body)�� ������ ����
	}
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground; // �÷��̾��� ���� ���̾ Foreground�� ����
	sortingOrder = 0; // �÷��̾��� ���� ������ 0���� ����
	//SetOrigin(Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) // ���� ���� Game ������ Ȯ��
	{
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene(); // ���� ���� Game ���̶�� SceneGame �����͸� ����
	}
	else
	{
		sceneGame = nullptr; // ���� ���� Game ���� �ƴ϶�� SceneGame �����͸� nullptr�� ����
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
	if (Utils::Magnitude(direction) > 1.f) // ���� ���� ������ ũ�Ⱑ 1���� ũ�ٸ�
	{
		Utils::Normalize(direction); // ���� ������ ũ�Ⱑ 1���� ũ�� ����ȭ
	}
	SetPosition(position + direction * speed * dt); // �÷��̾��� ��ġ�� ������Ʈ

	sf::Vector2i mousePos = InputMgr::GetMousePosition();
	sf::Vector2f mouseWorldPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWorldPos - GetPosition());
	SetRotation(Utils::Angle(look));

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
