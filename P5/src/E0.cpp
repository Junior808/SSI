#include "E0.hpp"

E0::E0(std::vector<std::string> semillas)
{
    LFSR1 = std::bitset<25>(semillas[0]);
    LFSR2 = std::bitset<31>(semillas[1]);
    LFSR3 = std::bitset<33>(semillas[2]);
    LFSR4 = std::bitset<39>(semillas[3]);
    R1 = std::bitset<2>(semillas[4]);
}

void E0::generar()
{
    std::bitset<1> zt;
    int caja1 = 0, caja2 = 0;

    caja1 += LFSR1[0] + LFSR2[0] + LFSR3[0] + LFSR4[0];

    // Cambio de posiciones para R1.
    int aux = R1[0];
    R1[0] = R1[1];
    R1[1] = aux;

    std::cout << "\nR1: " << R1 << std::endl;

    //Cambio de posiciones R2
    R2[0] = R1[1];
    R2[1] = R1[0];

    std::cout << "\nR2: " << R2 << std::endl;

    std::cout << "\nCAJA1: " << caja1 << std::endl;

    caja2 = R1.to_ulong() + caja1;

    std::cout << "\nCAJA2: " << caja2 << std::endl;

    std::bitset<2> suma_en_T2 = caja2 / 2;

    // Generar secuencia antes de cambiar valor de R1.
    zt = LFSR1[0] ^ LFSR2[0] ^ LFSR3[0] ^ LFSR4[0] ^ R1[0];
    Z += zt.to_string();

    //Formula PDF
    std::bitset<2> T2;

    T2[1] = R2[0];
    T2[0] = R2[1] ^ R2[0];

    std::cout << "\nT2: " << T2 << std::endl;

    std::bitset<2> suma_en_T1;

    suma_en_T1 = T2 ^ suma_en_T2;

    std::cout << "\nLFSR1: " << LFSR1[0] << std::endl;
    std::cout << "LFSR2: " << LFSR2[0] << std::endl;
    std::cout << "LFSR3: " << LFSR3[0] << std::endl;
    std::cout << "LFSR4: " << LFSR4[0] << std::endl;
    std::cout << "R1: " << R1[0] << std::endl;

    R1 ^= suma_en_T1;

    realimentacion();
}

void E0::realimentacion()
{
    std::bitset<1> br_1, br_2, br_3, br_4;
    br_1 = LFSR1[7] ^ LFSR1[11] ^ LFSR1[19] ^ LFSR1[24];
    br_2 = LFSR2[11] ^ LFSR2[15] ^ LFSR2[23] ^ LFSR2[30];
    br_3 = LFSR3[3] ^ LFSR3[23] ^ LFSR3[27] ^ LFSR3[32];
    br_4 = LFSR4[3] ^ LFSR4[27] ^ LFSR4[35] ^ LFSR4[38];

    LFSR1 >>= 1;
    LFSR2 >>= 1;
    LFSR3 >>= 1;
    LFSR4 >>= 1;

    LFSR1[24] = br_1[0];
    LFSR2[30] = br_1[0];
    LFSR3[33] = br_1[0];
    LFSR4[39] = br_1[0];
}

void E0::write()
{
    std::cout << "\n----------------------------------------------\n";
    std::cout << "LFSR1: " << LFSR1;
    std::cout << "\n----------------------------------------------\n";
    std::cout << "LFSR2: " << LFSR2;
    std::cout << "\n----------------------------------------------\n";
    std::cout << "LFSR3: " << LFSR3;
    std::cout << "\n----------------------------------------------\n";
    std::cout << "LFSR4: " << LFSR4;
    std::cout << "\n----------------------------------------------\n";
}