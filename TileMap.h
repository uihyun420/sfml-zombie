#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	sf::VertexArray va; // Ÿ�� ���� �׸��� ���� ���ؽ� �迭
	std::string spriteSheetId = "graphics/background_sheet.png"; 
	sf::Texture* texture = nullptr; 
	sf::Transform transform; // ��ȯ ���

	sf::Vector2i cellCount; // Ÿ���� ���� (����, ����)
	sf::Vector2f cellSize; // Ÿ���� ũ�� (��, ����)

public:
	TileMap(const std::string& name = ""); 
	virtual ~TileMap() = default;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size); // Ÿ�� �� ���� �Լ�
	void UpdateTransform(); // ��ȯ ��� ������Ʈ

	void SetPosition(const sf::Vector2f& pos) override; 
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

