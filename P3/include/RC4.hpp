#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <bitset>

class RC4
{
    std::vector<int> clave;
    std::vector<std::bitset<8>> cifrado;

    // std::vector<std::string> S;
    std::vector<int> S;

    int i_ = 0;
    int j_ = 0;

public:
    RC4(std::vector<int> clave_) : clave(clave_) {};
    ~RC4(){};

    void cifrar(std::vector<int> entrada);
    void descifrar(std::vector<int> entrada);

    void write();

private:
    void reiniciar();
    void ksa();
    int prga();
    void swap(int i_, int j_);
};