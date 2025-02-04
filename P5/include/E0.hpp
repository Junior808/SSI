#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>

class E0
{
    std::bitset<25> LFSR1;
    std::bitset<31> LFSR2;
    std::bitset<33> LFSR3;
    std::bitset<39> LFSR4;

    std::bitset<2> R1;
    std::bitset<2> R2;

    std::string Z;

public:
    E0(std::vector<std::string> semillas);
    ~E0(){};

    void generar();

    void write();
    std::string get_Z() { return Z; };

private:
    void realimentacion();
};