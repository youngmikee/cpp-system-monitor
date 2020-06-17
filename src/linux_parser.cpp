#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string key, line;
  double value, totalMemory, freeMemory, buffers;
  std::vector<double> m;
  std::ifstream fileStream(kProcDirectory + kMeminfoFilename);
  if(fileStream.is_open()) {
    int i{0};
    while(getline(fileStream, line) && i < 4){
      std::istringstream lineStream(line);
      lineStream >> key >> value;
      m.push_back(value);
      i++;
    }
    totalMemory = m[0];
    freeMemory = m[1];
    buffers = m[3];
  } else {

    return 0.0; 
  }


  return freeMemory / (totalMemory - buffers) ;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  string line;
  double sysUptime, sysIdletime;
  std::ifstream fileStream(kProcDirectory + kUptimeFilename);
  if(fileStream.is_open()) {
    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    lineStream >> sysUptime >> sysIdletime;
  } else {

    return 0; 
  }
  
  return sysUptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  string line;
  long total, value;
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  if(fileStream.is_open()) {
    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    while (lineStream >> value) {
      total =+ value;
    } 

    return total;
  } else {

    return 0; 
  }
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line, value;
  vector<string> jiffies;
  long total{0};
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if(fileStream.is_open()) {
    int i = 0;
    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    while (lineStream >> value && i < 23) {
      jiffies.push_back(value);
      i++;
    }

    if (jiffies[13] != "") {
      total += std::stoi(jiffies[13]);
    }

    if (jiffies[14] != "") {
      total += std::stoi(jiffies[14]);
    }

    // if (jiffies[15] != "") {
    //   total += std::stoi(jiffies[15]);
    // }

    // if (jiffies[16] != "") {
    //   total += std::stoi(jiffies[16]);
    // }

    return total;    
  } else {

    return total; 
  }  
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line, value;
  vector<string> jiffies;
  long total{0};
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  if(fileStream.is_open()) {
    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    while (lineStream >> value) {
      jiffies.push_back(value);
    }
    jiffies.erase(jiffies.begin());

    if (jiffies[kUser_] != "") {
      total += std::stoi(jiffies[kUser_]);
    }

    if (jiffies[kNice_] != "") {
      total += std::stoi(jiffies[kNice_]);
    }

    if (jiffies[kSystem_] != "") {
      total += std::stoi(jiffies[kSystem_]);
    }

    if (jiffies[kIRQ_] != "") {
      total += std::stoi(jiffies[kIRQ_]);
    }

    if (jiffies[kSoftIRQ_] != "") {
      total += std::stoi(jiffies[kSoftIRQ_]);
    }

    if (jiffies[kSteal_] != "") {
      total += std::stoi(jiffies[kSteal_]);
    }

    return total;
  } else {

    return 0; 
  }
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string line, value;
  vector<string> jiffies;
  long total{0};
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  if (fileStream.is_open()) {
    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    while (lineStream >> value) {
      jiffies.push_back(value);
    }
    jiffies.erase(jiffies.begin());

    if (jiffies[kIdle_] != "") {
      total += std::stoi(jiffies[kIdle_]);
    }
    if (jiffies[kIOwait_] != "") {
      total += std::stoi(jiffies[kIOwait_]);
    }

    return total;

  } else {

    return 0; 
  }
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, value;
  vector<string> info;
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  if(fileStream.is_open()) {
    std::getline(fileStream, line);
    std::istringstream lineStream(line);
    while (lineStream >> value) {
      info.push_back(value);
    } 
    info.erase(info.begin());
  } else {

    return info; 
  }

  return info;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line, key;
  int value;
  int processes{0};
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  if(fileStream.is_open()) {
    while (getline(fileStream, line)) {
      std::istringstream lineStream(line);
      lineStream >> key >> value;
      if(key == "processes"){
        processes = value;
      }
    }
    
  } else {

    return processes;
  }

  return processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, procs;
  int value;
  int result{0};
  std::ifstream fileStream(kProcDirectory + kStatFilename);
  if(fileStream.is_open()) {
    while(std::getline(fileStream, line)) {
      std::istringstream lineStream(line);
      lineStream >> procs >> value;
      if(procs == "procs_running") {
        result = value;
      }
    }
  } else {

    return result;
  } 

  return result;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kCmdlineFilename );
  if (fileStream.is_open()) {
    string line;
    getline(fileStream, line);
    return line;
  } else {

    return string();
  }
 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line, key, unit;
  int value;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::istringstream lineStream(line);
      lineStream >> key >> value >> unit;
      if (key == "VmSize:") {
        value = value / 1000;
      }
    }

    return std::to_string(value) + "MB";
  } else { 
    
    return string();
  } 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
    string line, key, value, uid;
    std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatusFilename);
    if (fileStream.is_open()) {
      while (getline(fileStream, line))
      {
        std::istringstream lineStream(line);
        lineStream >> key >> value;
        if (key == "Uid:") {
          uid = value;
        }  
      }

      return uid;
    } else {

      return string();
    }
  }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line, user, x, fUid, sUid, value;
  string uid = LinuxParser::Uid(pid);
  std::ifstream fileStream(kPasswordPath); 
  if (fileStream.is_open()) {
    while (getline(fileStream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineStream(line);
      lineStream >> value >> x >> fUid >> sUid;
      if (fUid == uid || sUid == uid) {
        user = value;
      }
    }

    return user;
  } else {

    return string();
  }
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, value;
  vector<string> stats;
  long uptime;
  std::ifstream fileStream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (fileStream.is_open()) {
      while (getline(fileStream, line)) {
        std::istringstream lineStream(line);
        while (lineStream >> value) {
          stats.push_back(value);
        }
      }
      
      if (stats[21] != "") {
        uptime = std::stoi(stats[21]) / sysconf(_SC_CLK_TCK);
      }
      
      return uptime;
  } else {

    return 0;
  }
}