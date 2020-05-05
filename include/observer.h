#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <condition_variable>
#include <memory>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>

class observer
{
public:
  virtual void update(std::vector<std::string>& v) = 0;
  virtual std::string stop() = 0;
};

class handler
{
private:
  std::vector<std::shared_ptr<observer>> view;
  std::atomic_uint line{0};
  std::atomic_uint command{0};
  std::atomic_uint block{0};
public:
  handler(){}
  ~handler();
  void subscribe(std::shared_ptr<observer> obs);
  void push(std::string& str, std::vector<std::string>& v, std::string& _time);
  std::string getTime();
  void line_count();
  void show(std::vector<std::string>& v, std::string& _time);
};