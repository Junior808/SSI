#include "Vernam.hpp"
#include "Vigenere.hpp"
#include "RC4.hpp"
#include "A5.hpp"
#include "E0.hpp"
#include "AES.hpp"
#include "AES_CBC.hpp"
#include "RSA.hpp"

#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <math.h>
#include <bitset>
#include <sstream>
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

void pre_cifrar(std::vector<std::vector<int>> &texto, std::vector<std::vector<int>> &ivector)
{
    for (int i = 0; i < texto.size(); i++)
        for (int j = 0; j < texto[i].size(); j++)
            texto[i][j] = texto[i][j] ^ ivector[i][j];
}

void cipher_stealing(int robar, std::vector<std::vector<int>> &texto_robado, std::vector<std::vector<int>> &texto_aumentado)
{
    int size_robado = 0, size_i_robado = 0;
    for (int k = 0; k < robar; k++)
    {
        size_robado = texto_robado.size() - 1;
        size_i_robado = texto_robado[size_robado][texto_robado[size_robado].size() - 1];

        texto_aumentado[texto_aumentado.size() - 1].push_back(size_i_robado);
        texto_robado[texto_robado.size() - 1].pop_back();
    }
}

int pow(int base, int exponente, int primo)
{
    int resultado = 1, y = base % primo;

    while ((exponente > 0) && (y > 1))
    {
        if (exponente % 2) // Impar
        {
            resultado = (resultado * y) % primo;
            exponente--;
        }
        else
        {
            y = (y * y) % primo;
            exponente /= 2;
        }
    }

    return resultado;
}

void vernam()
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

void vigenere()
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

            entrada = quitar_espacios(c_mensaje);

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

void rc4()
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

