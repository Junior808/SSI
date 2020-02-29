#include "RC4.hpp"

void RC4::cifrar(std::vector<int> entrada)
{
    reiniciar();
    for (int k = 0; k < entrada.size(); k++)
    {
        std::bitset<8> temp = std::bitset<8>(entrada[k]) ^ std::bitset<8>(prga());

        cifrado.push_back(temp);
    }
}

void RC4::ksa()
{
    i_ = 0, j_ = 0;
    for (int i = 0; i < 256; i++)
    {
        S.push_back(i);
    }

    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + clave[i % clave.size()] + S[i]) % 256;
        swap(i, j);
    }
}

int RC4::prga()
{
    i_ = (i_ + 1) % 256;
    j_ = (j_ + S[i_]) % 256;
    swap(i_, j_);

    int t = (S[i_] + S[j_]) % 256;

    return S[(S[i_] + S[j_]) % 256];
}

void RC4::swap(int i, int j)
{
    int aux = S[i];
    S[i] = S[j];
    S[j] = aux;
}

void RC4::reiniciar()
{
    S.clear();
    cifrado.clear();
    i_ = 0, j_ = 0;
    ksa();
}

void RC4::write()
{
    for (int i = 0; i < cifrado.size(); i++)
    {
        std::cout << cifrado[i].to_ulong() << " (" << cifrado[i] << ")" << std::endl;
    }
}