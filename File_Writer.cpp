#include <iostream>
#include <fstream>
using namespace std;

int writeFile(int x);

int main()
{
    writeFile(10);
    return 0;
}

int writeFile(int x)
{
    ofstream myfile;
    if (! myfile)
    {
        cout << "Error opening file!" << endl;
        return -1;
    }

    else{
    myfile.open("test.txt", std::ofstream::out | std::ofstream::app);

    for(int i = 1; i<=x; i++){
        myfile << i  << ". " << "Writing this to a file." <<endl;
        cout  << i  << ". " <<  "Writing this to a file." <<endl;
        }
    }
    myfile.close();
    return 0;
}
