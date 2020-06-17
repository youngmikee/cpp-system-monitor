#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <unistd.h>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    this->SetUtilization();
    int const prev_total = this->total_;
    int const prev_idle = this->idle_;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    this->SetUtilization();
    int current_idle = this->idle_;
    int current_total = this->total_; 

    float idle = current_idle - prev_idle;
    float total = current_total - prev_total;

    float util = (total - idle) / (total / 100000);
    return util / 100000;

}

void Processor::SetUtilization() {
    this->total_ = 0;
    std::vector<std::string> stats = LinuxParser::CpuUtilization();
    std::string idle = stats[LinuxParser::kIdle_];
    std::string iowait = stats[LinuxParser::kIOwait_];
    for (auto stat : stats) {
        if (stat != "") {
            this->total_ += std::stoi(stat);
        }
    }
    if (idle != "") {
        this->idle_ = std::stoi(idle);

        if (iowait != "") {
            this->idle_ += std::stoi(iowait);
        }
    }
}

// void Processor::SetUtilization() {
//     std::vector<std::string> cpuLine = LinuxParser::CpuUtilization();
//     int kuser = std::stoi(cpuLine[LinuxParser::kUser_]);
//     int knice = std::stoi(cpuLine[LinuxParser::kNice_]);
//     int ksystem = std::stoi(cpuLine[LinuxParser::kSystem_]);
//     int kidle = std::stoi(cpuLine[LinuxParser::kIdle_]);
//     int kiowait = std::stoi(cpuLine[LinuxParser::kIOwait_]);
//     int kirq = std::stoi(cpuLine[LinuxParser::kIRQ_]);
//     int ksoftirq = std::stoi(cpuLine[LinuxParser::kSoftIRQ_]);
//     int ksteal = std::stoi(cpuLine[LinuxParser::kSteal_]);
    
//     int idle = kidle + kiowait;  // Done
//     int noneIdle = kuser + knice + ksystem + kirq + ksystem + ksoftirq + ksteal; // Done
//     this->total_ = idle + noneIdle;
//     this->idle_ = idle;
// }