void a5()
{
    A5 cifrando;

    std::vector<std::string> semillas;
    std::string aux;

    // //Los mismos al reves

    std::string s1 = "1000101100010001001";
    std::string s2 = "0101100100011110011010";
    std::string s3 = "11110000111101100111101";
    semillas = {s1, s2, s3};

    cifrando.insertar_semillas(semillas);

    int pos;
    std::vector<int> pos_mayoria;

    int a = 9 - 1, b = 11 - 1, c = 11 - 1;
    pos_mayoria = {a, b, c};

    cifrando.pos_mayoria(pos_mayoria);

    aux.clear();
    std::vector<std::vector<int>> pos_polinomios;
    std::vector<int> aux_pos_polinomios;
    int polinomio = 0;

    std::vector<int> x1 = {19 - 1, 18 - 1, 17 - 1, 14 - 1};
    std::vector<int> x2 = {22 - 1, 21 - 1};
    std::vector<int> x3 = {23 - 1, 22 - 1, 21 - 1, 8 - 1};
    pos_polinomios = {x1, x2, x3};

    cifrando.pos_polinomios(pos_polinomios);

    bool salir = false;
    int operacion = 0, repeticiones = 0;

    while (!salir)
    {
        std::cout << "\n----------------------------------------\n";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Generar secuencia.\n";
        std::cout << "[2] Mostrar información de los polinomios.\n";
        std::cout << "------------------------------------------\n";
        std::cin >> operacion;

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            repeticiones = 6;
            for (int i = 0; i < repeticiones; i++)
            {
                cifrando.cifrar();
                cifrando.write();
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
}

void e0()
{
    std::string lfsr1 = "0101010101010101010101111";
    std::string lfsr2 = "0101010101010101010101010101111";
    std::string lfsr3 = "010101010101010101010101010101111";
    std::string lfsr4 = "010101010101010101010101010101010101010";

    std::string r1 = "01";

    std::vector<std::string> semilas = {lfsr1, lfsr2, lfsr3, lfsr4, r1};

    E0 generador(semilas);

    bool salir = false;
    int operacion = 0;

    while (!salir)
    {
        std::cout << "\n------------------------------------";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Generar secuencia.\n";
        std::cout << "[2] Mostrar información de los LFSR.\n";
        std::cout << "------------------------------------\n";
        std::cin >> operacion;

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            for (int i = 0; i < 4; i++)
            {
                generador.write();
                generador.generar();
            }

            std::cout << "\nZ: " << generador.get_Z() << std::endl;
            break;
        case 2:
            generador.write();
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
}

void snow3g_aes()
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
}

void aes()
{
    //  Clave y texto por defecto (PDF)
    std::vector<std::vector<int>> clave_;
    std::vector<std::vector<int>> texto_;

    clave_ = {
        {0x00, 0x04, 0x08, 0x0c},
        {0x01, 0x05, 0x09, 0x0d},
        {0x02, 0x06, 0x0a, 0x0e},
        {0x03, 0x07, 0x0b, 0x0f}};

    texto_ = {
        {0x00, 0x44, 0x88, 0xcc},
        {0x11, 0x55, 0x99, 0xdd},
        {0x22, 0x66, 0xaa, 0xee},
        {0x33, 0x77, 0xbb, 0xff}};

    //   ------------------------------------

    //  Clave y texto pedir por teclado.
    std::vector<std::vector<int>> clave;
    std::vector<std::vector<int>> texto;

    for (int i = 0; i < 4; i++)
    {
        clave.resize(4);
        texto.resize(4);
        for (int j = 0; j < 4; j++)
        {
            clave[i].resize(4);
            texto[i].resize(4);
        }
    }

    //   ------------------------------------

    AES cifrado;
    bool salir = false;
    int operacion = 0;
    std::string entrada;
    while (!salir)
    {
        std::cout << "------------------------------------";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Valores por defecto.\n";
        std::cout << "[2] Introducir valores.\n";
        std::cin >> operacion;
        std::cout << "------------------------------------\n";

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:

            std::cout << "Clave: ";
            for (int j = 0; j < clave_.size(); j++)
                for (int i = 0; i < clave_[j].size(); i++)
                    std::cout << std::hex << clave_[i][j];

            std::cout << "\nBloque de texto: ";
            for (int j = 0; j < texto_.size(); j++)
                for (int i = 0; i < texto_[j].size(); i++)
                    std::cout << std::hex << texto_[i][j];

            cifrado.introducir_datos(clave_, texto_);
            cifrado.cifrar();
            cifrado.write();
            break;
        case 2:
            std::cout << "------------------------------------";
            std::cout << "\nIntroduzca la clave:\n";
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    std::cin >> entrada;
                    std::istringstream(entrada) >> std::hex >> clave[i][j];
                }
            }
            std::cout << "------------------------------------";
            std::cout << "\nIntroduzca el texto:\n";
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    std::cin >> entrada;
                    std::istringstream(entrada) >> std::hex >> texto[i][j];
                }
            }
            std::cout << "------------------------------------";

            cifrado.introducir_datos(clave, texto);
            cifrado.cifrar();
            cifrado.write();
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
}

