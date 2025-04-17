#include "Menu.h"

Menu::Menu() {}
Menu::~Menu() {}

bool Menu::Init(SDL_Renderer* renderer) {
    // Tải hình nền cho menu
    return background_.LoadImg("img//menu_background.png", renderer);
}

int Menu::ShowMenu(SDL_Renderer* renderer, TTF_Font* /*font*/) {
    bool quit = false; // Biến dùng để thoát khỏi vòng lặp menu
    SDL_Event event;   // Biến để xử lý sự kiện

    // Tải các font chữ bình thường và phóng to
    TTF_Font* font_normal = TTF_OpenFont("font//dlxfont.ttf", 36);   // Font bình thường
    TTF_Font* font_hover = TTF_OpenFont("font//dlxfont.ttf", 48);    // Font phóng to khi hover
    if (!font_normal || !font_hover) {
        // Nếu không tải được font, in thông báo lỗi và trả về -1
        printf("Failed to load fonts: %s\n", TTF_GetError());
        return -1;
    }

    bool hover_start = false; // Biến kiểm tra có hover trên nút "Start" không
    bool hover_exit = false;  // Biến kiểm tra có hover trên nút "Exit" không

    // Khởi tạo vị trí mặc định cho các nút "Start" và "Exit"
    SDL_Rect start_rect = { 0, 0, 0, 0 };  // Vị trí ban đầu của nút Start
    SDL_Rect exit_rect = { 0, 0, 0, 0 };   // Vị trí ban đầu của nút Exit

    while (!quit) {
        int x, y;
        SDL_GetMouseState(&x, &y); // Lấy vị trí chuột hiện tại

        // Tạo đối tượng văn bản cho các nút "Start" và "Exit"
        TextObject start_text;
        TextObject exit_text;

        // Kiểm tra xem chuột có ở trên nút "Start" không
        hover_start = (x >= start_rect.x && x <= start_rect.x + start_rect.w &&
            y >= start_rect.y && y <= start_rect.y + start_rect.h);
        start_text.SetText("Start");   // Cài đặt nội dung cho nút "Start"
        start_text.SetColor(TextObject::WHITE_TEXT);  // Cài đặt màu sắc cho văn bản
        start_text.LoadFromRenderText(hover_start ? font_hover : font_normal, renderer);  // Chọn font dựa vào trạng thái hover

        // Cập nhật vị trí và kích thước cho nút "Start"
        start_rect = {
            SCREEN_WIDTH / 2 - start_text.GetWidth() / 2,  // Căn giữa màn hình
            SCREEN_HEIGHT / 2 + 100,                        // Vị trí y của nút "Start"
            start_text.GetWidth(),                         // Chiều rộng của nút "Start"
            start_text.GetHeight()                         // Chiều cao của nút "Start"
        };

        // Kiểm tra xem chuột có ở trên nút "Exit" không
        hover_exit = (x >= exit_rect.x && x <= exit_rect.x + exit_rect.w &&
            y >= exit_rect.y && y <= exit_rect.y + exit_rect.h);
        exit_text.SetText("Exit");    // Cài đặt nội dung cho nút "Exit"
        exit_text.SetColor(TextObject::WHITE_TEXT);  // Cài đặt màu sắc cho văn bản
        exit_text.LoadFromRenderText(hover_exit ? font_hover : font_normal, renderer);  // Chọn font dựa vào trạng thái hover

        // Cập nhật vị trí và kích thước cho nút "Exit"
        exit_rect = {
            SCREEN_WIDTH / 2 - exit_text.GetWidth() / 2,  // Căn giữa màn hình
            SCREEN_HEIGHT / 2 + 200,                        // Vị trí y của nút "Exit"
            exit_text.GetWidth(),                          // Chiều rộng của nút "Exit"
            exit_text.GetHeight()                          // Chiều cao của nút "Exit"
        };

        // Vòng lặp xử lý sự kiện
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                // Nếu người dùng đóng cửa sổ, thoát và đóng font
                TTF_CloseFont(font_normal);
                TTF_CloseFont(font_hover);
                return -1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Nếu nhấn chuột vào nút "Start"
                if (hover_start) {
                    TTF_CloseFont(font_normal);
                    TTF_CloseFont(font_hover);
                    return 1;  // Trở về giá trị 1, để bắt đầu trò chơi
                }
                // Nếu nhấn chuột vào nút "Exit"
                if (hover_exit) {
                    TTF_CloseFont(font_normal);
                    TTF_CloseFont(font_hover);
                    return 0;  // Trở về giá trị 0, để thoát trò chơi
                }
            }
        }

        // Vẽ lại hình nền và các nút sau mỗi khung hình
        background_.Render(renderer, NULL);
        start_text.RenderText(renderer, start_rect.x, start_rect.y);
        exit_text.RenderText(renderer, exit_rect.x, exit_rect.y);

        // Cập nhật màn hình
        SDL_RenderPresent(renderer);
    }

    // Đóng font khi thoát khỏi vòng lặp
    TTF_CloseFont(font_normal);
    TTF_CloseFont(font_hover);
    return -1;  // Nếu không chọn nút nào, trả về -1
}
