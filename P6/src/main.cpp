#include <iostream>
#include <bitset>
#include <sstream>

void suma(std::bitset<8> &byte, int &algoritmo)
{
    if (algoritmo == 1) // SNOW 3G
        byte ^= std::bitset<8>("10101001");
    else // AES
        byte ^= std::bitset<8>("00011011");
}

std::bitset<8> multiplicar(std::bitset<8> primer, std::bitset<8> segundo, int algoritmo)
{
    std::cout << "\n------------------------------------";
    std::cout << "\nPrimer byte: " << primer;
    std::cout << "\nSegundo byte: " << segundo;

    std::bitset<8> resultado = 0;

    if (segundo[0])
        resultado = primer;

    for (int i = 1; i < 8; i++)
    {
        if (primer[7])
        {
            primer <<= 1;
            suma(primer, algoritmo);
        }
        else
            primer <<= 1;

        if (segundo[i])
            resultado ^= primer;
    }
    std::cout << "\nResultado: ";
    return resultado;
}

int main()
{
    bool salir = false;
    int operacion = 0;
    std::string primer_byte, segundo_byte;
    int primer = 0, segundo = 0;

    std::cout << "\n------------------------------------";
    std::cout << "\nPrimer byte (hexadecimal):";
    std::cin >> primer_byte;
    std::cout << "Segundo byte (hexadecimal): ";
    std::cin >> segundo_byte;

    while (!salir)
    {
        std::cout << "------------------------------------";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Multiplicación SNOW 3G.\n";
        std::cout << "[2] Multiplicación AES.\n";
        std::cout << "------------------------------------\n";
        std::cin >> operacion;

        std::istringstream(primer_byte) >> std::hex >> primer;
        std::istringstream(segundo_byte) >> std::hex >> segundo;

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            std::cout << multiplicar(std::bitset<8>(primer), std::bitset<8>(segundo), 1) << std::endl;
            std::cout << "------------------------------------\n";
            break;
        case 2:
            std::cout << multiplicar(std::bitset<8>(primer), std::bitset<8>(segundo), 2) << std::endl;
            std::cout << "------------------------------------\n";
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
    return 0;
}