void aes_cbc()
{
    //  Clave y texto por defecto (PDF)
    std::vector<std::vector<int>> clave_;
    std::vector<std::vector<int>> ivector_;
    std::vector<std::vector<int>> texto1_;
    std::vector<std::vector<int>> texto2_;
    std::vector<std::vector<int>> texto3_;

    int size_t1 = 0, size_t3 = 0, robar;

    std::vector<std::vector<int>> resultado1;
    std::vector<std::vector<int>> resultado2;

    clave_ = {
        {0x00, 0x04, 0x08, 0x0c},
        {0x01, 0x05, 0x09, 0x0d},
        {0x02, 0x06, 0x0a, 0x0e},
        {0x03, 0x07, 0x0b, 0x0f}};

    ivector_ = {
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00}};

    texto1_ = {
        {0x00, 0x44, 0x88, 0xcc},
        {0x11, 0x55, 0x99, 0xdd},
        {0x22, 0x66, 0xaa, 0xee},
        {0x33, 0x77, 0xbb, 0xff}};

    texto2_ = {
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00}};

    texto3_ = {
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00}};

    //   ------------------------------------

    AES_CBC cifrado;
    bool salir = false;
    int operacion = 0;
    std::string entrada;
    while (!salir)
    {
        std::cout << "------------------------------------";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Valores por defecto CBC.\n";
        std::cout << "[2] Valores por defecto Cipher Stealing.\n";
        std::cin >> operacion;
        std::cout << "------------------------------------\n";

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:

            std::cout << "Clave: ";
            for (int j = 0; j < clave_.size(); j++)
                for (int i = 0; i < clave_[j].size(); i++)
                    std::cout << std::hex << clave_[i][j];

            std::cout << "\nIV: ";
            for (int j = 0; j < ivector_.size(); j++)
                for (int i = 0; i < ivector_[j].size(); i++)
                    std::cout << std::hex << ivector_[i][j];

            std::cout << "\nBloque de texto 1: ";
            for (int j = 0; j < texto1_.size(); j++)
                for (int i = 0; i < texto1_[j].size(); i++)
                    std::cout << std::hex << texto1_[i][j];

            std::cout << "\nBloque de texto 2: ";
            for (int j = 0; j < texto2_.size(); j++)
                for (int i = 0; i < texto2_[j].size(); i++)
                    std::cout << std::hex << texto2_[i][j];

            pre_cifrar(texto1_, ivector_);
            cifrado.introducir_datos(clave_, texto1_);
            ivector_ = cifrado.cifrar();
            cifrado.write();

            pre_cifrar(texto2_, ivector_);
            cifrado.entrada_nueva(texto2_);
            ivector_ = cifrado.cifrar();
            cifrado.write();
            break;

        case 2:

            ivector_ = {
                {0x00, 0x00, 0x00, 0x00},
                {0x00, 0x00, 0x00, 0x00},
                {0x00, 0x00, 0x00, 0x00},
                {0x00, 0x00, 0x00, 0x00}};

            std::cout << "Clave: ";
            for (int j = 0; j < clave_.size(); j++)
                for (int i = 0; i < clave_[j].size(); i++)
                    std::cout << std::hex << clave_[i][j];

            std::cout << "\nIV: ";
            for (int j = 0; j < ivector_.size(); j++)
                for (int i = 0; i < ivector_[j].size(); i++)
                    std::cout << std::hex << ivector_[i][j];

            std::cout << "\nBloque de texto 1: ";
            for (int j = 0; j < texto1_.size(); j++)
                for (int i = 0; i < texto1_[j].size(); i++)
                {
                    std::cout << std::hex << texto1_[i][j];
                    size_t1++;
                }

            std::cout << "\nBloque de texto 2: ";
            for (int j = 0; j < texto3_.size(); j++)
                for (int i = 0; i < texto3_[j].size(); i++)
                {
                    std::cout << std::hex << texto3_[i][j];
                    size_t3++;
                }

            robar = size_t1 - size_t3;

            pre_cifrar(texto1_, ivector_);
            cifrado.introducir_datos(clave_, texto1_);
            resultado1 = cifrado.cifrar();

            pre_cifrar(texto3_, resultado1);
            cipher_stealing(robar, resultado1, texto3_);
            cifrado.entrada_nueva(texto3_);
            resultado2 = cifrado.cifrar();

            std::cout << "Bloque 1 cifrado: ";
            for (int j = 0; j < resultado2.size(); j++)
                for (int i = 0; i < resultado2[j].size(); i++)
                    std::cout << std::hex << resultado2[i][j];

            std::cout << "\nBloque 2 cifrado: ";
            for (int j = 0; j < resultado1.size(); j++)
                for (int i = 0; i < resultado1[j].size(); i++)
                    std::cout << std::hex << resultado1[i][j];

            std::cout << "\n";

            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
}

