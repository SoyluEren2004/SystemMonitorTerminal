#include<iostream>
#include<cstdlib>

class RamCpuMonitor
{
private:
    char line[256];
    long long memTotal;
    long long memAvailable;

    unsigned long long prevIdle = 0;
    unsigned long long prevTotal = 0;
    void getRam();
    void getCpu();
    void getCpuTemp();
public:
    RamCpuMonitor(/* args */);
    ~RamCpuMonitor();
    void printInfo();
};


