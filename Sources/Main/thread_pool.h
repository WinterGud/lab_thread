#pragma once
#include <functional>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>

class thread_pool
{
public:
    thread_pool(int numThreads, std::string folderPath);
    ~thread_pool();
    void run();
    
    
private:
    std::vector<std::thread> m_threads;
    std::set<std::string> m_fileNames;
    std::map<std::string, int> m_wordsMap;
    std::mutex m_mutex;
    std::function<void(const std::string&, std::map<std::string, int>&)> m_funcToScrap;
    void parseFileNames(const std::string& path);
    void scrapFile(const std::string& path, std::map<std::string, int>& wordsMap);
    
};
