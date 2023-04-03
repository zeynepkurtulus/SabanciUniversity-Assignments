#include <iostream>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW7_PrintQueue.h"
#include <mutex>
#include <string>
#include <thread>
#include <random>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <time.h>
using namespace std;

int maxPrintJobs, minpages, maxpages, counter = 0, idofprinter = 0, usercounter = 0;
mutex usermutex, printermutex, coutmutex, idmutex;
HW7PrintQueue printqueue;

int random_range(const int& min, const int& max) { // returns a random integer within the given range
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void user(const int &mintime, const int & maxtime, const int &userid)
{
    
    while (idofprinter <= maxPrintJobs) {
        this_thread::sleep_for(chrono::seconds(random_range(mintime, maxtime))); // sleeps for a random amount of time
        usermutex.lock();
        //usercounter++;
        idofprinter++;
        int pagecount =  random_range(minpages, maxpages); // this is the number of pages to be printed
        printqueue.enqueue(idofprinter, pagecount); // add the userid and number of pages to be printer to the queue
        int size = printqueue.getCurrentSize();
        usermutex.unlock();
        
        time_t current_time = chrono::system_clock::to_time_t (chrono::system_clock::now());
        struct tm *ptm = localtime(&current_time);
        //ptm->tm_min++;
        //ptm->tm_sec=0;
        coutmutex.lock();
        cout << "User " << userid << " sent new print job with ID " << idofprinter << " sent to the printer queue, number of pages: " << pagecount << " (print queue size: " << size << ")    " << put_time(ptm,"%X") << endl;
        coutmutex.unlock();
       
        
    }
}


void printjobs()
{
    int prntid, pg;
    while (counter <= maxPrintJobs) {
        printermutex.lock();
        if (!printqueue.isEmpty()) // checks if there is something to print
        {
            printqueue.dequeue(prntid, pg);
            int curr_size = printqueue.getCurrentSize();
            counter++;
            printermutex.unlock();
            time_t current_time = chrono::system_clock::to_time_t (chrono::system_clock::now());
            struct tm *ptm = localtime(&current_time);
            //ptm->tm_min++;
            //ptm->tm_sec=0;
            
            coutmutex.lock();
            cout << "The printer started to print the job with ID: " << prntid << ", number of pages: " << pg << "  (print queue size: " << curr_size << ")    " << put_time(ptm,"%X") << endl;
            //ptm->tm_min++;
            //ptm->tm_sec=0;
            coutmutex.unlock();
        
            this_thread::sleep_for(chrono::seconds(pg)); // sleep the tread
            current_time = chrono::system_clock::to_time_t (chrono::system_clock::now());
            ptm = localtime(&current_time);
            //ptm->tm_min++;
            //ptm->tm_sec=0;
            coutmutex.lock();
            cout << "The printer finished printing the job with ID: " << idofprinter << ", number of pages: " << pg << "  " << put_time(ptm,"%X") << endl;
            //ptm->tm_min++;
            coutmutex.unlock();
            
            //printermutex.unlock();
        }
        else // if the queue is empty allow the user to add stuff
            printermutex.unlock();
    }
}



int main()
{
    
    int mintime, maxtime;
    cout << "Please enter the max number of print jobs: ";
    cin >> maxPrintJobs;
    cout << "Please enter the min and max values for the waiting time period (in seconds) after creating a print job: " << endl;
    cout << "Min: ";
    cin >> mintime;
    cout << "Max: ";
    cin >> maxtime;
    cout << "Please enter the min and max values for the number of pages in a print job:" << endl;
    cout << "Min number of pages: ";
    cin >> minpages;
    cout << "Max number of pages: ";
    cin >> maxpages;
    time_t current_time = chrono::system_clock::to_time_t (chrono::system_clock::now());
    struct tm *ptm = localtime(&current_time);
    cout << "Simulation starts " << put_time(ptm,"%X") << endl;
    ptm->tm_min++;
    ptm->tm_sec=0;
    thread user1(&user, mintime, maxtime,1);
    thread user2(&user, mintime, maxtime,2);
    thread user3(&user, mintime, maxtime,3);
    thread printer(&printjobs);
    user1.join();
    user2.join();
    user3.join();
    printer.join();
    current_time = chrono::system_clock::to_time_t (chrono::system_clock::now());
    ptm = localtime(&current_time);
    cout<<"End of the simulation ends "<< put_time(ptm,"%X")<<endl<<endl;
    ptm->tm_min++;
    ptm->tm_sec=0;
    
    return 0;
}

