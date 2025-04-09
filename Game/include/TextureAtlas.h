#pragma once
#include <stdexcept>
#include <map>
#include "TextureCache.h"



class TextureAtlas
{
public:
	struct Region;

	TextureAtlas()
		: m_currentRegionIndex(0)
		, m_TextureAtlasPixelSize{ 0,0 }
		, m_CurrentFramePosition{ 0,0 }
		, m_FrameRect{ 0,0,0,0 }
		, m_texture(nullptr)
		, m_textureloaded(false)
	{
	}
	virtual ~TextureAtlas() = default;

	void Load(const std::string& filename)
	{
		m_Sprite.setTexture(m_texture->getTexture(filename));
		m_textureloaded = true;
	}
	void unLoad()
	{
		m_textureloaded = false;
	}
	bool TextureisLoaded()
	{
		return m_textureloaded;
	}
	/*const sf::Sprite& getCurrentFrameSprite() const
	{

		if (TextureisLoaded() == true)
		{
			m_Sprite.setTextureRect(m_FrameRect);
			return m_Sprite;
		}
		else
			throw std::runtime_error("the texture is not loaded");
	}*/
	sf::Sprite& getCurrentFrameSprite()
	{
		if (TextureisLoaded() == true)
		{
			m_Sprite.setTextureRect(m_FrameRect);
			return m_Sprite;
		}
		else
			throw std::runtime_error("the texture is not loaded");
	}

	bool hasNegativeValues(const sf::Vector2i& vec)
	{
		return vec.x < 0 || vec.y < 0;
	}

	void setVirtualGridStandard(const sf::Vector2i& VirtualGridSize,
		const sf::Vector2i& SpriteSheetPixelSize,
		const sf::Vector2i& frameSize,
		const sf::Vector2i& spacing = sf::Vector2i(0, 0))
	{
		if (hasNegativeValues(VirtualGridSize) || hasNegativeValues(SpriteSheetPixelSize) || hasNegativeValues(frameSize) || hasNegativeValues(spacing))
			throw std::out_of_range("size cannot be negative");

		int TotalWidth = VirtualGridSize.x * frameSize.x + (VirtualGridSize.x - 1) * spacing.x;
		int TotalHeight = VirtualGridSize.y * frameSize.y + (VirtualGridSize.y - 1) * spacing.y;

		if (TotalWidth > SpriteSheetPixelSize.x || TotalHeight > SpriteSheetPixelSize.y)
			throw std::runtime_error("The total size of the virtual grid (in rows and columns) cannot exceed or be equal to the size of the spritesheet.");
		if (VirtualGridSize.x == 0 && VirtualGridSize.y == 0)
			throw std::runtime_error("the grid cannot be empty");
		if (frameSize.x == 0 || frameSize.y == 0)
			throw std::runtime_error("frame size cannot be 0");
		if (frameSize.x >= SpriteSheetPixelSize.x || frameSize.y >= SpriteSheetPixelSize.y)
			throw std::runtime_error("frame size cannot be greater than or equal to Sprite-Sheet size (in pixels)");

		setSpriteSheetPixelSize(SpriteSheetPixelSize);

		m_RegionList.clear();
		addRegion({ 0,0 }, VirtualGridSize, frameSize, spacing);

		setFramePosition(0, 0);
	}
	const sf::Vector2i& getVirtualGridStandard() const
	{
		return m_RegionList[0].getRegionSize();
	}



