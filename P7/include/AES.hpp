#pragma once
#include <iostream>
#include <string>
#include <vector>

class AES
{

    std::vector<int> S_Caja;
    std::vector<int> Matriz_MixColumn;

public:
    AES();
    ~AES(){};

    void expandir_clave();

    void addRoundKey();
    void ByteSub();
    void ShiftRow();
    void MixColumn();
};