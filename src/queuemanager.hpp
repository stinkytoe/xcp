#ifndef QUEUEMANAGER_HPP
#define QUEUEMANAGER_HPP

#include "xcp.hpp"

#include <list>
class QueueManager
{
private:
  typedef std::list<CopyDescriptor> CopiesList;
  CopiesList _copies_list;

public:
  void add(const CopyDescriptor desc)
  {
    _copies_list.push_back(desc);
  }

  void process();
};

#endif//QUEUEMANAGER_HPP