	void setFramePosition(unsigned int x, unsigned int y)
	{
		const Region& activeRegion = m_RegionList[m_currentRegionIndex];
		if (x >= activeRegion.getRegionSize().x || y >= activeRegion.getRegionSize().y)
			throw std::out_of_range("coordinate outside the active region");

		m_CurrentFramePosition.x = x;
		m_CurrentFramePosition.y = y;
		updateFrameRect(x, y);

	}
	const sf::Vector2i& getFramePosition() const
	{
		return m_CurrentFramePosition;
	}
	void updateFrameRect(int gridX, int gridY)
	{
		const Region& activeRegion = m_RegionList[m_currentRegionIndex];
		m_FrameRect.left = activeRegion.getRegionPosition().x + gridX * (activeRegion.getFrameSize().x + activeRegion.getSpacing().x);
		m_FrameRect.top = activeRegion.getRegionPosition().y + gridY * (activeRegion.getFrameSize().y + activeRegion.getSpacing().y);
		m_FrameRect.width = activeRegion.getFrameSize().x;
		m_FrameRect.height = activeRegion.getFrameSize().y;
	}


	//position est en pixels(position du coin supérieur gauche de la région)
	//regionSize est en nombre de frames(ex: 7 colonnes(x), 6 lignes(y))
	//frameSize est en pixels(taille de chaque frame)
	//spacing est en pixels(espace entre les frames)
	void addRegion(const sf::Vector2i& position,
		const sf::Vector2i& regionSize,
		const sf::Vector2i& frameSize,
		const sf::Vector2i& spacing = sf::Vector2i(0, 0))
	{


		if (hasNegativeValues(regionSize) || hasNegativeValues(m_TextureAtlasPixelSize) || hasNegativeValues(frameSize) || hasNegativeValues(spacing))
			throw std::out_of_range("size cannot be negative");

		int TotalWidth = regionSize.x * frameSize.x + (regionSize.x - 1) * spacing.x;
		int TotalHeight = regionSize.y * frameSize.y + (regionSize.y - 1) * spacing.y;

		if (TotalWidth > m_TextureAtlasPixelSize.x || TotalHeight > m_TextureAtlasPixelSize.y)
			throw std::runtime_error("The total size of the virtual grid (in rows and columns) cannot exceed to the size of the spritesheet.");
		if (regionSize.x == 0 && regionSize.y == 0)
			throw std::runtime_error("the grid cannot be empty");
		if (frameSize.x == 0 || frameSize.y == 0)
			throw std::runtime_error("frame size cannot be 0");
		if (frameSize.x > m_TextureAtlasPixelSize.x || frameSize.y > m_TextureAtlasPixelSize.y)
			throw std::runtime_error("frame size cannot be greater than to Sprite-Sheet size (in pixels)");

		m_RegionList.push_back(Region(position, regionSize, frameSize, spacing));


		if (m_RegionList.size() == 1)
			m_currentRegionIndex = 0;
	}

	void setActiveRegion(const size_t& currentRegionindex)
	{
		if (currentRegionindex >= m_RegionList.size())
			throw  std::out_of_range("region index greater than the size of the region list in the Sprite-Sheet");

		m_currentRegionIndex = currentRegionindex;
	}
	const Region& getActiveRegion() const
	{
		return m_RegionList[m_currentRegionIndex];
	}
	void setSpriteSheetPixelSize(const sf::Vector2i& spritesheetsize)
	{
		m_TextureAtlasPixelSize = spritesheetsize;
	}
	const sf::Vector2i& getSpriteSheetPixelSize() const
	{
		return m_TextureAtlasPixelSize;
	}
	const Region& getRegion(const size_t& Regionindex) const
	{
		if (Regionindex >= m_RegionList.size())
			throw std::out_of_range("region index out of range");
		return m_RegionList[Regionindex];
	}
	Region& getRegion(const size_t& Regionindex)
	{
		if (Regionindex >= m_RegionList.size())
			throw std::out_of_range("region index out of range");
		return m_RegionList[Regionindex];
	}
	const size_t getRegionListSize() const
	{
		return m_RegionList.size();
	}
	void centerOrigin()
	{
		float CenterX = m_FrameRect.width / 2.0f;
		float CenterY = m_FrameRect.height / 2.0f;
		setOrigin(CenterX, CenterY);
	}
	void setOrigin(float x, float y)
	{
		m_Sprite.setOrigin(x, y);
	}
	void setOrigin(const sf::Vector2f& origin)
	{
		m_Sprite.setOrigin(origin);
	}
	const sf::Vector2f& getOrigin() const
	{
		return m_Sprite.getOrigin();
	}

