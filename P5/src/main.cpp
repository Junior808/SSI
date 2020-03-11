#include "E0.hpp"

int main()
{
    std::string lfsr1 = "0101010101010101010101011";
    std::string lfsr2 = "0101010101010101010101010101011";
    std::string lfsr3 = "010101010101010101010101010101011";
    std::string lfsr4 = "010101010101010101010101010101010101011";

    std::string r1 = "01";

    std::vector<std::string> semilas = {lfsr1, lfsr2, lfsr3, lfsr4, r1};

    std::vector<int> x1 = {7, 11, 19, 24};
    std::vector<int> x2 = {11, 15, 23, 30};
    std::vector<int> x3 = {3, 23, 27, 32};
    std::vector<int> x4 = {3, 27, 35, 38};
    std::vector<std::vector<int>> posiciones = {x1, x2, x3, x4};
}