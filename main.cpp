#include "RamCpuMonitor.h"
#include "HardDiskMonitor.h"
#include "FanControl.h"
#include <iostream>
#include <unistd.h>

struct {
    RamCpuMonitor ram_cpu_monitor;
    HardDiskMonitor hard_disk_monitor;
    FanControl fan_control;
} obj;

int main() {
    while (true) {
        obj.ram_cpu_monitor.printInfo();
        obj.hard_disk_monitor.printDiskInfo();
        obj.fan_control.Fancontrol();
        std::cout << "---FRAME END---" << std::endl;
        sleep(5);
    }
    return 0;
}
