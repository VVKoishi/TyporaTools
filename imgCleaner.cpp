#include "ImgCleaner.h"

// change to your path
const path dirPath = "../";
const path imgPath = "../assets/";

int main() {
	
	ImgCleaner ic(dirPath, imgPath);
	ic.Run();

	return 0;
}