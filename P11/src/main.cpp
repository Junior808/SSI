#include "RSA.hpp"
#include <string>

std::string quitar_espacios(char *entrada)
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
    RSA A(421, 7, 1619);
    RSA B(2347, 347, 5);

    std::string entrada;
    char c_mensaje[500];

    bool salir = false;
    int operacion = 0;
    while (!salir)
    {
        std::cout << "------------------------------------";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Introducir mensaje A.\n";
        std::cout << "[2] Introducir mensaje B.\n";
        std::cin >> operacion;
        std::cout << "------------------------------------\n";

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            std::cout << "Introduzca el mensaje a cifrar:\n";
            std::cin.ignore();
            std::cin.getline(c_mensaje, 90);

            entrada = quitar_espacios(c_mensaje);

            if (!A.test())
            {
                std::cout << "Los números no son primos.\n";
                return 0;
            }
            else
            {
                A.cifrar(entrada);
                A.write();
            }
            break;
        case 2:
            std::cout << "Introduzca el mensaje a cifrar:\n";
            std::cin.ignore();
            std::cin.getline(c_mensaje, 90);

            entrada = quitar_espacios(c_mensaje);

            if (!B.test())
            {
                std::cout << "Los números no son primos.\n";
                return 0;
            }
            else
            {
                B.cifrar(entrada);
                B.write();
            }
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
}