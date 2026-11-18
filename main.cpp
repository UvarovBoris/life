#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

class Life {
    int w_;
    int h_;
    std::vector<std::uint8_t> generation_;
    std::vector<std::uint8_t> nextGeneration_;

    [[nodiscard]] int countAliveNeighbours(const int x, const int y) const {
        return getBorderless(x - 1, y - 1)
               + getBorderless(x, y - 1)
               + getBorderless(x + 1, y - 1)
               + getBorderless(x - 1, y)
               + getBorderless(x + 1, y)
               + getBorderless(x - 1, y + 1)
               + getBorderless(x, y + 1)
               + getBorderless(x + 1, y + 1);
    }


    [[nodiscard]] bool get(const int x, const int y) const {
        return generation_[x + w_ * y];
    }

    [[nodiscard]] bool getBorderless(const int x, const int y) const {
        const int xBorderless = ((x % w_) + w_) % w_;
        const int yBorderless = ((y % h_) + h_) % h_;
        return get(xBorderless, yBorderless);
    }

    void set(const int x, const int y, const bool value) {
        generation_[x + w_ * y] = value;
    }

public:
    Life(const int w, const int h) : w_{w},
                                     h_{h},
                                     generation_(w * h),
                                     nextGeneration_(w * h) {
        set(1, 0, true);
        set(2, 1, true);
        set(0, 2, true);
        set(1, 2, true);
        set(2, 2, true);

        set(19, 10, true);
        set(19, 11, true);
        set(19, 12, true);
    }

    void step() {
        for (int y = 0; y < h_; y++) {
            for (int x = 0; x < w_; x++) {
                const int flatPos = x + w_ * y;
                const bool isAlive = generation_[flatPos];
                const int aliveNeighbour = countAliveNeighbours(x, y);

                if (isAlive) {
                    nextGeneration_[flatPos] = aliveNeighbour == 2 || aliveNeighbour == 3;
                } else {
                    nextGeneration_[flatPos] = aliveNeighbour == 3;
                }
            }
        }
        std::swap(generation_, nextGeneration_);
    }

    friend std::ostream &operator<<(std::ostream &os, const Life &life);
};

std::ostream &operator<<(std::ostream &os, const Life &life) {
    os << "\033[H";

    //top border
    os << std::string(life.w_ + 2, '#') << "\n";

    for (int y = 0; y < life.h_; y++) {
        os << "#";
        for (int x = 0; x < life.w_; x++) {
            os << (life.get(x, y) ? "0" : " ");
        }
        os << "#\n";
    }

    //bottom border
    os << std::string(life.w_ + 2, '#') << "\n";

    return os;
}

int main() {
    Life life{20, 20};
    std::cout << "\033[2J\033[?25l";
    while (true) {
        std::cout << life << std::endl;
        life.step();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
