//main.cpp file
#include "common_headers.h"
#include <iostream>
#include <exception>

//chip 8 class will hold onto the state of the machine and interpreter 
void RUN() {
    cpuchip8 cpu;
    cpu.Initialize("/path/to/program/file"); //initialize and Runcycle see line 11, create the skeleton
    bool quit = false;
    while (!quit){ cpu.runcycle(); }
}

int main(int argc, char** argv)
{
    try{ RUN(); } 
    catch (const std::exception& e){
        std::cerr << "ERROR: "<< e.what();
        return 1; }
}