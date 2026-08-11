#include<iostream>
#include<cstdlib>

class HardDiskMonitor
{
private:
    /* data */
    void getDiskSpace();
    void getDiskHealth();
    void getDiskTemp();
public:
    HardDiskMonitor(/* args */);
    ~HardDiskMonitor();
    void printDiskInfo();
};

