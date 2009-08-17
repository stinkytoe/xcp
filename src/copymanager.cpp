#include "xcp.hpp"

void CopyManager::copy()
{
  _display.before(_desc, _copier.length(), _copier.offset());
  
  while( !_copier.done() ) {
    _copier.step();
    _display.step(_desc, _copier.length(), _copier.offset());
  }      
  
  _display.after(_desc, _copier.length(), _copier.offset());
}
