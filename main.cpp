#include "utils.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    try {
        ImageDownloader downloaderOne;
        downloaderOne.SetURL_FilePath("https://protei.ru/themes/custom/aga/favicon.ico", "../downloaded_image.ico");
        downloaderOne.Init();
    }
    catch (const std::exception& ex){
        std::cerr << ex.what() << std::endl;
        return -1;
    }
    return 0;
}
