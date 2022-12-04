#include "Image.h"
#include "common_headers.h"

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