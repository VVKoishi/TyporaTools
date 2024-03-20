#include "ImgCleaner.h"

// Change to your path
const path dirPath = "./";
const path imgPath = "./assets/";

int main() {

    cout << "Current Path: " << current_path() << "\n";

    ImgCleaner ic(dirPath, imgPath);
    ic.Run();

    return 0;
}