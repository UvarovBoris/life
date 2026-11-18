#include <iostream>

class Life {
    constexpr static int w = 20;
    constexpr static int h = 20;
    bool field[w][h]{};

public:
    Life() {
        field[10][10] = true;
    }

    friend std::ostream &operator<<(std::ostream &os, const Life &life);
};

std::ostream &operator<<(std::ostream &os, const Life &life) {
    //top border
    for (int x = 0; x < life.w + 2; x++) {
        std::cout << "#";
        if (x == life.w + 1) {
            std::cout << "\n";
        }
    }

    for (int y = 0; y < life.h; y++) {
        for (int x = 0; x < life.w; x++) {
            //left border
            if (x == 0) {
                std::cout << "#";
            }

            if (life.field[x][y]) {
                std::cout << "O";
            } else {
                std::cout << " ";
            }

            //right border
            if (x == life.w - 1) {
                std::cout << "#" << "\n";
            }
        }
    }

    //bottom border
    for (int x = 0; x < life.w + 2; x++) {
        std::cout << "#";
    }
    return os;
}

int main() {
    Life life{};
    std::cout << life << std::endl;
    return 0;
}
