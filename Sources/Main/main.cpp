#include <iostream>      
#include <thread>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include <mutex>

std::mutex mutex;
 
void scrapFile(std::string path, std::map<std::string, int>& wordsMap)
{
    std::ifstream is(path);
    if(!is)
    {
        std::cout << "file path is uncorrected\n";
    }
    else
    {
        while (is)
        {
            std::string temp;
            is >> temp;
            mutex.lock();
            if (wordsMap.find(temp) == wordsMap.end())
            {
                wordsMap.emplace(temp, 1);
            }
            else
            {
                wordsMap.at(temp) += 1;
            }
            mutex.unlock();
        }
    }
}

int main() 
{
    using namespace std::chrono;

    std::vector<std::string> paths =
        {
        "..\\..\\Solution\\Main\\data\\file1.txt",
        "..\\..\\Solution\\Main\\data\\file2.txt",
        "..\\..\\Solution\\Main\\data\\file3.txt",
        "..\\..\\Solution\\Main\\data\\file4.txt",
        "..\\..\\Solution\\Main\\data\\file5.txt",
        "..\\..\\Solution\\Main\\data\\file6.txt"
        };

    const int threadsNum = 2;
    std::vector<std::thread> threads(threadsNum);
    steady_clock::time_point timeStart = steady_clock::now();
    std::map<std::string, int> wordsMap;

    for (int i = 0; i < paths.size() / threadsNum; i++)
    {
        for (int j = 0; j < threadsNum; j++)
        {
            threads[j] = std::thread(scrapFile, paths[i + j], std::ref(wordsMap));
        }
 
        for (int j = 0; j < threadsNum; j++)
        {
            threads[j].join();
        }
    }
    steady_clock::time_point timeEnd = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(timeEnd - timeStart);
    for (auto it = wordsMap.begin(); it != wordsMap.end(); it++)
    {
        std::cout << it->first << ' ' << it->second << '\n';
    }

    std::cout << time_span.count();
    
    
    
    return 0;
}