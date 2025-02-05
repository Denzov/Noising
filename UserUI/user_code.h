#ifndef _USER_CODE_H_
#define _USER_CODE_H_

char* user_encoder(char* data, char length)
{
    static char out[]{
        2, 3, 4, 64, 12
    };

    return out;
}

char* user_decoder(char* data, char length)
{
    static char out[]{
        2, 3, 4, 64, 12
    };

    return out;
}

#endif // !_USER_CODE_H_