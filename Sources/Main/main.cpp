#include "thread_pool.h"
#include <fstream>
#include <iostream>

std::mutex mutex;

void scrapFile(const std::string& path, std::map<std::string, int>& wordsMap)
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
            
            if (wordsMap.find(temp) == wordsMap.end())
            {
                std::lock_guard<std::mutex> lck (mutex);
                wordsMap.emplace(temp, 1);
            }
            else
            {
                std::lock_guard<std::mutex> lck (mutex);
                wordsMap.at(temp) += 1;
            }
        }
    }
}

int main() 
{
    std::string path {"..\\..\\/Sources\\Files"};
    thread_pool tp(4, path);
    //tp.run();
    std::map<std::string, int> wordsMap;
    scrapFile("..\\..\\/Sources\\Files\\file1 – копія (2).txt", wordsMap);

    
    return 0;
}