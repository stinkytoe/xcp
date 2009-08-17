#ifndef COPIER_HPP
#define COPIER_HPP

class Copier
{
private:
  // parameters
  CopyDescriptor _desc;
  unsigned _block_size;
 
  //internal variables
  bool _done;
  unsigned _src_length;
  unsigned _src_offset;
  std::ifstream _src;
  std::ofstream _dest;

public:
  Copier(CopyDescriptor desc,	 
	 unsigned block_size)
    : _desc(desc),
      _src(_desc.src.c_str()),
      _dest(_desc.dest.c_str()),
      _block_size(block_size)
  {
    _done = false;
  
    // get length of the source file
    _src.seekg (0, std::ios::end);
    _src_length = _src.tellg();
    _src.seekg (0, std::ios::beg);    
    _src_offset = 0;

    if(_src_length == 0)
      _done = true;

    if(!_src.good())
      throw "Unable to open source file!";

    if(!_dest.good())
      throw "Unable to open dest file!";
  }

  void step();

  bool done()
  {
    return _done;
  }

  unsigned length()
  {
    return _src_length;
  }

  unsigned offset()
  {
    return _src_offset;
  }
};

#endif//COPIER_HPP
