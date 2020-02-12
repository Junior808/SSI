#include "Vigenere.hpp"

void Vigenere::cifrar(std::string entrada)
{
    minusculas(entrada);
    int pos_clave = 0, pos_mensaje = 0, pos_alfabeto = 0;

    for (int i = 0; i < entrada.size(); i++)
    {
        pos_clave = clave[i % clave.size()] - 65;
        pos_mensaje = entrada[i] - 65;
        pos_alfabeto = (pos_clave + pos_mensaje) % alfabeto.size();

        cifrado += alfabeto[pos_alfabeto];
    }
}

void Vigenere::descifrar(std::string entrada)
{
    minusculas(entrada);
    int pos_clave = 0, pos_mensaje = 0, pos_alfabeto = 0;

    for (int i = 0; i < entrada.size(); i++)
    {
        pos_clave = clave[i % clave.size()] - 65;
        pos_mensaje = entrada[i] - 65;

        if ((pos_mensaje - pos_clave) >= 0)
        {
            pos_alfabeto = (pos_mensaje - pos_clave) % alfabeto.size();
        }
        else
        {
            pos_alfabeto = (pos_mensaje - pos_clave + alfabeto.size()) % alfabeto.size();
        }

        descifrado += alfabeto[pos_alfabeto];
    }
}

void Vigenere::minusculas(std::string &entrada)
{
    for (int i = 0; i < entrada.size(); i++)
    {
        if (islower(entrada[i]))
        {
            entrada[i] = entrada[i] - 32;
        }
    }
}

void Vigenere::expandir_clave(std::string entrada)
{
    int div = entrada.size() / clave.size();
    int resto = entrada.size() % clave.size();
}
