#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

int STOP = 1;


// Function to call for creating a thread
void sleeping_function(int n_sec){
    while(STOP == 1) {
    cout<<"Let me sleep for " << n_sec <<" seconds\n";
    sleep(n_sec);
    }
}

int main(){

    cout<<"Creating a thread...\n";
    // create a thread
    thread th1(sleeping_function, 2);

    sleep(20);
    STOP = 0;
    cout<<"Deleting the thread...\n";
    // delete the thread
    th1.join();

}
