#include "FanControl.h"
#include <iostream>
#include <unistd.h>
#include <sys/poll.h> // poll 

void FanControl::Fancontrol(){
    int choice = -1; 
    std::cout<<"Fan Control:\n-> 1-Close Fans\n-> 2-Set mid level to your fan\n-> 3-Set max level to your fan"<<std::endl;
    std::cout<<"Type number (5s timeout): " << std::flush;

    // Linux poll  (stdin, fd = 0)
    struct pollfd pfd;
    pfd.fd = 0; // STDIN_FILENO
    pfd.events = POLLIN;

    // 5s
    int ret = poll(&pfd, 1, 5000); 

    if (ret > 0) { 
        std::cin >> choice;
    } else {
        std::cout << "\n[Time out: No input received, skipping...]\n";
        return; 
    }

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
