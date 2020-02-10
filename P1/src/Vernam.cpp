#include "Vernam.hpp"

void Vernam::cifrar(std::string entrada_)
{
    borrar();
    entrada = entrada_;
    convertir_binario(entrada);

    // Se une en un solo string el mensaje en binario.
    std::string final;
    for (int i = 0; i < binario.size(); i++)
    {
        final += binario[i];
    }

    std::bitset<8> clave_;
    std::vector<std::bitset<8>> clave_entera;
    std::istringstream clv(clave);

    // Leo cada 8 bits de la clave.
    for (int i = 0; i < clave.size() / 8; i++)
    {
        clv >> clave_;
        clave_entera.push_back(clave_);
    }

    std::bitset<8> final_;
    std::istringstream fnl(final);

    std::vector<std::bitset<8>> mensaje_entero;
    //Leo cada 8 bits del mensaje en binario.
    for (int i = 0; i < final.size() / 8; i++)
    {
        fnl >> final_;
        mensaje_entero.push_back(final_);
    }

    //Hago la suma XOR entre los 8 bits del mensaje y de la clave.
    for (int i = 0; i < mensaje_entero.size(); i++)
    {
        mensaje_entero[i] ^= clave_entera[i];
    }

    // Junto todo en un solo string.
    for (int i = 0; i < mensaje_entero.size(); i++)
    {
        mensaje_cifrado_binario += mensaje_entero[i].to_string();
    }

    mensaje_cifrado = convertir_binario_string(mensaje_cifrado_binario);
}

void Vernam::descifrar(std::string cifrado_)
{
    borrar();
    entrada = cifrado_;
    mensaje_cifrado = cifrado_;
    convertir_binario(mensaje_cifrado);

    std::string final;

    // Uno en un solo string el mensaje en binario.
    for (int i = 0; i < binario.size(); i++)
    {
        final += binario[i];
    }

    std::bitset<8> clave_;
    std::vector<std::bitset<8>> clave_entera;
    std::istringstream clv(clave);

    // Leo cada 8 bits de la clave.
    for (int i = 0; i < clave.size() / 8; i++)
    {
        clv >> clave_;
        clave_entera.push_back(clave_);
    }

    std::bitset<8> final_;
    std::istringstream fnl(final);

    std::vector<std::bitset<8>> mensaje_entero;
    //Leo cada 8 bits del mensaje en binario.
    for (int i = 0; i < final.size() / 8; i++)
    {
        fnl >> final_;
        mensaje_entero.push_back(final_);
    }

    //Hago la suma XOR entre los 8 bits del mensaje y de la clave.
    for (int i = 0; i < mensaje_entero.size(); i++)
    {
        mensaje_entero[i] ^= clave_entera[i];
    }

    // Junto todo en un solo string.
    for (int i = 0; i < mensaje_entero.size(); i++)
    {
        mensaje_descifrado_binario += mensaje_entero[i].to_string();
    }

    mensaje_descifrado = convertir_binario_string(mensaje_descifrado_binario);
}

void Vernam::write()
{
    std::cout << "Write binario: " << mensaje_cifrado_binario << "\n";
    std::cout << "Write cifrado: " << mensaje_cifrado << "\n";
    std::cout << "Write descifrado: " << mensaje_descifrado << "\n";
}

std::string Vernam::get_mensaje_cifrado()
{
    return mensaje_cifrado;
}

std::string Vernam::get_mensaje_descifrado()
{
    return mensaje_descifrado;
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

void Vernam::borrar()
{
    entrada.clear();
    mensaje_cifrado_binario.clear();
    mensaje_cifrado.clear();
    mensaje_descifrado.clear();
    mensaje_descifrado_binario.clear();
}
