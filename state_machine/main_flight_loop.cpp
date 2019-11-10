#include <iostream>


int main(){

    enum States { idle=0, powered, coast, apoge, descent, help_me };
    States current_state = powered;
    


    switch(current_state){
        case idle:
            std::cout << "idle\n";
            break;
        case powered:
            std::cout << "powered\n";
            break;
        case coast:
            std::cout << "coast\n";
            break;
        case apoge:
            std::cout << "apoge\n";
            break;
        case descent:
            std::cout << "descent\n";
            break;
        case help_me:
            std::cout << "help_me\n";
    }
    return 0;
}

