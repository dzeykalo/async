
#include "observer.h"

  handler::~handler()
  {
    std::stringstream ss;
    ss << "main thread - " << line << " receive, " << block << " block, " << command << " command" << std::endl;
    for (auto &s : view)
      ss << s->stop();
    std::cout << ss.str();
  }

  void handler::subscribe(std::shared_ptr<observer> obs) {
    view.push_back(obs);
  }
  void handler::push(std::string& str, std::vector<std::string>& v, std::string& _time)
  {
    if (v.empty())
      _time = getTime();
    if (!str.empty())
      v.push_back(str);
    str.clear();
  }
  std::string handler::getTime(){
    std::time_t tim = std::time(nullptr); 
    return std::to_string(tim);
  }
  void handler::line_count(){ ++line; }

  void handler::show(std::vector<std::string>& v, std::string& _time)
  {
    if (!v.empty())
    {
      command += v.size();
      ++block;
      v.push_back(_time);
      for (auto &s : view)
      {
        s->update(v);
      }
      v.clear();
    }      
  }
