#include "funciones_main.hpp"

int main()
{

    bool salir = false;
    int operacion = 0;
    while (!salir)
    {
        std::cout << "------------------------------------";
        std::cout << "\n¿Qué cifrado desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Vernam.\n";
        std::cout << "[2] Vigenere.\n";
        std::cout << "[3] RC4.\n";
        std::cout << "[4] A5/1.\n";
        std::cout << "[5] E0.\n";
        std::cout << "[6] Multiplicación SNOW 3G y AES.\n";
        std::cout << "[7] Rijndael (AES).\n";
        std::cout << "[8] Modos de cifrado en bloque.\n";
        std::cout << "[9] Diffie-Hellman.\n";
        std::cout << "[10] Fiat-Shamir.\n";
        std::cout << "[11] RSA.\n";
        std::cout << "[12] ElGamal Elíptico.\n";
        std::cout << "Cifrado: ";
        std::cin >> operacion;
        std::cout << "------------------------------------\n";

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            vernam();
            break;
        case 2:
            vigenere();
            break;
        case 3:
            rc4();
            break;
        case 4:
            a5();
            break;
        case 5:
            e0();
            break;
        case 6:
            snow3g_aes();
            break;
        case 7:
            aes();
            break;
        case 8:
            aes_cbc();
            break;
        case 9:
            diffie();
            break;
        case 10:
            fiat();
            break;
        case 11:
            rsa();
            break;
        case 12:
            elgamal();
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
}