#include "FanControl.h"



void FanControl::Fancontrol(){
    int choice;
    std::cout<<"Fan Control:\n-> 1-Close Fans\n-> 2-Set mid level to your fan\n-> 3-Set max level to your fan"<<std::endl;
    std::cout<<"Type number: ";
    std::cin>>choice;
    std::cout<<std::endl;
    switch (choice)
    {
    case 1:
        system("echo 1 | sudo tee /sys/class/hwmon/hwmon3/pwm1_enable");
        system("echo 0 | sudo tee /sys/class/hwmon/hwmon3/pwm1");
        std::cout<<"you close your fan"<<std::endl;
        break;
    
    case 2:
        system("echo 1 | sudo tee /sys/class/hwmon/hwmon3/pwm1_enable");
        system("echo 128 | sudo tee /sys/class/hwmon/hwmon3/pwm1");
        std::cout<<"you set your fan mid level"<<std::endl;
        break;
    case 3:
        system("echo 1 | sudo tee /sys/class/hwmon/hwmon3/pwm1_enable");
        system("echo 255 | sudo tee /sys/class/hwmon/hwmon3/pwm1");
        std::cout<<"you set your fan max level"<<std::endl;
        break;
        
    default:
        break;
    }

}
