#include "A5.hpp"

int main()
{
    // std::string s1 = "1001000100011010001";
    // std::string s2 = "0101100111100010011010";
    // std::string s3 = "10111100110111100001111";

    //Los mismos al reves
    std::string s1 = "1000101100010001001";
    std::string s2 = "0101100100011110011010";
    std::string s3 = "11110000111101100111101";

    A5 cifrando;

    cifrando.insertar_semillas(s1, s2, s3);

    int a = 9 - 1, b = 11 - 1, c = 11 - 1;

    cifrando.pos_mayoria(a, b, c);

    std::vector<int> x1 = {19 - 1, 18 - 1, 17 - 1, 14 - 1};
    std::vector<int> x2 = {22 - 1, 21 - 1};
    std::vector<int> x3 = {23 - 1, 22 - 1, 21 - 1, 8 - 1};

    cifrando.pos_polinomios(x1, x2, x3);

    // cifrando.write();
    for (int i = 0; i < 6; i++)
    {
        cifrando.cifrar();
    }
    std::cout << "\nZ: " << cifrando.get_Z() << std::endl;
}