#include "xcp.hpp"

void SimpleDisplay::before(const CopyDescriptor desc, const unsigned length, const unsigned offset)
{
  std::cout << "Starting copy: \"" << desc.src
	    << "\" -> \"" << desc.dest << "\"" << std::endl;
  
}

void SimpleDisplay::step(const CopyDescriptor desc, const unsigned length, const unsigned offset)
{
  std::cout << "length: " << length 
	    << " offset: " << offset
    //<< " percent: %" << ((long long)offset*100LL) / (long long)length 
	    << std::endl;
}

void SimpleDisplay::after(const CopyDescriptor desc, const unsigned length, const unsigned offset)
{
  std::cout << "Copy Complete!" << std::endl;    
}

void ProgressDisplay::before(const CopyDescriptor desc, const unsigned length, const unsigned offset) 
{
  std::cout << "Starting copy: \"" << desc.src
	    << "\" -> \"" << desc.dest << "\"" << std::endl;
}
  
void ProgressDisplay::step(const CopyDescriptor desc, const unsigned length, const unsigned offset) 
{
  const unsigned line_length = (_line_length > 10)? _line_length-6 : 10;
  unsigned percent = ((long long)offset*100LL) / (long long)length;
  unsigned num_hashes = ((long long)percent*(long long)line_length) / 100LL;
  unsigned num_dots = line_length - num_hashes;

  std::cout << "\r[";
  for(int cnt=0; cnt<num_hashes; cnt++)
    std::cout << '#';
  for(int cnt=0; cnt<num_dots; cnt++)
    std::cout << '.';
  std::cout << "] %" << percent;
}
  
void ProgressDisplay::after(const CopyDescriptor desc, const unsigned length, const unsigned offset) 
{
  std::cout << std::endl << "Copy Complete!" << std::endl;    
}
