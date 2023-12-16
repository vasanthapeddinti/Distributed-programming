// This program creates three threads t1, t2, t3.
// th1(mommy) waits for th2(daddy) to finish
// th2(daddy) waits for th3(child) to finish

#include<iostream>
#include<thread>
#include<unistd.h>

using namespace std;

int POTTY_DONE = 0;
int CHILD_DONE = 0;
int DADDY_DONE = 0;


void child_function(int n_sec){
    cout<< "inside child\n";
    while(POTTY_DONE != 1){
        cout<< "Let me sleep for " << n_sec <<" seconds\n" ;
        sleep(n_sec); // This guy sleeps for 5 seconds
    }
    cout<< "child finishing..\n";
    CHILD_DONE = 1;
}

void daddy_function(){
    cout<< "inside daddy\n";
    while (CHILD_DONE != 1){
        cout<< "Waiting for child thread to finish\n";
        this_thread::sleep_for(6000ms); // So, daddy waits for 6 seconds
    }
    cout<< "daddy finishing..\n";
    DADDY_DONE = 1;
}

void mommy_function(){
    cout<< "inside mommy\n";
    while (DADDY_DONE != 1){
        cout<< "Waiting for daddy thread to finish\n";
        this_thread::sleep_for(7000ms); // So, mommy waits for 7 seconds
    }
    cout<< "mommy finishing..\n";
}


int main(){

    // Creating thread th1
    thread th1(mommy_function);

    sleep(1);

    // Creating thread th2
    thread th2(daddy_function);

    sleep(1);

    // Creating thread th3
    thread th3(child_function, 5);

    sleep(1);

    cout << "finishing potty\n";
    sleep(5);

    POTTY_DONE = 1;


    cout<<"Deleting the thread...\n";
    // delete the thread
    th1.join();
    cout<<"Thread1 exited...\n";
    th2.join();
    cout<<"Thread2 exited...\n";
    th3.join();
    cout<<"Thread3 exited...\n";

}