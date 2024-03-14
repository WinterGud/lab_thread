#include <iostream>      
#include <thread>
#include <fstream>
#include <vector>
#include <chrono>
 
void scrapFile(std::string path, std::vector<int>& numWordsList)
{
    std::ifstream is(path);
    if(!is)
    {
        std::cout << "file path is uncorrected\n";
    }
    else
    {
        int num = 0;
        while (is)
        {
            std::string temp;
            is >> temp;
            ++num;
        }
        numWordsList.push_back(num);
    }
}

int main() 
{
    using namespace std::chrono;
    steady_clock::time_point timeStart = steady_clock::now();
    
    std::vector<int> numWordsList;
    std::thread thread1 (scrapFile, "..\\..\\Solution\\Main\\data\\file1.txt", std::ref(numWordsList));
    std::thread thread2 (scrapFile, "..\\..\\Solution\\Main\\data\\file2.txt", std::ref(numWordsList));
 
    thread1.join();                
    thread2.join();
    
    steady_clock::time_point timeEnd = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(timeEnd - timeStart);
    std::cout << time_span.count() << " seconds.\n";
    
    std::cout << numWordsList[0] << ' ' << numWordsList[1];
    
    return 0;
}