
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
	GameMap() : game_map_() { ; }
	~GameMap() { ; }
	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map_; };
	void SetMap(Map& map_data) { game_map_ = map_data; };
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES]; // Đối tượng hình ảnh có thể hình ảnh màu xanh , xam, đỏ ....  (DẠNG MAP)..
};
#endif // !GAME_MAP_H

//Cú pháp : game_map_() là một phần của Member Initialization List(Danh sách khởi tạo thành viên) trong C++.
//
//Khi một đối tượng của GameMap được tạo ra, tất cả thành viên của nó(bao gồm game_map_) cũng cần được khởi tạo.
//game_map_() đảm bảo rằng game_map_ được khởi tạo bằng constructor mặc định của lớp hoặc struct mà nó thuộc về.