#ifndef _UI_H_
#define _UI_H_

#include <fstream>
#include <filesystem>
#include <stdint.h>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <cstdlib>  
#include <ctime>    


typedef char* (*Decoder)(char* data, int length);
typedef char* (*Encoder)(char* data, int length);

class UI{
private:
    Decoder decoder;
    Encoder encoder;

    std::string NAME_CONFIG_FILE = "SIM_CONFIG";
    
    std::map<std::string, float> config;

    uint8_t* noise_data;

    float error_change_in_bit;
    float error_change_in_byte;
    uint32_t samples;

    static bool is_float(const std::string& str);

    bool pass_bit_values();
    bool is_config_available();
    bool load_config_from_file();

    void create_noise_data();

    void init_config();
    void noise_simulation_byte_by_byte();
    void noise_simulation_bit_by_bit();

    
public: 

    bool Init();
    void SetCodingFunction(Encoder user_encoder, Decoder user_decoder);
    void SimulateNoise();
    void debug();
};

bool UI::is_float(const std::string& str){
    try {
        std::size_t pos;
        std::stof(str, &pos);
        return pos == str.size();
    } 
    catch (...) {
        return false;
    }
}

bool UI::is_config_available(){
    if(!std::filesystem::exists(NAME_CONFIG_FILE)){
        std::cout << "[INFO] Config not exist\n";

        std::string config_format = 
       {".ENCODER_BLOCK_SIZE_BITS=0\n" + std::string(
        ".DECODER_BLOCK_SIZE_BITS=0\n") + std::string(
        ".SIMULATED_BYTES=100\n") + std::string(
        ".ERROR_CHANGE_IN_BIT=0.003\n") + std::string(
        ".ERROR_CHANGE_IN_BYTE=1\n")
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

void UI::init_config(){
    config["ENCODER_BLOCK_SIZE_BITS"] = 0;
    config["DECODER_BLOCK_SIZE_BITS"] = 0;
    config["SIMULATED_BYTES"] = 0;
    config["ERROR_CHANGE_IN_BIT"] = 0;
    config["ERROR_CHANGE_IN_BYTE"] = 0;
}

bool UI::load_config_from_file(){
    std::ifstream CONFIG(NAME_CONFIG_FILE);
    std::vector<char> str_config((std::istreambuf_iterator<char>(CONFIG)), std::istreambuf_iterator<char>());
    for(size_t i = 0; i < str_config.size(); i++){
        if(str_config[i] == '.'){
            i++;         

            if(i >= str_config.size()){
                return false;
            }
    
            /*ONLY CAPS ENGLISH LETTERS OR UNDERLINING*/
            std::string str_attribute_name = "";
            while (str_config[i] == '_' || (str_config[i] >= 65 && str_config[i] < 91)){
                str_attribute_name += str_config[i];
                i++;
            }
    
            std::string str_attribute_value = "";
            if(str_config[i] == '='){
                i++;
                while(str_config[i] == '.' || (str_config[i] >= 48 && str_config[i] < 57)){
                    str_attribute_value += str_config[i];
                    i++;
                }
            }

            if(is_float(str_attribute_value)){
                config[str_attribute_name] = std::stof(str_attribute_value);
            }
            else{
                return false;
            }
        }
    }
    
    for(auto& [key, value] : config){
        std::cout << key << " = " << value << "\n";
    }


    CONFIG.close();
    return true;
}

bool UI::Init(){
    init_config();
    
    try
    {
        if(!is_config_available()){ return false; }
        if(!load_config_from_file()){ return false; }
    }
    catch(...)
    {
        std::cout << "[ERROR] Loading config file is failed\n";
        return false;
    }
    
    std::srand(std::time(nullptr));

    return true;
}

void UI::SetCodingFunction(Encoder user_encoder, Decoder user_decoder){
    decoder = user_decoder;
    encoder = user_encoder;
}

/* This simulation is enabled when attribute "ERROR_CHANGE_IN_BYTE" is defined or not equal to 0*/
void UI::noise_simulation_byte_by_byte(){
    for(uint32_t sample = 0; sample < samples; sample++){
        
    }
}

/* This simulation is enabled when the attribute ERROR_CHANGE_IN_BIT is defined or not equal to 0 
    AND the attribute ERROR_CHANGE_IN_BYTE is not defined.*/
void UI::noise_simulation_bit_by_bit(){
    for(uint32_t sample = 0; sample < samples; sample++){
        
    }
}

void UI::SimulateNoise(){
    error_change_in_bit = config["ERROR_CHANGE_IN_BIT"];
    error_change_in_byte = config["ERROR_CHANGE_IN_BYTE"];
    samples = config["SAMPLES"];
    
    if(config["ERROR_CHANGE_IN_BYTE"] > 0){
        noise_simulation_byte_by_byte();
    }
    else{
        noise_simulation_bit_by_bit();
    }
        
}

void UI::debug(){
    std::cout << "UI\n";

    char* ptr = nullptr;    

    std::cout << (int)encoder(ptr, 3)[3];
}

#endif // !_UI_H_