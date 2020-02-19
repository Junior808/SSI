#include "../include/RC4.hpp"

int main()
{

    std::vector<int> clave;

    clave.push_back(2);
    clave.push_back(5);

    RC4 cifrado(clave);

    std::vector<int> cifrar;
    std::vector<int> descifrar;

    cifrar.push_back(1);
    cifrar.push_back(34);
    cifrado.cifrar(cifrar);
    // cifrado.write();

    descifrar.push_back(145);
    descifrar.push_back(44);

    cifrado.descifrar(descifrar);
    cifrado.write();

}