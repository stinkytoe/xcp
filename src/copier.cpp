#include "xcp.hpp"


void Copier::step()
{
  if(_done) //should we signal an error here or not?
    return;
  
  char buffer[_block_size];
  //_src_offset = _src.tellg();
  unsigned bytes_left = _src_length - _src_offset;
  unsigned this_block_size = (bytes_left < _block_size)? bytes_left : _block_size;
  
  _src.read(buffer, this_block_size);
  _dest.write(buffer, this_block_size);
  
  _src_offset += this_block_size;
  
  if( _src_offset == _src_length )
    _done = true;
  
}
