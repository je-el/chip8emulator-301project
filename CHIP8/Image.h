#ifndef IMAGE_H_
#define IMAGE_H_
#include "common_headers.h"

class Image {
    public:
        //Allocs
        Image(int cols, int rows);
        ~Image();

        uint8_t* Row(int r);

        //returns a pixel that can be changed
        uint8_t& At(int c, int r);

        void SetAll(uint8_t value);

        void DrawToStdout();

        //void XOR(int c, int r, uint8_t val);

    private:
        int cols_;
        int rows_;
        uint8_t* data_;
};



#endif