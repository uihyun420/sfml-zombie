#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size) 
{
	cellCount = count; 
	cellSize = size;

	va.clear(); 
	va.setPrimitiveType(sf::Quads);  
	va.resize(count.x * count.y * 4); 

	sf::Vector2f posOffset[4] = // 타일의 각 꼭짓점 위치 오프셋
	{
		{ 0.f, 0.f },
		{ size.x, 0.f },
		{ size.x, size.y },
		{ 0.f, size.y },
	};

	sf::Vector2f texCoords[4] = // 타일의 각 꼭짓점 텍스처 좌표
	{
		{ 0.f, 0.f },
		{ 50.f, 0.f },
		{ 50.f, 50.f },
		{ 0.f, 50.f },
	};

	for (int i = 0; i < count.y; ++i) // 타일 맵의 각 행과 열을 순회하면서 타일을 설정
	{
		for (int j = 0; j < count.x; ++j) // 각 열을 순회하면서 타일을 설정
		{
			int texIndex = Utils::RandomRange(0, 3); // 랜덤하게 텍스처 인덱스를 선택
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1) // 테두리 타일의 경우
			{
				texIndex = 3; // 테두리 타일은 항상 같은 텍스처 사용
			}

			int quadIndex = i * count.x + j;
			sf::Vector2f quadPos(j * size.x, i * size.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				va[vertexIndex].texCoords = texCoords[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
}



void TileMap::UpdateTransform() 
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
	UpdateTransform();
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;

	Set({ 50, 50 }, {50.f, 50.f});
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(spriteSheetId);

	SetOrigin(Origins::MC);
	SetScale({ 1.f, 1.f });
	SetRotation(45.f);
	SetPosition({ 0.f, 0.f });
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window) 
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform; 
	window.draw(va, state);
}

