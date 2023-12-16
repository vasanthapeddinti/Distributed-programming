#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

// Function to call for creating a thread
void sleeping_function(int n_sec){
    cout<<"Let me sleep for " << n_sec <<" seconds\n";
    sleep(n_sec);
    cout<<"I slept for " << n_sec <<" seconds\n";
}

int main(){

    cout<<"Creating a thread...\n";
    // create a thread
    thread th1(sleeping_function, 10);

    cout<<"Deleting the thread...\n";
    // delete the thread
    th1.join();

}
