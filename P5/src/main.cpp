#include "E0.hpp"

int main()
{
    std::string lfsr1 = "0101010101010101010101111";
    std::string lfsr2 = "0101010101010101010101010101111";
    std::string lfsr3 = "010101010101010101010101010101111";
    std::string lfsr4 = "010101010101010101010101010101010101010";

    std::string r1 = "01";

    std::vector<std::string> semilas = {lfsr1, lfsr2, lfsr3, lfsr4, r1};

    E0 generador(semilas);

    bool salir = false;
    int operacion = 0;

    while (!salir)
    {
        std::cout << "\n------------------------------------";
        std::cout << "\n¿Qué desea hacer?\n";
        std::cout << "[0] Salir.\n";
        std::cout << "[1] Generar secuencia.\n";
        std::cout << "[2] Mostrar información de los LFSR.\n";
        std::cout << "------------------------------------\n";
        std::cin >> operacion;

        switch (operacion)
        {
        case 0:
            salir = true;
            break;
        case 1:
            for (int i = 0; i < 4; i++)
            {
                generador.write();
                generador.generar();
            }

            std::cout << "\nZ: " << generador.get_Z() << std::endl;
            break;
        case 2:
            generador.write();
            break;
        default:
            std::cout << "\nOperación incorrecta.\n";
        }
    }
    return 0;
}