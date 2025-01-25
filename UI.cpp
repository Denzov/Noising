#include "UI.h"

bool UI::pass_bit_values(){
    std::ifstream CONFIG(NAME_CONFIG_FILE);

    if(!CONFIG){
        std::cout << "\"CONFING\" not exist\n";
        std::string answer = "";

        std::cout << "Create a file of the following format:\n"
                  << ".VALUE_INPUT_PACKET_BITS=0\n" 
                  << ".VALUE_ENCODING_PACKET_BITS=0\n\n"
                  << "(Y/N?)\n";
        
        std::cin >> answer;

        if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "yes"){
            std::ofstream OFSTR_CONFIG(NAME_CONFIG_FILE);

            OFSTR_CONFIG << ".VALUE_INPUT_PACKET_BITS=0\n"
                         << ".VALUE_ENCODING_PACKET_BITS=0\n";

            OFSTR_CONFIG.close();
        }
        return false;
    }

    std::vector<char> str;
    char num;
    while(CONFIG >> num){
        str.push_back(num);
    }

    for(int i = 0; i < str.size(); i++){
        std::cout << str[i]; 
    }
    
    std::cout << '\n'; 

    return true;
}

void UI::print(){
    std::cout << "UI\n";

    char* ptr = nullptr;    

    std::cout << (int)decoder(ptr, 3)[3];
}