#include <spdlog/spdlog.h>

int main() {
    spdlog::info("Это информационное сообщение");
    spdlog::warn("Это предупреждение");
    spdlog::error("Ошибка: {} + {} = {}", 1, 2, 1+2);
}