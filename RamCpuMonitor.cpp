/*
    Hedef: Konsola her 2 saniyede bir anlık RAM kullanım yüzdesini ve CPU yükünü yazdıran bir program yaz
    Linux için: /proc/meminfo ve /proc/stat dosyalarını C ile açıp okumayı hallet(fopen, fgets)

*/
#include "RamCpuMonitor.h"

RamCpuMonitor::RamCpuMonitor() {
}

// Destructor
RamCpuMonitor::~RamCpuMonitor() {
}
void RamCpuMonitor::getCpu() {
    system("head -n 5 /proc/stat");
    FILE* file = fopen("/proc/stat", "r");
    if (!file) {
        std::cerr << "couldn't open file /proc/stat" << std::endl;
        return;
    }

    char line[256];
    if (fgets(line, sizeof(line), file)) {
        unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
        sscanf(line, "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
               &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal);

        // Current hesaplamalar
        unsigned long long currentIdle = idle + iowait;
        unsigned long long currentTotal = user + nice + system + idle + iowait + irq + softirq + steal;

        // Delta hesaplamaları
        unsigned long long totalDiff = currentTotal - prevTotal;
        unsigned long long idleDiff = currentIdle - prevIdle;

        // eski değerleri güncelle
        prevTotal = currentTotal;
        prevIdle = currentIdle;

        // bölünme hatasını önle
        if (totalDiff > 0) {
            double cpuUsage = ((double)(totalDiff - idleDiff) / totalDiff) * 100.0;
            std::cout << "CPU usage  : %" << cpuUsage << std::endl;
        }
    }

    fclose(file);
}
void RamCpuMonitor::getRam() {
    FILE* file = fopen("/proc/meminfo", "r");
    if (!file) {
        std::cerr << "Dosya acilamadi!" << std::endl;
        return;
    }

    char line[256];
    memTotal = 0;
    memAvailable = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %lld kB", &memTotal) == 1) {
            continue;
        }

        if (sscanf(line, "MemAvailable: %lld kB", &memAvailable) == 1) {
            break;
        }
    }

    fclose(file);

    if (memTotal > 0) {
        long long cuRam = memTotal - memAvailable;
        double ramPercant = ((double)cuRam / memTotal) * 100.0;

        std::cout << "Total RAM     : " << memTotal / 1024 << " MB" << std::endl;
        std::cout << "Available RAM : " << memAvailable / 1024 << " MB" << std::endl;
        std::cout << "Currently Used RAM : " << cuRam / 1024 << " MB" << std::endl;
        std::cout << "Currently Used RAM  : %" << ramPercant << std::endl;
    }
}
void RamCpuMonitor::getCpuTemp(){
    FILE* file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!file) {
        std::cerr << "Dosya acilamadi!" << std::endl;
        return;
    }

    long long tempVal = 0;
    if (fscanf(file, "%lld", &tempVal) == 1) {
        double cpuTempC = (double)tempVal / 1000.0;
        std::cout << "CPU TEMP : " << cpuTempC << " °C" << std::endl;
    } else {
        std::cerr << "couldn't read temp!" << std::endl;
    }

    fclose(file);
}
void RamCpuMonitor::printInfo(){
    std::cout<<"--------------------------------------------------- M E M O R Y  I N F O --------------------------------------------------"<<std::endl;
    getRam();
    std::cout<<""<<std::endl;
    std::cout<<"--------------------------------------------------- C P U  I N F O -----------------------------------------------------"<<std::endl;
    getCpu();
    std::cout<<""<<std::endl;
    std::cout<<"--------------------------------------------------- C P U  T E M P -----------------------------------------------------"<<std::endl;
    getCpuTemp();
}