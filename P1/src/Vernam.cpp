#include "Vernam.hpp"

void Vernam::cifrar()
{
    convertir_binario(entrada);

    // Clave en binario.

    std::string final;

    // Uno en un solo string el mensaje en binario.
    for (int i = 0; i < binario.size(); i++)
    {
        final += binario[i];
    }

    // Hago la suma XOR.
    std::bitset<24> clave_(clave);
    std::bitset<24> mensaje_binario;

    mensaje_binario = std::bitset<24>(final);
    mensaje_binario ^= clave_;

    mensaje_cifrado_binario = mensaje_binario.to_string();

    mensaje_cifrado = convertir_binario_string(mensaje_cifrado_binario);
}

void Vernam::descifrar()
{
    convertir_binario(mensaje_cifrado);

    // Clave en binario.

    std::string final;

    // Uno en un solo string el mensaje en binario.
    for (int i = 0; i < binario.size(); i++)
    {
        final += binario[i];
    }

    // Hago la suma XOR.
    std::bitset<24> clave_(clave);
    std::bitset<24> mensaje_binario;

    mensaje_binario = std::bitset<24>(final);
    mensaje_binario ^= clave_;

    mensaje_descifrado_binario = mensaje_binario.to_string();

    mensaje_descifrado = convertir_binario_string(mensaje_descifrado_binario);
}

void Vernam::write()
{
    std::cout << "Write binario: " << mensaje_cifrado_binario << "\n";
    std::cout << "Write cifrado: " << mensaje_cifrado << "\n";
    std::cout << "Write descifrado: " << mensaje_descifrado << "\n";
}

void Vernam::convertir_binario(std::string entrada_)
{
    std::vector<int> numero;
    binario.clear();
    // Obtengo el caracter en decimal y lo convierto a binario.
    for (int i = 0; i < entrada_.size(); i++)
    {
        numero.push_back(int(entrada_[i]));
        binario.push_back(std::bitset<8>(numero[i]).to_string());
    }
}

std::string Vernam::convertir_binario_string(std::string mensaje_binario)
{
    int tamano = mensaje_binario.size() / entrada.size();

    std::vector<std::string> mensaje;

    std::string caracter;
    for (int i = 0; i < mensaje_binario.size() / tamano; i++)
    {
        for (int j = i * tamano; j < (i + 1) * tamano; j++)
        {
            caracter += mensaje_binario[j];
        }
        mensaje.push_back(caracter);
        caracter.clear();
    }

    std::string mensaje_string;
    for (int i = 0; i < mensaje.size(); i++)
    {
        unsigned long decimal = std::bitset<8>(mensaje[i]).to_ulong();
        mensaje_string.push_back(char(decimal));
    }

    return mensaje_string;
}
