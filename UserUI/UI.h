#ifndef _UI_H_
#define _UI_H_

#include <fstream>
#include <filesystem>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <map>
#include <string>

typedef char* (*Decoder)(char* data, int lenght);
typedef char* (*Encoder)(char* data, int lenght);

class UI{
private:
    Decoder decoder;
    Encoder encoder;

    std::string NAME_CONFIG_FILE = "SIM_CONFIG";
    
    bool is_created_config;
    std::map<std::string, float> map_config;

public: 
    bool pass_bit_values();
    bool available_config();
    bool pass_config_to_map();

    void setCodingFunction(Encoder user_encoder, Decoder user_decoder);
    bool init();
    void simulateNoise();
    void print();
};

bool UI::available_config(){
    if(!std::filesystem::exists(NAME_CONFIG_FILE)){
        std::cout << "[INFO] Config not exist\n";

        std::string config_format = 
       {"INPUT_PACKET_BITS=0\n" + std::string(
        "ENCODING_PACKET_BITS=0\n") + std::string(
        "SAMPLES=100\n") + std::string(
        "ERROR_CHANGE_IN_BIT=0.003\n") + std::string(
        "ERROR_CHANGE_IN_BYTE=1\n")
        };

        std::cout << "Create a file of the format:\n"
                    << config_format
                    << "\n(y/n?)\n";
        
        std::string answer;
        std::cin >> answer;

        if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "yes"){
            std::ofstream OFSTR_CONFIG(NAME_CONFIG_FILE);

            OFSTR_CONFIG << config_format;

            OFSTR_CONFIG.close();
        }
        else{ 
            return false;
        }
    }

    return true;
}

bool UI::pass_config_to_map(){
    std::ifstream CONFIG(NAME_CONFIG_FILE);
    std::vector<char> str_config((std::istreambuf_iterator<char>(CONFIG)), std::istreambuf_iterator<char>());
    for(size_t i = 0; i < str_config.size(); i++){
        bool flag_error_of_cofig = 0;
        std::string str_argument_name = "";
        while(str_config[i] != '='){
            if(i >= str_config.size()){
                flag_error_of_cofig = 1;
                break;
            }

            str_argument_name += str_config[i];
            i++; 
        }
        
        i++;
        std::string str_argument_value = "";
        while(str_config[i] != '\n'){
            if(i >= str_config.size()){
                flag_error_of_cofig = 1;
                break;
            }
            str_argument_value += str_config[i];
            i++;
        }

        if(!flag_error_of_cofig){
            float argument_value = std::stof(str_argument_value);
            map_config[str_argument_name] = argument_value;
        }
        else{
            std::cout << "[ERROR] Error of config file\n";
            return false;
        }
    }    

    for(auto& [key, value] : map_config){
        std::cout << key << " = " << value << "\n";
    }

    CONFIG.close();
    return true;
}

bool UI::init(){
    if(!available_config()) return false;
    if(!pass_config_to_map()) return false;
    
    return true;
}

void UI::setCodingFunction(Encoder user_encoder, Decoder user_decoder){
    decoder = user_decoder;
    encoder = user_encoder;
}

void UI::simulateNoise(){
    
}

void UI::print(){
    std::cout << "UI\n";

    char* ptr = nullptr;    

    std::cout << (int)decoder(ptr, 3)[3];
}

#endif // !_UI_H_