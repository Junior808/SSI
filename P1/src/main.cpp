#include "../include/Vernam.hpp"

int main()
{

    // Vernam cifrando("SOL", "001111000001100001110011");

    int opcion = 0;

    std::cout << "¿Desea introducir la clave manual o de forma aleatoria?\n";
    std::cout << "[0] Manual\n";
    std::cout << "[1] Aleatoria\n";
    std::cin >> opcion;

    std::string entrada, clave;

    int aleatorio = 0;

    if (opcion == 0)
    {
        std::cout << "Introduzca la clave:\n";
        std::cin >> clave;

        std::cout << "Introduzca la entrada:\n";
        std::cin >> entrada;
    }
    else
    {
        std::cout << "Introduzca la entrada:\n";
        std::cin >> entrada;

        srand(time(NULL));

        for (int i = 0; i < entrada.size(); i++)
        {
            aleatorio = rand() % 64;
            std::bitset<8> clave_bitset(aleatorio);
            clave += clave_bitset.to_string();
        }
    }

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