void diffie_hellman(int p, int a, int x_a, int x_b)
{
    int y_a, y_b;

    std::cout << "------------------Canal público------------------\n";
    std::cout << "Número primo: " << p;
    std::cout << "\nAlfa: " << a;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Número secreto: " << x_a;
    y_a = pow(a, x_a, p);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------B------------------\n";
    std::cout << "Número secreto: " << x_b;
    y_b = pow(a, x_b, p);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------Canal público------------------\n";
    std::cout << "[A] - Me da " << y_a;
    std::cout << "\n[B] - A mi " << y_b;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Entonces K vale " << pow(y_b, x_a, p);
    std::cout << "\n-------------------------------------\n";

    std::cout << "------------------B------------------\n";
    std::cout << "Entonces K vale " << pow(y_a, x_b, p);
    std::cout << "\n-------------------------------------\n";
}

void diffie()
{
    diffie_hellman(13, 4, 5, 2);
    diffie_hellman(43, 23, 25, 33);
    diffie_hellman(113, 43, 54, 71);
}

void fiat_shamir(int p, int q, int s, int x_1, int x_2, int bit_e, int iteraciones)
{

    int n = p * q;

    std::cout << "------------------Canal público------------------\n";
    std::cout << "N: " << n;
    std::cout << "\n-------------------------------------------------\n";

    std::cout << "------------------A------------------\n";
    std::cout << "Número secreto S: " << s;
    std::cout << "\n-------------------------------------\n";

    unsigned long int v = (s * s) % n;

    std::cout << "------------------Canal público------------------\n";
    std::cout << "[A] - V vale " << v;
    std::cout << "\n-------------------------------------------------\n";

    unsigned long int y, x = x_1;
    for (int i = 0; i < iteraciones; i++)
    {
        std::cout << "------------------Iteración " << i << "------------------\n";

        std::cout << "------------------A------------------\n";
        std::cout << "Número secreto X: " << x;
        std::cout << "\n-------------------------------------\n";

        unsigned long int a = (x * x) % n;
        std::cout << "------------------Canal público------------------\n";
        std::cout << "[A] - A vale " << a;
        std::cout << "\n[B] - Pues calcula con esto: " << bit_e;
        std::cout << "\n-------------------------------------------------\n";

        if (bit_e == 0)
        {
            y = x % n;
            std::cout << "------------------Canal público------------------\n";
            std::cout << "[A] - Me da esto: " << y;
            std::cout << "\n-------------------------------------------------\n";

            std::cout << "------------------B------------------\n";
            std::cout << "Y^2 (mod N) = " << (y * y) % n << " debería coincidir con A (mod N) = " << a;
            std::cout << ".\n-------------------------------------\n";

            if (((y * y) % n) == a)
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡Correcto!";
                std::cout << "\n-------------------------------------------------\n";
            }
            else
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡ERROR!";
                std::cout << "\n-------------------------------------------------\n";
            }
        }
        else
        {
            y = (x * s) % n;
            std::cout << "------------------Canal público------------------\n";
            std::cout << "[A]: - Me da esto: " << y;
            std::cout << "\n-------------------------------------------------\n";

            std::cout << "------------------B------------------\n";
            std::cout << "Y^2 (mod N) = " << (y * y) % n << " debería coincidir con A*V (mod N) = " << (a * v) % n;
            std::cout << ".\n-------------------------------------\n";

            if (((y * y) % n) == (a * v) % n)
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡Correcto!";
                std::cout << "\n-------------------------------------------------\n";
            }
            else
            {
                std::cout << "------------------Canal público------------------\n";
                std::cout << "[B]: ¡ERROR!";
                std::cout << "\n-------------------------------------------------\n";
            }
        }
        x = x_2;
        bit_e++;
    }
}

void fiat()
{
    fiat_shamir(7, 5, 3, 16, 2, 0, 2);
    fiat_shamir(683, 811, 43215, 16785, 2, 1, 1);
}

void rsa()
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
                return;
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
                return;
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

int main()
{
}