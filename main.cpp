#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>

int main() {
    std::string user_code_path = "UserUI/";
    std::string program_name = "PROCESS_UI";

    system(("g++ " + user_code_path + "*.cpp -o " + program_name).c_str());
    if(std::filesystem::exists(program_name + ".exe"))
    {
        system(("attrib +h " + program_name + ".exe").c_str());
        system(program_name.c_str());
        system(("attrib -h " + program_name + ".exe").c_str());
        system(("del " + program_name + ".exe").c_str());
    }
    return 0;
}
