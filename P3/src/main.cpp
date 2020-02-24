#include "../include/RC4.hpp"
#include <random>
#include <math.h>

std::vector<int> convertir(std::string &entrada)
{
    entrada.push_back(',');
    std::vector<int> salida;

    std::vector<int> temp;
    int resultado = 0;
    int exp = 0;
    for (int i = 0; i < entrada.size(); i++)
    {
        if (entrada[i] != ',')
        {
            temp.push_back(entrada[i] - 48);
        }
        else
        {
            for (int j = temp.size() - 1; j >= 0; j--)
            {
                resultado += temp[j] * pow(10, exp);
                exp++;
            }
            salida.push_back(resultado);
            resultado = 0;
            exp = 0;
            temp.clear();
            temp.resize(0);
        }
    }
    return salida;
}

int main()
{
    std::string clave_;
    std::vector<int> clave;

    int opcion = 0;

    std::cout << "--------------------------------------------------------\n";
    std::cout << "¿Desea introducir la clave manual o de forma aleatoria?\n";
    std::cout << "[0] Manual\n";
    std::cout << "[1] Aleatoria\n";
    std::cout << "--------------------------------------------------------\n";
    std::cin >> opcion;

    if (opcion == 0)
    {
        std::cout << "Introduzca la clave:\n";
        std::cin >> clave_;

        clave = convertir(clave_);
    }
    else
    {
        std::random_device rd;
        std::uniform_int_distribution<> distr1(1, 30);
        std::uniform_int_distribution<> distr2(1, 256);

        int size = distr1(rd);

        for (int i = 0; i < size; i++)
        {
            clave.push_back(distr2(rd));
        }

        std::cout << "Clave aleatoria: \n";
        for (int i = 0; i < clave.size(); i++)
        {
            if (i == clave.size() - 1)
                std::cout << clave[i] << "\n";
            else
                std::cout << clave[i] << ",";
        }
    }

    std::string entrada_;
    std::vector<int> entrada;
    int operacion = 0;
    bool salir = false;

    RC4 cifrado(clave);

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
            std::cin >> entrada_;

            entrada = convertir(entrada_);

            cifrado.cifrar(entrada);

            std::cout << "Mensaje cifrado: \n";
            cifrado.write();

            break;
        case 2:
            std::cout << "Introduzca la entrada cifrada:\n";
            std::cin >> entrada_;

            entrada = convertir(entrada_);

            cifrado.cifrar(entrada);

            std::cout << "Mensaje descifrado: \n";
            cifrado.write();

            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
}