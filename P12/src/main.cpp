#include "ElGamalEliptico.hpp"

int main()
{
    int primo, a, b, x, y, aA, dB, mensaje;

    std::cout << "\nIntroducir número primo p: ";
    std::cin >> primo;
    std::cout << "\nCurva elíptica y^2 = x^3 + ax + b.";
    std::cout << "\nIntroducir valor de a: ";
    std::cin >> a;
    std::cout << "Introducir valor de b: ";
    std::cin >> b;

    ElGamalEliptico cifrado(a, b, primo);

    std::cout << "\nIndique el punto base.\n";
    std::cout << "\t- Indique la coordenada X: ";
    std::cin >> x;
    std::cout << "\t- Indique la coordenada y: ";
    std::cin >> y;

    std::cout << "\nIndique la clave privada aA: ";
    std::cin >> aA;

    std::cout << "Indique la clave privada dB: ";
    std::cin >> dB;

    cifrado.set_claves(aA, dB);

    std::cout << "\nIntroduzca el mensaje a cifrar: ";
    std::cin >> mensaje;

    cifrado.cifrar(mensaje, std::make_pair(x, y));
    cifrado.write();
}