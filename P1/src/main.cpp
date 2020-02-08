#include "../include/Vernam.hpp"

int main()
{
    Vernam cifrando("SOL", "001111000001100001110011");

    cifrando.cifrar();
    cifrando.descifrar();

    cifrando.write();

}