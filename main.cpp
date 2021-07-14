#include "utils.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    try {
        DownloaderImage downloaderOne;
        downloaderOne.Init();
    }
    catch (const std::exception& ex){
        std::cerr << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
