#include "thread_pool.h"


int main() 
{
    std::string path {"..\\..\\/Sources\\Files"};
    thread_pool tp(4, path);
    tp.run();

    
    return 0;
}