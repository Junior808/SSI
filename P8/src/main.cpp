#include "AES.hpp"
#include <sstream>

void pre_cifrar(std::vector<std::vector<int>> &texto, std::vector<std::vector<int>> &ivector)
{
    for (int i = 0; i < texto.size(); i++)
        for (int j = 0; j < texto[i].size(); j++)
            texto[i][j] = texto[i][j] ^ ivector[i][j];
}

void cipher_stealing(int robar, std::vector<std::vector<int>> &texto_robado, std::vector<std::vector<int>> &texto_aumentado)
{
    std::vector<int> robando;
    int size_robado = 0, size_i_robado = 0;
    for (int k = 0; k < robar; k++)
    {
        size_robado = texto_robado.size() - 1;
        size_i_robado = texto_robado[size_robado][texto_robado[size_robado].size() - 1];

        texto_aumentado[texto_aumentado.size() - 1].push_back(size_i_robado);
        texto_robado[texto_robado.size() - 1].pop_back();
    }
}

int main()
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

    AES cifrado;
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
    return 0;
}