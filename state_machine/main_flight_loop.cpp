#include <iostream>

enum States { idle=0, powered, coast, apoge, descent, help_me };
bool quit = false;

void idle_state (){}
void powered_state (){}
void coast_state (){}
void apoge_state (){}
void descent_state (){}
void help_me_state (){}


void event_powered (States *current_state_ptr) {*current_state_ptr = powered;}
void event_coast (States *current_state_ptr) {*current_state_ptr = coast;}
void event_apoge (States *current_state_ptr) {*current_state_ptr = apoge;}
void event_descent (States *current_state_ptr) {*current_state_ptr = descent;}
void event_help_me (States *current_state_ptr) {* current_state_ptr = help_me;}

int main(){

    
    States current_state = idle;

    while (quit == false){
      switch(current_state){
        case idle:
            std::cout << "idle\n";
            idle_state();

            event_powered(&current_state);
            break;
        
        case powered:
            std::cout << "powered\n";
            powered_state();

            event_coast(&current_state);
            break;
        case coast:
            std::cout << "coast\n";
            coast_state();

            event_apoge(&current_state);
            break;
        case apoge:
            std::cout << "apoge\n";
            apoge_state();

            event_descent(&current_state);
            break;
        case descent:
            std::cout << "descent\n";
            descent_state();

            event_help_me(&current_state);
            break;
        case help_me:
            std::cout << "help_me\n";
            help_me_state();
            quit = true;
        }  
    }
    
    
    return 0;
}

