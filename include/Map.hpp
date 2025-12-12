#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

/**
 * @enum CellType
 * @brief Types of cells in the game map
 */
enum class CellType {
    EMPTY,      ///< Empty space where player can walk
    WALL,       ///< Indestructible wall
    BLOCK,      ///< Destructible block
    EXPLOSION   ///< Explosion effect
};

/**
 * @class Map
 * @brief Represents the game map/grid
 * 
 * This class manages the game map, including walls, blocks, and explosions.
 * It handles collision detection and map updates.
 */
class Map {
public:
    /**
     * @brief Constructor for Map
     * @param width Width of the map in cells
     * @param height Height of the map in cells
     */
    Map(int width, int height);
    
    /**
     * @brief Destructor
     */
    ~Map();
    
    /**
     * @brief Get the width of the map
     * @return Map width
     */
    int getWidth() const;
    
    /**
     * @brief Get the height of the map
     * @return Map height
     */
    int getHeight() const;
    
    /**
     * @brief Get the cell type at a specific position
     * @param x X coordinate
     * @param y Y coordinate
     * @return CellType at the position
     */
    CellType getCell(int x, int y) const;
    
    /**
     * @brief Set the cell type at a specific position
     * @param x X coordinate
     * @param y Y coordinate
     * @param type CellType to set
     */
    void setCell(int x, int y, CellType type);
    
    /**
     * @brief Check if a position is walkable
     * @param x X coordinate
     * @param y Y coordinate
     * @return True if position is walkable
     */
    bool isWalkable(int x, int y) const;
    
    /**
     * @brief Check if a position is valid (within map bounds)
     * @param x X coordinate
     * @param y Y coordinate
     * @return True if position is valid
     */
    bool isValidPosition(int x, int y) const;
    
    /**
     * @brief Create an explosion at a position
     * @param x X coordinate
     * @param y Y coordinate
     * @param range Explosion range
     */
    void createExplosion(int x, int y, int range);
    
    /**
     * @brief Remove explosion effects from the map
     */
    void clearExplosions();
    
    /**
     * @brief Initialize the map with walls and blocks
     */
    void initialize();

private:
    int width;                          ///< Map width
    int height;                         ///< Map height
    std::vector<std::vector<CellType>> grid;  ///< 2D grid representing the map
    
    /**
     * @brief Check if a position should have a wall
     * @param x X coordinate
     * @param y Y coordinate
     * @return True if position should be a wall
     */
    bool shouldBeWall(int x, int y) const;
};

#endif // MAP_HPP

