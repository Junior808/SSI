#include "../include/Vigenere.hpp"
#include <random>

std::string quitar_espacios(char *entrada, int size)
{
    char *cpy = entrada;
    char *temp = entrada;

    while (*cpy)
    {
        if (*cpy != ' ')
            *temp++ = *cpy;
        cpy++;
    }
    *temp = 0;

    std::string devolver = entrada;

    return devolver;
}

int main()
{
    std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int opcion = 0;

    std::cout << "--------------------------------------------------------\n";
    std::cout << "¿Desea introducir la clave manual o de forma aleatoria?\n";
    std::cout << "[0] Manual\n";
    std::cout << "[1] Aleatoria\n";
    std::cout << "--------------------------------------------------------\n";
    std::cin >> opcion;

    std::string entrada, clave;
    char c_mensaje[500];

    if (opcion == 0)
    {
        std::cout << "Introduzca la clave:\n";
        std::cin >> clave;
    }
    else
    {
        std::random_device rd;
        std::uniform_int_distribution<> distr(0, 26);

        int size = distr(rd);

        for (int i = 0; i < size; i++)
        {
            clave += alfabeto[distr(rd)];
        }
        std::cout << "Clave: " << clave << "\n";
    }

    Vigenere cifrando(clave);

    int operacion = 0;
    bool salir = false;

    while (!salir)
    {
        std::cout << "\n--------------------------\n";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Cifrar mesaje.\n";
        std::cout << "[2] Descifrar mensaje.\n";
        std::cout << "--------------------------\n";
        std::cin >> operacion;

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:

            std::cout << "Introduzca la entrada:\n";
            std::cin.ignore();
            std::cin.getline(c_mensaje, 90);

            entrada = quitar_espacios(c_mensaje, 90);

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