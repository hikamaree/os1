#include "../h/console.h"
#include "../h/tcb.h"

ConsoleBuffer* CON::input;
ConsoleBuffer* CON::output;

void CON::init() {
    input = new ConsoleBuffer(1024);
    output = new ConsoleBuffer(1024);
	TCB::createThread((void(*)(void*))CON::print, nullptr);
}

char CON::get_input(){
    return input->get();
}

char CON::get_output(){
    return output->get();
}

void CON::put_input(char c){
    input->put(c);
}

void CON::put_output(char c){
    output->put(c);
}

void CON::print() {
    while(true) {
        if(*((char *) CONSOLE_STATUS) & CONSOLE_TX_STATUS_BIT) {
            *((char*)CONSOLE_TX_DATA) = CON::get_output();
        }
    }
}
