#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class Vigenere
{
    std::string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string clave;
    std::string cifrado;
    std::string descifrado;

public:
    Vigenere(std::string clave_) : clave(clave_) { minusculas(clave); };
    ~Vigenere(){};

    void cifrar(std::string entrada);
    void descifrar(std::string entrada);

    std::string get_mensaje_cifrado() { return cifrado; };
    std::string get_mensaje_descifrado() { return descifrado; };

private:
    void minusculas(std::string &entrada); //Función que comprueba si el mensaje está en minúscula y lo pasa a mayúscula.
    void borrar();
};