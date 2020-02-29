#include "A5.hpp"
#include <algorithm>
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
            salida.push_back(resultado - 1);
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
    A5 cifrando;

    std::vector<std::string> semillas;
    std::string aux;

    std::cout << "--------------------------------------------------------\n";
    std::cout << "Introduzca las 3 semillas de los polinomios.\n";
    std::cout << "--------------------------------------------------------\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Semilla[" << i + 1 << "]: ";
        std::cin >> aux;
        std::reverse(aux.begin(), aux.end());
        semillas.push_back(aux);
        aux.clear();
    }

    // std::string s1 = "1001000100011010001";
    // // std::string s2 = "0101100111100010011010";
    // // std::string s3 = "10111100110111100001111";

    // //Los mismos al reves

    // std::string s1 = "1000101100010001001";
    // std::string s2 = "0101100100011110011010";
    // std::string s3 = "11110000111101100111101";
    // semillas = {s1, s2, s3};

    cifrando.insertar_semillas(semillas);

    int pos;
    std::vector<int> pos_mayoria;

    // int a = 9 - 1, b = 11 - 1, c = 11 - 1;
    // pos_mayoria = {a, b, c};

    std::cout << "-------------------------------------------------------------\n";
    std::cout << "Introduzca la posición del bit de control de la fun. mayoría.\n";
    std::cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Polinomio[" << i + 1 << "]: ";
        std::cin >> pos;

        while (pos > semillas[i].size() || pos < 0)
        {
            std::cout << "\n------------------------------------------------\n";
            std::cout << "Ha introducido una posición errónea.\n";
            std::cout << "Tamaño del polinomio[" << i + 1 << "]: " << semillas[i].size() << "\n";
            std::cout << "Posición del bit de control de la fun. mayoría: ";
            std::cin >> pos;
            std::cout << "------------------------------------------------\n";
        }

        pos_mayoria.push_back(pos - 1);
    }

    cifrando.pos_mayoria(pos_mayoria);

    aux.clear();
    std::vector<std::vector<int>> pos_polinomios;
    std::vector<int> aux_pos_polinomios;
    int polinomio = 0;

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "Introduzca las posiciones de los bits de realimentación del polinomio.\n";
    std::cout << "Ejemplo: 19,18,17,14\n";
    std::cout << "----------------------------------------------------------------------\n";
    for (int i = 0; i < 3; i++)
    {
        std::cout << "Polinomio[" << i + 1 << "]: ";
        std::cin >> aux;

        aux_pos_polinomios = convertir(aux);

        for (int i = 0; i < aux_pos_polinomios.size(); i++)
        {
            if (aux_pos_polinomios[i] > semillas[polinomio].size() || pos < 0)
            {
                std::cout << "\nHa introducido una posición errónea: " << aux_pos_polinomios[i] + 1 << "\n";
                std::cout << "Tamaño del polinomio[" << i << "]: " << semillas[i].size() << "\n";
                return 1;
            }
        }

        pos_polinomios.push_back(aux_pos_polinomios);
        polinomio++;
    }

    // std::vector<int> x1 = {19 - 1, 18 - 1, 17 - 1, 14 - 1};
    // std::vector<int> x2 = {22 - 1, 21 - 1};
    // std::vector<int> x3 = {23 - 1, 22 - 1, 21 - 1, 8 - 1};
    // pos_polinomios = {x1, x2, x3};

    cifrando.pos_polinomios(pos_polinomios);

    bool salir = false;
    int operacion = 0, repeticiones = 0;

    while (!salir)
    {
        std::cout << "\n----------------------------------------\n";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Cifrar mesaje.\n";
        std::cout << "[2] Mostrar información de los polinomios.\n";
        std::cout << "------------------------------------------\n";
        std::cin >> operacion;

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            // std::cout << "\n¿Cuántos bits quiere cifrar?\n";
            // std::cin >> repeticiones;

            repeticiones = 6;
            for (int i = 0; i < repeticiones; i++)
            {
                cifrando.cifrar();
            }

            std::cout << "\nZ: " << cifrando.get_Z() << std::endl;
            break;
        case 2:
            cifrando.write();
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
    return 0;
}