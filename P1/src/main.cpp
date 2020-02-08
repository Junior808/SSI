#include "../include/Vernam.hpp"

int main()
{

    // Vernam cifrando("SOL", "001111000001100001110011");

    std::string entrada, clave;

    std::cout << "Introduzca la clave:\n";
    std::cin >> clave;

    Vernam cifrando(clave);

    int operacion = 0;
    bool salir = false;
    while (!salir)
    {
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Cifrar mesaje.\n";
        std::cout << "[2] Descifrar mensaje.\n";
        std::cin >> operacion;
        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            std::cout << "Introduzca la entrada:\n";
            std::cin >> entrada;

            cifrando.cifrar(entrada);

            std::cout << "Mensaje cifrado: " << cifrando.get_mensaje_cifrado() << "\n";

            break;
        case 2:
            std::cout << "Introduzca la entrada cifrada:\n";
            std::cin >> entrada;

            cifrando.descifrar(entrada);

            std::cout << "Mensaje descifrado: " << cifrando.get_mensaje_descifrado() << "\n";

            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
}