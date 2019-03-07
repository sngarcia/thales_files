#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>
#include <chrono>
#include <thread>


using namespace std;
using namespace std::chrono_literals;
namespace fs = std::experimental::filesystem;

int main()
{

    int count = 0;
    std::time_t current = std::time(nullptr);

    while(true){
    cout << "Count : " << count <<"\n";
    count++;
    cout << "Current_path() = "  << fs::current_path()<<"\n";

    for(auto& p: fs::recursive_directory_iterator("A_directory")){
        string str (p.path());
        string prefix = str.substr(12, 4);
        if (prefix.find("cool") != string::npos ) {
            std::cout << str<<" - >found."<<"\n";
            //After 60 seconds, it will transfer the to directory B.
            std::this_thread::sleep_for(60s);
            // Try to copy the file to destiny directory
            try {
                fs::copy(str, "B_directory/");
            } catch(fs::filesystem_error& e) {
                std::cout << e.what() << '\n';
            }
            //Removes the file from previous directory
            cout<<"\n Deleted "<<fs::remove(str) <<": "<<str<< " from A_directory";
        }
    }

//Wait 1 second in each loop - Our program will check at each 60 seconds
    std::this_thread::sleep_for(60s);

}

     return 0;
}
