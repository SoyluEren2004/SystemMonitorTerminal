#include "HardDiskMonitor.h"

HardDiskMonitor::HardDiskMonitor(){

}
HardDiskMonitor::~HardDiskMonitor(){

}
void HardDiskMonitor::getDiskSpace(){
    system("df -H");
}
void HardDiskMonitor::getDiskHealth(){
    system("sudo smartctl -H /dev/sda | grep -i result; sudo smartctl -A /dev/sda | grep -E \"Media_Wearout_Indicator|Available_Reservd_Space\"");
}
void HardDiskMonitor::getDiskTemp() {
    FILE* pipe = popen("sudo smartctl -A /dev/sda | grep -i 'Temperature_Celsius' | awk '{print $10}'", "r");
    if (!pipe) {
        std::cerr << "coudn't start termial command !" << std::endl;
        return;
    }

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    if (!result.empty()) {
        result.erase(result.find_last_not_of(" \n\r\t") + 1);
        std::cout << "DISK TEMP : " << result << " °C" << std::endl;
    } else {
        std::cerr << "couldn't read temp (be Root )!" << std::endl;
    }
}
void HardDiskMonitor::printDiskInfo(){
    std::cout<<""<<std::endl;
    std::cout<<"<----------------------------------------------------- D I S K   I N F O  ------------------------------------------------>"<<std::endl;
    getDiskSpace();
    std::cout<<""<<std::endl;
    std::cout<<"<----------------------------------------------------- D I S K   H E A L T H  ------------------------------------------------>"<<std::endl;
    getDiskHealth();
    std::cout<<""<<std::endl;
    std::cout<<"<----------------------------------------------------- D I S K   T E M P  ------------------------------------------------>"<<std::endl;
    getDiskTemp();
}