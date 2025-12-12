#include "../include/Map.hpp"
#include <algorithm>

/**
 * @brief Constructor for Map
 * @param width Width of the map in cells
 * @param height Height of the map in cells
 */
Map::Map(int width, int height) : width(width), height(height) {
    // Initialize grid with empty cells
    grid.resize(height);
    for (int i = 0; i < height; i++) {
        grid[i].resize(width, CellType::EMPTY);
    }
    
    initialize();
}

/**
 * @brief Destructor
 */
Map::~Map() {
}

/**
 * @brief Get the width of the map
 * @return Map width
 */
int Map::getWidth() const {
    return width;
}

/**
 * @brief Get the height of the map
 * @return Map height
 */
int Map::getHeight() const {
    return height;
}

/**
 * @brief Get the cell type at a specific position
 * @param x X coordinate
 * @param y Y coordinate
 * @return CellType at the position
 */
CellType Map::getCell(int x, int y) const {
    if (!isValidPosition(x, y)) {
        return CellType::WALL;
    }
    return grid[y][x];
}

/**
 * @brief Set the cell type at a specific position
 * @param x X coordinate
 * @param y Y coordinate
 * @param type CellType to set
 */
void Map::setCell(int x, int y, CellType type) {
    if (isValidPosition(x, y)) {
        grid[y][x] = type;
    }
}

/**
 * @brief Check if a position is walkable
 * @param x X coordinate
 * @param y Y coordinate
 * @return True if position is walkable
 */
bool Map::isWalkable(int x, int y) const {
    if (!isValidPosition(x, y)) {
        return false;
    }
    
    CellType cell = getCell(x, y);
    return cell == CellType::EMPTY || cell == CellType::EXPLOSION;
}

/**
 * @brief Check if a position is valid (within map bounds)
 * @param x X coordinate
 * @param y Y coordinate
 * @return True if position is valid
 */
bool Map::isValidPosition(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

/**
 * @brief Create an explosion at a position
 * @param x X coordinate
 * @param y Y coordinate
 * @param range Explosion range
 */
void Map::createExplosion(int x, int y, int range) {
    // Center explosion
    if (isValidPosition(x, y)) {
        CellType cell = getCell(x, y);
        if (cell == CellType::BLOCK) {
            setCell(x, y, CellType::EMPTY);
        } else if (cell != CellType::WALL) {
            setCell(x, y, CellType::EXPLOSION);
        }
    }
    
    // Explosion in four directions
    int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    for (int dir = 0; dir < 4; dir++) {
        for (int r = 1; r <= range; r++) {
            int newX = x + directions[dir][0] * r;
            int newY = y + directions[dir][1] * r;
            
            if (!isValidPosition(newX, newY)) {
                break;
            }
            
            CellType cell = getCell(newX, newY);
            
            // Stop explosion at walls
            if (cell == CellType::WALL) {
                break;
            }
            
            // Destroy blocks and create explosion
            if (cell == CellType::BLOCK) {
                setCell(newX, newY, CellType::EMPTY);
                break; // Stop explosion after destroying block
            } else {
                setCell(newX, newY, CellType::EXPLOSION);
            }
        }
    }
}

/**
 * @brief Remove explosion effects from the map
 */
void Map::clearExplosions() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid[y][x] == CellType::EXPLOSION) {
                grid[y][x] = CellType::EMPTY;
            }
        }
    }
}

/**
 * @brief Initialize the map with walls and blocks
 */
void Map::initialize() {
    // Create border walls
    for (int x = 0; x < width; x++) {
        grid[0][x] = CellType::WALL;
        grid[height - 1][x] = CellType::WALL;
    }
    for (int y = 0; y < height; y++) {
        grid[y][0] = CellType::WALL;
        grid[y][width - 1] = CellType::WALL;
    }
    
    // Create internal walls in a grid pattern
    for (int y = 2; y < height - 1; y += 2) {
        for (int x = 2; x < width - 1; x += 2) {
            grid[y][x] = CellType::WALL;
        }
    }
    
    // Place destructible blocks randomly
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            // Don't place blocks on walls or in starting positions
            if (grid[y][x] == CellType::EMPTY && !shouldBeWall(x, y)) {
                // Randomly place blocks (about 30% chance)
                if ((x + y) % 3 == 0 && (x * y) % 5 != 0) {
                    grid[y][x] = CellType::BLOCK;
                }
            }
        }
    }
    
    // Ensure starting positions are clear (corners)
    // Player starting position (top-left)
    grid[1][1] = CellType::EMPTY;
    grid[1][2] = CellType::EMPTY;
    grid[2][1] = CellType::EMPTY;
    
    // Enemy starting positions - clear area around each enemy
    // Top-right enemy (mapWidth - 2, 1)
    int enemy1X = width - 2;
    int enemy1Y = 1;
    for (int dy = -1; dy <= 2; dy++) {
        for (int dx = -2; dx <= 0; dx++) {
            int x = enemy1X + dx;
            int y = enemy1Y + dy;
            if (isValidPosition(x, y) && grid[y][x] != CellType::WALL) {
                grid[y][x] = CellType::EMPTY;
            }
        }
    }
    
    // Bottom-left enemy (1, mapHeight - 2)
    int enemy2X = 1;
    int enemy2Y = height - 2;
    for (int dy = -2; dy <= 0; dy++) {
        for (int dx = -1; dx <= 2; dx++) {
            int x = enemy2X + dx;
            int y = enemy2Y + dy;
            if (isValidPosition(x, y) && grid[y][x] != CellType::WALL) {
                grid[y][x] = CellType::EMPTY;
            }
        }
    }
    
    // Bottom-right enemy (mapWidth - 2, mapHeight - 2)
    int enemy3X = width - 2;
    int enemy3Y = height - 2;
    for (int dy = -2; dy <= 0; dy++) {
        for (int dx = -2; dx <= 0; dx++) {
            int x = enemy3X + dx;
            int y = enemy3Y + dy;
            if (isValidPosition(x, y) && grid[y][x] != CellType::WALL) {
                grid[y][x] = CellType::EMPTY;
            }
        }
    }
}

/**
 * @brief Check if a position should have a wall
 * @param x X coordinate
 * @param y Y coordinate
 * @return True if position should be a wall
 */
bool Map::shouldBeWall(int x, int y) const {
    // Starting positions (corners) should not have walls
    // Player starting area (top-left)
    if ((x == 1 && y == 1) || (x == 1 && y == 2) || (x == 2 && y == 1)) {
        return false;
    }
    
    // Enemy starting areas - expanded zones
    // Top-right enemy area
    if (x >= width - 4 && x <= width - 2 && y >= 0 && y <= 3) {
        return false;
    }
    
    // Bottom-left enemy area
    if (x >= 0 && x <= 3 && y >= height - 4 && y <= height - 2) {
        return false;
    }
    
    // Bottom-right enemy area
    if (x >= width - 4 && x <= width - 2 && y >= height - 4 && y <= height - 2) {
        return false;
    }
    
    return false;
}

