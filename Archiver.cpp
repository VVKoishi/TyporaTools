#include "Archiver.h"

// Change to your path
const path from = "./";
const path to = "./archived/";
// And default images path is "./assets/" , "./archived/assets/"
const path imgPath = "assets/";

int main(int argc, const char* argv[]) {

    cout << "Current Path: " << current_path() << "\n";

    if (argc < 2)
    {
        cout << "Usage: tools/ta a.md b.md c.md \n"
            << "From: " << from << "\n"
            << "To: " << to << "\n"
            << "You can change the paths setting in source code.\n";
        return 0;
    }

    vector<string> mdFileNames(argc-1);
    for (int i = 0; i < argc-1; i++)
    {
        mdFileNames[i] = argv[i+1];
    }

    Archiver a(mdFileNames, from, to, imgPath);
    a.Run();

    return 0;
}