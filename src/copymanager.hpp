#ifndef COPYMANAGER_HPP
#define COPYMANAGER_HPP

#include "xcp.hpp"

class CopyManager
{
private:
  CopyDescriptor _desc;

  Copier _copier;
  
  Display& _display;

  
public:
  CopyManager(CopyDescriptor desc, unsigned block_size, Display& display)
    : _desc(desc), _copier(desc, block_size), _display(display)
  {
  }
  
  void copy();
};


#endif//COPYMANAGER_HPP
