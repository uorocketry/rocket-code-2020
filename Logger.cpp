#include <iostream>
#include <fstream>
using namespace std;

class Rocket
{
    // private variables are only available to methods in the class
    private:
        string name;
        float sensor1;
        float sensor2;

    // Public variables can be accessed by anything with access to the object
    public:
        //constructor
        Rocket(string);

        void log(string filename);
        float getSensor1(){return sensor1;}
        void setSensor1(float val){sensor1 = val;}

        float getSensor2(){return sensor2;}
        void setSensor2(float val){sensor2 = val;}
        //Destructor
        ~Rocket();
};

//Rocket constructor
Rocket::Rocket(string name)
{
    this->name = name;
}

void Rocket::log(string filename)
{
    ofstream myfile(filename.c_str(), std::ios_base::app); //append;
    if(myfile.is_open())
    {
        cout << "Writing sensor1 data: " << this->getSensor1() << " to " << filename << endl;
        cout << "Writing sensor2 data: " << this->getSensor2() << " to " << filename << endl;

        myfile << "sensor1: "<< this->getSensor1() << endl;
        myfile << "sensor2: "<< this->getSensor2() << endl;
        myfile.close();
    }
    else cout << "Unable to open " <<filename << endl;
}

//Rocket deconstructor
Rocket::~Rocket()
{
    cout << "Rocket " << this->name << " destroyed" << endl;
}

int main()
{
    //rocket instance
    Rocket uOttRocket("Rocky");

    //sbg update sensor
    uOttRocket.setSensor1(25.83);
    uOttRocket.setSensor2(3000.44);
    uOttRocket.log("LogFile.txt");

    uOttRocket.setSensor1(199.95);
    uOttRocket.setSensor2(3.14159);
    uOttRocket.log("LogFile.txt");
    return 0;
}
