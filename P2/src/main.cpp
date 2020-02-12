#include "../include/Vigenere.hpp"

std::string quitar_espacios(char *entrada, int size)
{
    char* cpy = entrada;
    char* temp = entrada;

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

    int opcion = 0;

    std::cout << "¿Desea introducir la clave manual o de forma aleatoria?\n";
    std::cout << "[0] Manual\n";
    std::cout << "[1] Aleatoria\n";
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
        srand(time(NULL));

        for (int i = 0; i < rand() % 17; i++)
        {
            std::cout << "No implementado :)\n";
        }

        std::cout << clave;
    }

    Vigenere cifrando(clave);

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