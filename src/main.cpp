#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include "process.h"
#include "format.h"
#include <iostream>

int main() {
  System system;

  //std::cout << "Linux Pids: " << LinuxParser::Pids().size() << "\n"
  // std::cout << "Linux Memory : " << LinuxParser::MemoryUtilization() << "\n";
  //std::cout << "Linux Uptime: " << LinuxParser::UpTime() << "\n";
  //std::cout << "Time in sec: " << system.UpTime() << "\n";
  //std::cout << "Running processes: " << LinuxParser::RunningProcesses() << "\n";
  //std::cout << "Total Processes: " << LinuxParser::TotalProcesses() << "\n";
  //std::cout << "CPU utilizaton: " << system.Cpu().Utilization() << "\n";
  // for (auto i : LinuxParser::Pids()) {
  //   std::cout << "Pids: " << i << "\n";
  // }
  // std::cout << "Total Jiffies: " << LinuxParser::Jiffies() << "\n";
  // std::cout << "Total ActiveJiffies: " << LinuxParser::IdleJiffies() << "\n";
  // std::cout << "Total ActiveJiffies: " << LinuxParser::ActiveJiffies(1) << "\n";
  // std::cout << "Ram: " << LinuxParser::Ram(1)<< "\n";
  // std::cout << "User: " << LinuxParser::User(4158)<< "\n";
  // std::cout << "Uid: " << LinuxParser::Uid(6094)<< "\n";
  // std::cout << "Uid: " << LinuxParser::UpTime(6094)<< "\n";
  // Process process(6094);
  // std::cout << "Process 4158 cpu Util: " << process.CpuUtilization() << "\n" <<
  // "Uptime: " << Format::ElapsedTime(process.UpTime()) << "\n" << "Process command: " << process.Command() << "\n";  
  
   NCursesDisplay::Display(system);
}