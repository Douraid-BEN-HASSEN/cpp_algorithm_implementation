// +------+
// | MAIN |
// +------+
#include <Windows.h>

#include "utils.h"

int main(int argc, char* argv[])
{

    if (argc > 4) {

        std::cout << "[0] " << argv[1] << std::endl;
        std::cout << "[1] " << argv[2] << std::endl;
        std::cout << "[2] " << argv[3] << std::endl;
        std::cout << "[3] " << argv[4] << std::endl;

        SetConsoleTitleA(argv[4]);

        setreadFromOutput(argv[1]);
        setnCouleurDifferente(atoi(argv[2]));
        setFolder(argv[3]);
        setFilename(argv[4]);

        
    }
    else if(argc == 4) {

        SetConsoleTitleA(argv[4]);

        std::cout << "[0] " << argv[1] << std::endl;
        std::cout << "[1] " << argv[2] << std::endl;
        std::cout << "[2] " << argv[3] << std::endl;
        std::cout << "[3] " << argv[4] << std::endl;

        setreadFromOutput(argv[1]);
        setnCouleurDifferente(atoi(argv[2]));
        setFolder(argv[3]);
        setFilename(argv[4]);
    }
    else {
        setreadFromOutput("D:/META_P2_final/x64/Debug/result/output_latin_square_10.txt");
        setnCouleurDifferente(97);
        setFolder("D:/META_P2_final/META_P2/");
        setFilename("latin_square_10.col");
    }

    init();

    algo_hybride();
}