	void setScale(float x, float y)
	{
		m_Sprite.setScale(x, y);
	}
	void setScale(float factor)
	{
		m_Sprite.setScale(factor, factor);
	}
	void setScale(const sf::Vector2f& factors)
	{
		m_Sprite.setScale(factors);
	}
	const sf::Vector2f& getScale() const
	{
		return m_Sprite.getScale();
	}

private:
	size_t m_currentRegionIndex;
	std::vector<Region> m_RegionList;

	sf::Vector2i m_TextureAtlasPixelSize;

	sf::Vector2i m_CurrentFramePosition;
	sf::IntRect m_FrameRect;

	sf::Sprite m_Sprite;
	TextureCache* m_texture;

	bool m_textureloaded;

	struct Region
	{
		sf::Vector2i m_RegionPosition;
		sf::Vector2i m_RegionSize;
		sf::Vector2i m_FrameSize;
		sf::Vector2i m_Spacing;

		Region(const sf::Vector2i& position,
			const sf::Vector2i& regionsize,
			const sf::Vector2i& frameSize,
			const sf::Vector2i& spacing = sf::Vector2i(0, 0))
			: m_RegionPosition(position)
			, m_RegionSize(regionsize)
			, m_FrameSize(frameSize)
			, m_Spacing(spacing)
		{
		}
		void setRegionPosition(sf::Vector2i position)
		{
			m_RegionPosition = position;
		}

		const sf::Vector2i& getRegionPosition() const
		{
			return m_RegionPosition;
		}
		void setFrameSize(unsigned int width, unsigned int height)
		{
			m_FrameSize.x = width;
			m_FrameSize.y = height;
		}
		void setFrameSize(sf::Vector2i size)
		{
			m_FrameSize = size;
		}
		const sf::Vector2i& getFrameSize() const
		{
			return m_FrameSize;
		}
		void setSpacing(sf::Vector2i spacing)
		{
			m_Spacing = spacing;
		}
		const sf::Vector2i& getSpacing() const
		{
			return m_Spacing;
		}
		void setRegionSize(sf::Vector2i regionsize)
		{
			m_RegionSize = regionsize;
		}
		const sf::Vector2i& getRegionSize() const
		{
			return m_RegionSize;
		}
	};
};


using tile = char;
class TileType
{
public:
	TileType();
	~TileType()
	{
		delete m_textureatlas;
		m_textureatlas = nullptr;
	}
	const tile& getTileType()const
	{
		return m_tiletype;
	}
	tile& getTileType()
	{
		return m_tiletype;
	}
	void setTileType(tile tiletype)
	{
		m_tiletype = tiletype;
	}
	const bool& isHatHitbox()const
	{
		return m_hashitbox;
	}
	void setIsHatHitbox(bool ishathitbox)
	{
		m_hashitbox = ishathitbox;
	}
	const sf::Sprite& getSprite()const
	{
		return m_textureatlas->getCurrentFrameSprite();
	}


	sf::Sprite& getSprite()
	{
		return m_textureatlas->getCurrentFrameSprite();
	}
	void setSprite(const std::string& filename, const sf::Vector2i& position,
		           const sf::Vector2i& regionSize,
		           const sf::Vector2i& frameSize,
		           const sf::Vector2i& spacing = sf::Vector2i(0, 0))
	{
		m_textureatlas->Load(filename);
		m_textureatlas->addRegion(position, regionSize, frameSize, spacing);
	}
private:
	tile m_tiletype;
	TextureAtlas* m_textureatlas;
	bool m_hashitbox;
};
class TileMap
{
public:

private:
	std::map<sf::Vector2i, tile> m_map;
};