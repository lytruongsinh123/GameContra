
#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "BaseFunction.h"
#include "BaseObject.h"
#define MAX_TILES 20
class TileMat : public BaseObject { // Kế thứa từ BaseObject
public:
	TileMat() { ; }
	~TileMat() { ; }
};
// Kết hợp với TileMat xây dựng map fill toàn bộ tilemat vòa vị trí ô vuông của map
class GameMap {
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES]; // Đối tượng hình ảnh có thể hình ảnh màu xanh , xam, đỏ ....  (DẠNG MAP)..
};
#endif // !GAME_MAP_H
