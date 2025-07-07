#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	sf::VertexArray va;
	std::string spriteSheetId = "graphics/background_sheet.png";
	sf::Texture* texture = nullptr;
	sf::Transform transform;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;

public:
	TileMap(const std::string& name = "");
	virtual ~TileMap() = default;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void UpdateTransform();

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

