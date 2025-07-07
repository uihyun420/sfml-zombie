#pragma once
#include "GameObject.h"

class SceneGame;

class Player : public GameObject // ���� ������Ʈ�� ��ӹ޾� �÷��̾� Ŭ������ ����
{
protected:
	sf::Sprite body; // �÷��̾ �׸������� ��ü
	std::string texId = "graphics/player.png"; // �÷��̾��� �ؽ��� ���̵�

	sf::Vector2f direction; // �÷��̾��� �̵� ����
	sf::Vector2f look; // �÷��̾ �ٶ󺸴� ����

	float speed = 500.f; // �÷��̾��� �̵� �ӵ�

	SceneGame* sceneGame = nullptr; // �÷��̾ ���� ���� ��

public:
	Player(const std::string& name = ""); // ������, �̸��� ���ڷ� ����
	~Player() override = default;

	void SetPosition(const sf::Vector2f& pos) override; // �÷��̾��� ��ġ�� ����
	void SetRotation(float rot) override; // �÷��̾��� ȸ�� ������ ����
	void SetScale(const sf::Vector2f& s) override; // �÷��̾��� ũ�⸦ ����
	void SetOrigin(const sf::Vector2f& o) override; // �÷��̾��� ������ ����
	void SetOrigin(Origins preset) override; // �÷��̾��� ������ �̸� ���ǵ� ������ ����

	void Init() override; // �ʱ�ȭ �Լ�, �÷��̾��� �ؽ��ĸ� �ε��ϰ� ��������Ʈ�� ����
	void Release() override; // ���ҽ� ���� �Լ�, �÷��̾��� �ؽ��ĸ� ����
	void Reset() override; // �÷��̾��� ���¸� �ʱ�ȭ
	void Update(float dt) override; // ������Ʈ �Լ�, �÷��̾��� �̵� �� ȸ���� ó��
	void Draw(sf::RenderWindow& window) override; // �׸��� �Լ�, �÷��̾��� ��������Ʈ�� �����쿡 �׸���
};

