#include "thread_pool.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <mutex>

namespace 
{
    namespace fs = std::filesystem;
}

thread_pool::thread_pool(int numThreads, std::string folderPath)
    : m_threads(numThreads)
    , m_funcToScrap(std::bind(&thread_pool::scrapFile, this, folderPath, m_wordsMap))
{
    parseFileNames(folderPath);
}

thread_pool::~thread_pool()
{
}

void thread_pool::run()
{
    using namespace std::chrono;
    const steady_clock::time_point timeStart = steady_clock::now();

    m_funcToScrap("..\\..\\Sources\\Files\file1 – копія (2).txt", m_wordsMap);
    
    // auto it = m_fileNames.begin();
    //
    // for (int i = 0; i < m_threads.size(); ++i)
    // {
    //     m_threads[i] = std::thread(m_funcToScrap, *it, std::ref(m_wordsMap));
    //     it = std::next(it);
    // }
    //
    // while (it != m_fileNames.end())
    // {
    //     for (auto& m_thread : m_threads)
    //     {
    //         if (m_thread.joinable())
    //         {
    //             m_thread.join();
    //             if (it == m_fileNames.end())
    //             {
    //                 break;
    //             }
    //             m_thread = std::thread(m_funcToScrap, *(it), std::ref(m_wordsMap));
    //             it = std::next(it);
    //         }
    //     }
    // }
    //
    // for (auto& m_thread : m_threads)
    // {
    //     if (m_thread.joinable())
    //     {
    //         m_thread.join();
    //     }
    // }
    
    const steady_clock::time_point timeEnd = steady_clock::now();
    const duration<double> time_span = duration_cast<duration<double>>(timeEnd - timeStart);
    for (auto& it : m_wordsMap)
    {
        std::cout << it.first << ' ' << it.second << '\n';
    }

    std::cout << time_span.count();
}

void thread_pool::scrapFile(const std::string& path, std::map<std::string, int>& wordsMap)
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
                std::lock_guard<std::mutex> lck (m_mutex);
                wordsMap.emplace(temp, 1);
            }
            else
            {
                std::lock_guard<std::mutex> lck (m_mutex);
                wordsMap.at(temp) += 1;
            }
        }
    }
}

void thread_pool::parseFileNames(const std::string& folderPath)
{
    try {
        if (fs::exists(folderPath) && fs::is_directory(folderPath))
            {
            for (const auto& entry : fs::directory_iterator(folderPath))
                {
                if (fs::is_directory(entry))
                {
                    parseFileNames(folderPath + '\\' + entry.path().filename().string());
                }
                else if (fs::is_regular_file(entry))
                {
                    m_fileNames.insert(folderPath + '\\' + entry.path().filename().string());
                    std::cout << folderPath + '\\' + entry.path().filename().string() << '\n';
                }
                else
                {
                    std::cout << entry.path().filename() << " is another type of entry." <<'\n';
                }
            }
        }
        else
        {
            std::cerr << "Вказаний шлях не існує або не є директорією." << '\n';
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Помилка: " << ex.what() << "\n";
    }
}
