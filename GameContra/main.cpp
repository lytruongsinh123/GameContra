#include <SDL.h>
#include <vector>
#include <ctime>
#include<SDL_image.h>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int CELL_SIZE = 20;

struct Point {
    int x, y;
};

class SnakeGame {
public:
    SnakeGame() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        running = true;
        direction = { 1, 0 };
        snake.push_back({ 10, 10 });
        spawnFood();
    }

    ~SnakeGame() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void run() {
        while (running) {
            handleEvents();
            update();
            render();
            SDL_Delay(100);
        }
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    std::vector<Point> snake;
    Point direction;
    Point food;

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP: if (direction.y == 0) direction = { 0, -1 }; break;
                case SDLK_DOWN: if (direction.y == 0) direction = { 0, 1 }; break;
                case SDLK_LEFT: if (direction.x == 0) direction = { -1, 0 }; break;
                case SDLK_RIGHT: if (direction.x == 0) direction = { 1, 0 }; break;
                }
            }
        }
    }

    void update() {
        Point newHead = { snake[0].x + direction.x, snake[0].y + direction.y };

        if (newHead.x < 0 || newHead.y < 0 || newHead.x >= SCREEN_WIDTH / CELL_SIZE || newHead.y >= SCREEN_HEIGHT / CELL_SIZE) {
            running = false;
            return;
        }

        for (const auto& segment : snake) {
            if (newHead.x == segment.x && newHead.y == segment.y) {
                running = false;
                return;
            }
        }

        snake.insert(snake.begin(), newHead);
        if (newHead.x == food.x && newHead.y == food.y) {
            spawnFood();
        }
        else {
            snake.pop_back();
        }
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (const auto& segment : snake) {
            SDL_Rect rect = { segment.x * CELL_SIZE, segment.y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect foodRect = { food.x * CELL_SIZE, food.y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        SDL_RenderFillRect(renderer, &foodRect);

        SDL_RenderPresent(renderer);
    }

    void spawnFood() {
        srand(time(0));
        food = { rand() % (SCREEN_WIDTH / CELL_SIZE), rand() % (SCREEN_HEIGHT / CELL_SIZE) };
    }
};

int main(int argc, char* argv[]) {
    
    SnakeGame game;
    game.run();
    return 0;
}
