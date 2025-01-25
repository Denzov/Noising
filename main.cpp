#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {
    system("g++ mainUI.cpp UI.cpp UserCode/decoder.cpp UserCode/encoder.cpp -o UI");
    system("UI");
    system("del UI.exe");
    return 0;
}
