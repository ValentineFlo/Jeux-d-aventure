#pragma once
#include <stdexcept>
#include <map>
#include <fstream>
#include <memory>
#include "TextureCache.h"
#include "Region.h"
#include "RegionManager.h"



class TextureAtlas
{
protected:
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
	const bool TextureisLoaded() 
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
		const sf::Vector2i& TextureAtlasPixelSize,
		const sf::Vector2i& frameSize,
		const sf::Vector2i& spacing = sf::Vector2i(0, 0))
	{
		if (hasNegativeValues(VirtualGridSize) || hasNegativeValues(TextureAtlasPixelSize) || hasNegativeValues(frameSize) || hasNegativeValues(spacing))
			throw std::out_of_range("size cannot be negative");

		int TotalWidth = VirtualGridSize.x * frameSize.x + (VirtualGridSize.x - 1) * spacing.x;
		int TotalHeight = VirtualGridSize.y * frameSize.y + (VirtualGridSize.y - 1) * spacing.y;

		if (TotalWidth > TextureAtlasPixelSize.x || TotalHeight > TextureAtlasPixelSize.y)
			throw std::runtime_error("The total size of the virtual grid (in rows and columns) cannot exceed or be equal to the size of the spritesheet.");
		if (VirtualGridSize.x == 0 && VirtualGridSize.y == 0)
			throw std::runtime_error("the grid cannot be empty");
		if (frameSize.x == 0 || frameSize.y == 0)
			throw std::runtime_error("frame size cannot be 0");
		if (frameSize.x >= TextureAtlasPixelSize.x || frameSize.y >= TextureAtlasPixelSize.y)
			throw std::runtime_error("frame size cannot be greater than or equal to Sprite-Sheet size (in pixels)");

		setTextureAtlasPixelSize(TextureAtlasPixelSize);

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


	//position est en pixels(position du coin sup�rieur gauche de la r�gion)
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
	void setTextureAtlasPixelSize(const sf::Vector2i& textureatlassize)
	{
		m_TextureAtlasPixelSize = textureatlassize;
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
	/*void HorizontalMirror(float x, float y)
	{
		setScale(-x, y);
	}*/
	void setScale(const sf::Vector2f& factors)
	{
		m_Sprite.setScale(factors);
	}
	const sf::Vector2f& getScale() const
	{
		return m_Sprite.getScale();
	}
	
		
protected:
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
//class TileType
//{
//public:
//	TileType();
//	~TileType()
//	{
//		delete m_textureatlas;
//		m_textureatlas = nullptr;
//	}
//	const tile& getTileType()const
//	{
//		return m_tiletype;
//	}
//	tile& getTileType()
//	{
//		return m_tiletype;
//	}
//	void setTileType(tile tiletype)
//	{
//		m_tiletype = tiletype;
//	}
//	const bool& isHatHitbox()const
//	{
//		return m_hashitbox;
//	}
//	void setIsHatHitbox(bool ishathitbox)
//	{
//		m_hashitbox = ishathitbox;
//	}
//	const sf::Sprite& getSprite()const
//	{
//		return m_textureatlas->getCurrentFrameSprite();
//	}
//
//
//	sf::Sprite& getSprite()
//	{
//		return m_textureatlas->getCurrentFrameSprite();
//	}
//	void setSprite(const std::string& filename, const sf::Vector2i& position,
//		           const sf::Vector2i& regionSize,
//		           const sf::Vector2i& frameSize,
//		           const sf::Vector2i& spacing = sf::Vector2i(0, 0))
//	{
//		m_textureatlas->Load(filename);
//		m_textureatlas->addRegion(position, regionSize, frameSize, spacing);
//	}
//private:
//	tile m_tiletype;
//	TextureAtlas* m_textureatlas;
//	bool m_hashitbox;
//};


//position est en pixels(position du coin sup�rieur gauche de la r�gion)
	//regionSize est en nombre de frames(ex: 7 colonnes(x), 6 lignes(y))
	//frameSize est en pixels(taille de chaque frame)
	//spacing est en pixels(espace entre les frames)
class TileSet : TextureAtlas
{
public:
	TileSet(TextureCache* texture)
		:TextureAtlas()
		,m_factor(3.0f)
	{
		m_texture = texture;
		setTextureAtlasPixelSize({ 160,128 });
		Load("TileSet\\TilesetTest.png");
		addRegion(sf::Vector2i(0, 8), sf::Vector2i(1, 1), sf::Vector2i(8, 8));//petit sol rouge r
		addRegion(sf::Vector2i(8, 8), sf::Vector2i(1, 1), sf::Vector2i(24, 24));// gros sol rouge R
		addRegion(sf::Vector2i(8+24, 8), sf::Vector2i(1, 1), sf::Vector2i(24, 24));// fond casser 
		addRegion(sf::Vector2i(8 + 24+24, 8), sf::Vector2i(1, 1), sf::Vector2i(8, 8));// petit sol gris foncer
		addRegion(sf::Vector2i(8 + 24 + 24, 16), sf::Vector2i(1, 1), sf::Vector2i(8, 8));// fond noir
		addRegion(sf::Vector2i(8 + 24 + 24+8, 8), sf::Vector2i(1, 1), sf::Vector2i(24, 24));// gros sol gris foncer
		addRegion(sf::Vector2i(8 + 24 + 24 + 8+24, 8), sf::Vector2i(1, 1), sf::Vector2i(24, 24));// fond sol gris foncer
		addRegion(sf::Vector2i(8 + 24 + 24 + 8 + 24+24-1, 8-1), sf::Vector2i(1, 1), sf::Vector2i(25, 9));// tapis roulant

		//addRegion(sf::Vector2i(0, 35), sf::Vector2i(1, 1), sf::Vector2i(7, 13));//petit sol jaune n�1
		//addRegion(sf::Vector2i(0, 35+13), sf::Vector2i(1, 1), sf::Vector2i(7, 7));//petit sol jaune n�2
		//addRegion(sf::Vector2i(7, 35), sf::Vector2i(1, 1), sf::Vector2i(7, 13));//gros sol jaune 

		setScale(m_factor);

		registerTile('r', 0,COLLISIONABLE);//petit sol rouge r
		registerTile('R', 1, COLLISIONABLE);// gros sol rouge 
		registerTile('C', 2, NONE);// fond casser
		registerTile('g', 3, COLLISIONABLE);// petit sol gris foncer
		registerTile('N', 4, NONE);// fond noir
		registerTile('G', 5,COLLISIONABLE);// gros sol gris foncer
		registerTile('A', 6,NONE);//fond sol gris foncer
		registerTile('T', 7,COLLISIONABLE);// tapis roulant

	}
	~TileSet()
	{
		
	}
	void registerTile( const tile& tile, const size_t& idxregionlist, const RegionType& regiontype)
	{
		m_tileset.insert({ tile, std::make_pair(idxregionlist,regiontype)});
	}
	const sf::Sprite& getTileSprite(const tile& tile) 
	{
		auto it = m_tileset.find(tile);
		if(it == m_tileset.end())
			throw std::out_of_range("The tile is not in the std::map m_tileset");
		setActiveRegion(it->second.first);
		setFramePosition(0, 0);
		return getCurrentFrameSprite();
	}
	const sf::Vector2i& getTileSize(const tile& tile) const
	{
		auto it = m_tileset.find(tile);
		if (it == m_tileset.end())
			throw std::out_of_range("The tile is not in the std::map m_tileset");
		return getRegion(it->second.first).getFrameSize();
	}
	const sf::Vector2i& getTileSize(const tile& tile) 
	{
		auto it = m_tileset.find(tile);
		if (it == m_tileset.end())
			throw std::out_of_range("The tile is not in the std::map m_tileset");
		return getRegion(it->second.first).getFrameSize();
	}
	const float& getFactor()const
	{
		return m_factor;
	}
	const RegionType& getRegionType(const tile& tile) const
	{
		auto it = m_tileset.find(tile);
		if (it == m_tileset.end())
			throw std::out_of_range("The tile is not in the std::map m_tileset");
		return it->second.second;
	}
	const RegionType& getRegionType(const tile& tile) 
	{
		auto it = m_tileset.find(tile);
		if (it == m_tileset.end())
			throw std::out_of_range("The tile is not in the std::map m_tileset");
		return it->second.second;
	}
private:
	
	std::map<tile, std::pair< size_t, RegionType>> m_tileset;
	float m_factor;
};



namespace sf
{
	bool operator<(const sf::Vector2i& left, const sf::Vector2i& right)
	{
		return (left.x < right.x) || (left.x == right.x && left.y < right.y);
	}
}
class TileMap:public IComposite
{
public:
	TileMap(TextureCache* texture)
		:IComposite(nullptr)
		,m_mapmodified(false)
	{
		m_tileset = new TileSet(texture);
		m_regionmanager = new RegionManager();
		m_BASE_CELL_SIZE = sf::Vector2i(8 * m_tileset->getFactor(), 8 * m_tileset->getFactor());
	}
	
	~TileMap()
	{
		delete m_tileset;
		m_tileset = nullptr;
		delete m_regionmanager;
		m_regionmanager = nullptr;
	}
	//Problème de position
	sf::Vector2i ConvertPixeltoCase(const sf::Vector2i& position)
	{
		return sf::Vector2i(static_cast<int>(position.x / getBASE_CELL_SIZE().x), static_cast<int>(position.y / getBASE_CELL_SIZE().y));
	}
	sf::Vector2i ConvertCasetoPixel(const sf::Vector2i& position)
	{
		return sf::Vector2i(ConvertPixeltoCase(position).x * getBASE_CELL_SIZE().x, ConvertPixeltoCase(position).y * getBASE_CELL_SIZE().y);
	}
	//Problème de position
	void CreateEmpty(const unsigned int& x,  const unsigned int& y)
	{
		m_map.clear();

		int gridX = static_cast<int>(std::ceil(x /  getBASE_CELL_SIZE().x));
		int gridY = static_cast<int>(std::ceil(y / getBASE_CELL_SIZE().y));

		for (int CaseX = 0;CaseX < gridX;++CaseX)
		{
			for (int CaseY = 0;CaseY < gridY;++CaseY)
			{
				setTile({ CaseX ,CaseY }, 'C');
			}
		}
	}
	void setTile(const sf::Vector2i& position, const tile& tile)
	{
		if(m_tileset->getRegionType(tile)!= NONE)
		{
			
			auto Newregion = m_regionmanager->createRegion(m_tileset->getRegionType(tile),
										static_cast<float>(ConvertCasetoPixel(position).x),
										static_cast<float>(ConvertCasetoPixel(position).y),
										static_cast<float>(m_tileset->getTileSize(tile).x*m_tileset->getFactor()),
										static_cast<float>(m_tileset->getTileSize(tile).y * m_tileset->getFactor()), this);

			m_map[position] = std::make_pair(tile, std::move(Newregion));
		}
		else
			m_map[position] = std::make_pair(tile, nullptr);
		
		setMapModified(true);
	}
	const tile& getTile(const sf::Vector2i& position) const
	{
		auto it = m_map.find(position);
		if(it==m_map.end())
			throw std::out_of_range("The position is not in the std::map m_map");
		return it->second.first;
	}
	tile& getTile(const sf::Vector2i& position)
	{
		auto it = m_map.find(position);
		if (it == m_map.end())
			throw std::out_of_range("The position is not in the std::map m_map");
		return it->second.first;
	}
	bool hasTile(const sf::Vector2i& position)
	{
		return m_map.find(position) != m_map.end();
	}
	void removeTile(const sf::Vector2i& position)
	{
		auto it = m_map.find(position);
		if (it == m_map.end())
			throw std::out_of_range("The position is not in the std::map m_map");
		m_map.erase(it);
		setMapModified(true);
	}

	void Render( sf::RenderWindow& window)
	{
		for (auto it = m_map.begin();it != m_map.end();++it)
		{
			const sf::Vector2i& gridpos = it->first;
			const tile& tiletype = it->second.first;

			sf::Sprite tileSprite = m_tileset->getTileSprite(tiletype);
			tileSprite.setPosition(static_cast<float>(gridpos.x * getBASE_CELL_SIZE().x),
								   static_cast<float>(gridpos.y * getBASE_CELL_SIZE().y));
			window.draw(tileSprite);
		}
	}
	const std::map<sf::Vector2i, std::pair< tile, std::unique_ptr<IRegion>>>& getMap() const
	{
		return m_map;
	}
	std::map<sf::Vector2i, std::pair< tile, std::unique_ptr<IRegion>>>& getMap()
	{
		return m_map;
	}
	const sf::Vector2i& getBASE_CELL_SIZE() const
	{
		return m_BASE_CELL_SIZE;
	}
	const bool& isMapModified() const
	{
		return m_mapmodified;
	}
	void setMapModified(bool mapmodifed)
	{
		m_mapmodified = mapmodifed;
	}
	void resetMapModified()
	{
		setMapModified(false);
	}
	bool hasRegion(const sf::Vector2i& position) const
	{
		auto it = m_map.find(position);
		if(it == m_map.end())
			throw std::out_of_range("The position is not in the std::map m_map");
		return it->second.second != nullptr;
	}
	const std::unique_ptr<IRegion>& getRegion(const sf::Vector2i& position) const
	{
		auto it = m_map.find(position);
		if (it == m_map.end())
			throw std::out_of_range("The position is not in the std::map m_map");
		return it->second.second;
	}
	const std::unique_ptr<IRegion>& getRegion(const sf::Vector2i& position) 
	{
		auto it = m_map.find(position);
		if (it == m_map.end())
			throw std::out_of_range("The position is not in the std::map m_map");
		return it->second.second;
	}

private:
	
	std::map<sf::Vector2i, std::pair< tile, std::unique_ptr<IRegion>>> m_map;
	TileSet* m_tileset;
	sf::Vector2i m_BASE_CELL_SIZE;
	bool m_mapmodified;
	RegionManager* m_regionmanager;
};

class LevelFactory
{
public:
	
	static bool SaveLevel(const TileMap& map, const std::string& filename)
	{
		std::ofstream file(filename);
		if (!file)
			throw std::runtime_error("file cannot be opened to save data");

		int m_minX;
		int m_minY;
		int m_maxX;
		int m_maxY;
		int m_TileCount;
		const auto& tileMap = map.getMap();
		if (tileMap.size() == 0)
		{
			m_minX = 0;
			m_minY = 0;
			m_maxX = 0;
			m_maxY = 0;
			m_TileCount = 0;

			file << "[METADATA]" << "\n";
			file << "MIN_X = " << m_minX  << "\n";
			file << "MIN_Y = " << m_minY << "\n";
			file << "MAX_X = " << m_maxX << "\n";
			file << "MAX_Y = " << m_maxY << "\n";
			file << "TILE_COUNT = " << m_TileCount << "\n";
			file << "\n";

			file << "[TILE_DATA]" << "\n";

			file.flush();
			return true;
		}
		m_minX = std::numeric_limits<int>::max();
		m_minY = std::numeric_limits<int>::max();
		m_maxX = std::numeric_limits<int>::min();
		m_maxY = std::numeric_limits<int>::min();
		for (const auto& [position, tile] : tileMap)
		{
			if (position.x < m_minX)
				m_minX = position.x;
			if (position.y < m_minY)
				m_minY = position.y;

			if (position.x > m_maxX)
				m_maxX = position.x;
			if (position.y > m_maxY)
				m_maxY = position.y;
		}
		m_TileCount = static_cast<int>(tileMap.size());

		file << "[METADATA]" << "\n";
		file << "MIN_X = " << m_minX << "\n";
		file << "MIN_Y = " << m_minY << "\n";
		file << "MAX_X = " << m_maxX << "\n";
		file << "MAX_Y = " << m_maxY << "\n";
		file << "TILE_COUNT = " << m_TileCount << "\n";
		file << "\n";

		file << "[TILE_DATA]" << "\n";
		for (const auto& [position, pairTileandRegion] : tileMap)
			file << "{" << position.x << "," << position.y << "}" << "  " << pairTileandRegion.first <<"  "<< pairTileandRegion.second <<"\n";

		file.flush();
		return true;
	}

	static bool LoadLevel(TileMap& map, const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file)
			throw std::runtime_error("file cannot be opened to load data");

		int m_minX;
		int m_minY;
		int m_maxX;
		int m_maxY;
		int m_TileCount;
		int Tilecounter = 0;
		std::string line;
		std::map< std::string, int*> m_metadata;
		m_metadata["MIN_X"] = &m_minX;
		m_metadata["MIN_Y"] = &m_minY;
		m_metadata["MAX_X"] = &m_maxX;
		m_metadata["MAX_Y"] = &m_maxY;
		m_metadata["TILE_COUNT"] = &m_TileCount;
		bool inMetadataSection = false;
		bool inTileDataSection = false;
		map.getMap().clear();

		while (std::getline(file, line))
		{
			if (line == "[METADATA]")
			{
				inMetadataSection = true;
				inTileDataSection = false;
				continue;
			}
			if (line == "[TILE_DATA]")
			{
				inMetadataSection = false;
				inTileDataSection = true;
				continue;
			}
			if (inMetadataSection == true && !line.empty())
			{
				auto equal = line.find('=');
				std::string key = line.substr(0, equal - 1);
				std::string value = line.substr(equal + 1);

				auto mapit = m_metadata.find(key);
				if (mapit != m_metadata.end())
					*(mapit->second) = std::stoi(value);
				else
					throw std::runtime_error("Unknown metadata key: " + key);
			}
			//{16,6}  tile  Region
			if (inTileDataSection == true && !line.empty())
			{
				auto braceopen = line.find('{');
				auto braceclose = line.find('}');
				auto comma = line.find(',');

				auto x = std::stoi(line.substr(braceopen + 1, comma - braceopen - 1));
				auto y = std::stoi(line.substr(comma + 1, braceclose - comma - 1));
				auto tilepos = line.find_first_not_of(" ", braceclose + 1);
				char tiletype = line[tilepos];
				auto region = line.find_first_not_of(" ", tilepos + 1);

				if (x >= m_minX && x <= m_maxX && y >= m_minY && y <= m_maxY)
				{
					map.setTile({ x,y }, (tiletype));
					Tilecounter++;
				}
				else
					throw std::out_of_range("Tile coordinates out of declared bounds");
			}
		}
		if (Tilecounter != *m_metadata["TILE_COUNT"])
			throw std::runtime_error("There is a discrepancy between the number of tiles announced and the number of tiles counted. m_TileCount = " + std::to_string(m_TileCount) + " Tilecounter = " + std::to_string(Tilecounter));
		return true;
	}

};