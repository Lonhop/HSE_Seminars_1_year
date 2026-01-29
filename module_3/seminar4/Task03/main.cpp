#include <memory>
#include <iostream>


class Buffer {

};



int main() {
    Buber buf(1024);
    buf[0] = 'H';
    buf[1] = 'i';
    buf.reset(2048);
    // !!!! Destructor should log final deallocation
}