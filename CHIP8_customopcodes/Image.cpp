
#include "common_headers.h"
#include "Image.h"
#include "cpu_chip8.h"

#include <iomanip>

Image::Image(int cols, int rows){
    data_ = static_cast<uint8_t*>(malloc(cols * rows * sizeof(uint8_t)));
    cols_ = cols;
    rows_ = rows;
}
Image::~Image(){
    free(data_);
}

uint8_t* Image::Row(int r){
    return &data_[r * cols_];
}

uint8_t& Image::At(int c, int r){
    return Row(r)[c];
}

void Image::SetAll(uint8_t value){
    std::memset(data_,value, rows_ * cols_);

}

void Image::DrawToStdout() {
    for (int r = 0; r < rows_ ; r++){
        for (int c = 0; c < cols_ ; c++){
            if ( At(c,r) > 0){ std::cout<< "X"; } else {std::cout << " ";}
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
//we will use drawto std out for now sp we can draw graphically to the console
// just until we set up the actual output


//see notes at #drawing to the console
//the interpreter also need to recieve back whether ot not  a pixel was turned off
// this i sused for collision detection
//remmeber that we xor to draw over with the sprites

//returns true if the new value unsets the pixel
bool Image::XOR(int c, int r, uint8_t val){
    uint8_t& current_val = At(c,r);
    uint8_t prev_val = current_val;
    current_val ^= val;
    return current_val == 0 && prev_val > 0;
}

void Image::CopyToRGB24(uint8_t* dst, int red_scale, int green_scale, int blue_scale) {
  int cols = Cols();
  for (int row = 0; row < Rows(); row++) {
    for (int col = 0; col < cols; col++) {
      dst[(row * cols + col) * 3] = At(col, row) * red_scale;
      dst[(row * cols + col) * 3 + 1] = At(col, row) * green_scale;
      dst[(row * cols + col) * 3 + 2] = At(col, row) * blue_scale;
    }
  }
 }

bool Image::XORSprite(int c, int r, int height, uint8_t* sprite){
    bool pixel_was_disabled = false;
    for (int y = 0; y < height; y++){
        int current_r = r + y;
        while (current_r >= rows_)
        {
            current_r -= rows_;
        }
        uint8_t sprite_byte = sprite[y];
        for (int x = 0; x < 8; x++){
            int current_c = c + x;
            while (current_c >= cols_){current_c -= cols_;}
            //we scan from MSbit to LSbit see notes
            uint8_t sprite_val = (sprite_byte & (0x80 >> x)) >> (7-x);
            pixel_was_disabled |= XOR(current_c, current_r, sprite_val);
        }  
    } 
    return pixel_was_disabled;
}
//we have to be precise whether we extract the bits as 1 or 0
// our image class supports 0 - 255 our XOR's could 
//get messy without the restriction
//now we just need to extract the parameters needed to call XORSprite