#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) 
{
    fstream data_file = fstream(argv[1]);

    cout << "hasdfaha" << endl;

    data_file.close();
    return 0;
}