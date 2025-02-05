#include "UI.h"

#include "user_code.h"

int main(int argc, char* argv[]){
    UI ui;
    if(ui.init()){
        ui.setCodingFunction((Encoder)user_encoder, (Decoder)user_decoder);
        ui.print();
    }
    
}