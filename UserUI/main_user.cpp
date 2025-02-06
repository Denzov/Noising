#include "UI.h"

#include "user_code.h"

int main(int argc, char* argv[]){
    UI ui;
    if(ui.Init()){
        ui.SetCodingFunction((Encoder)user_encoder, (Decoder)user_decoder);
        ui.debug();
    }
    
}