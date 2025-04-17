#include "RankingManager.h"
#include "TextObject.h"

RankingManager::RankingManager(const std::string& file_path) {
    // Khởi tạo đường dẫn tệp và tải dữ liệu xếp hạng từ tệp
    file_path_ = file_path;
    LoadRanking();
}

void RankingManager::LoadRanking() {
    // Xóa danh sách xếp hạng hiện tại
    ranking_.clear();
    // Mở tệp xếp hạng để đọc
    std::ifstream file(file_path_);
    if (!file.is_open()) return;  // Nếu không thể mở tệp, thoát hàm

    std::string name;
    int score;
    // Đọc dữ liệu từ tệp: tên người chơi và điểm số
    while (file >> name >> score) {
        // Thêm điểm và tên vào danh sách xếp hạng
        ranking_.push_back({ name, score });
    }

    // Đóng tệp sau khi đọc xong
    file.close();
}

void RankingManager::SaveRanking() {
    // Mở tệp để ghi dữ liệu
    std::ofstream file(file_path_);
    if (!file.is_open()) return;  // Nếu không thể mở tệp, thoát hàm

    // Ghi lại tên và điểm của từng người chơi vào tệp
    for (const auto& ps : ranking_) {
        file << ps.name << " " << ps.score << "\n";
    }

    // Đóng tệp sau khi ghi xong
    file.close();
}

void RankingManager::AddScore(const PlayerScore& ps) {
    // Thêm điểm của người chơi vào danh sách xếp hạng
    ranking_.push_back(ps);
    // Sắp xếp xếp hạng theo điểm số giảm dần
    std::sort(ranking_.begin(), ranking_.end(), [](const PlayerScore& a, const PlayerScore& b) {
        return a.score > b.score;
        });
    // Giới hạn danh sách xếp hạng chỉ giữ lại top 5
    if (ranking_.size() > 5) ranking_.resize(5);
}

void RankingManager::RenderRanking(SDL_Renderer* screen, TTF_Font* font) {
    // Tạo đối tượng văn bản để hiển thị tiêu đề "BANG XEP HANG"
    TextObject title;
    title.SetText("BANG XEP HANG");
    title.SetColor(TextObject::WHITE_TEXT);  // Màu trắng cho tiêu đề
    title.LoadFromRenderText(font, screen);  // Tải văn bản từ font
    title.RenderText(screen, 250, 100);  // Vẽ tiêu đề tại vị trí (250, 100)

    // Duyệt qua tất cả các điểm xếp hạng và hiển thị tên người chơi và điểm số
    for (size_t i = 0; i < ranking_.size(); ++i) {
        // Tạo chuỗi chứa số thứ tự, tên người chơi và điểm số
        std::string line = std::to_string(i + 1) + ". " + ranking_[i].name + ": " + std::to_string(ranking_[i].score);
        TextObject lineText;
        lineText.SetText(line);  // Cài đặt chuỗi văn bản
        lineText.SetColor(TextObject::WHITE_TEXT);  // Màu trắng cho dòng xếp hạng
        lineText.LoadFromRenderText(font, screen);  // Tải văn bản từ font
        lineText.RenderText(screen, 250, 150 + i * 40);  // Vẽ dòng xếp hạng tại vị trí phù hợp
    }
}
