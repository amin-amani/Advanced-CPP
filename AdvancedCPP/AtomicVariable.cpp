#include <iostream>
#include <atomic>
#include <thread>


int counter(0);
void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        counter++;
    }
}
void PrintNormalIncrement()
{
    for(int i=0;i<1000;i++){
        counter=0;
    std::thread thread1(incrementCounter);
    std::thread thread2(incrementCounter);

    thread1.join();
    thread2.join();
if(counter!=2000)
    std::cout << "wrong Counter value: " << counter << std::endl;
}

}

std::atomic<int> atomiccounter(0);
void atomicincrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        atomiccounter++;
    }
}
void PrintAtomiclIncrement()
{
    for(int i=0;i<1000;i++){
        atomiccounter=0;
    std::thread thread1(atomicincrementCounter);
    std::thread thread2(atomicincrementCounter);

    thread1.join();
    thread2.join();
if(counter!=2000)
    std::cout << "wrong Atomic Counter value: " << atomiccounter << std::endl;
}

}

int main() {
PrintNormalIncrement();
PrintAtomiclIncrement();


    return 0;
}
