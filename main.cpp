#include "RamCpuMonitor.h"
#include "HardDiskMonitor.h"
#include<iostream>
#include <unistd.h>// sleep() ve usleep()

struct 
{
    RamCpuMonitor ram_cpu_monitor;
    HardDiskMonitor hard_disk_monitor;
}obj;


int main(){
    while(true){
        system("clear");
        obj.ram_cpu_monitor.printInfo();
        obj.hard_disk_monitor.printDiskInfo();
        sleep(3);
    }
    
    return 0;
}