#include <string>
#include <iostream>
#include <experimental/filesystem>
using namespace::std;
namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[])
{
    string path = argv[1];
    for (auto & p : fs::directory_iterator(path))
    {
        cout << p << endl;
    }
    return 0;
}
