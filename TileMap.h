#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{
protected:
	sf::VertexArray va; // 타일 맵을 그리기 위한 버텍스 배열
	std::string spriteSheetId = "graphics/background_sheet.png"; 
	sf::Texture* texture = nullptr; 
	sf::Transform transform; // 변환 행렬

	sf::Vector2i cellCount; // 타일의 개수 (가로, 세로)
	sf::Vector2f cellSize; // 타일의 크기 (폭, 높이)

public:
	TileMap(const std::string& name = ""); 
	virtual ~TileMap() = default;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size); // 타일 맵 설정 함수
	void UpdateTransform(); // 변환 행렬 업데이트

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

