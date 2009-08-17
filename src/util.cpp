#include "xcp.hpp"


#ifdef __linux__

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

std::string get_file_part(const std::string path)
{
  unsigned last_slash = path.find_last_of('/');
  return path.substr(last_slash+1);
}

bool is_directory(const std::string path)
{
  struct stat sb;
  if(stat(path.c_str(),&sb))
    throw "Unable to stat directory!";
  
  //the ()? operator is probably redundant, but i want to emphasize the
  //c to c++ barrier. remove if we are sure it's all good.
  return ( S_ISDIR(sb.st_mode) )? true : false;
}
  
bool is_file(const std::string path)
{
  struct stat sb;
  if(stat(path.c_str(),&sb))
    throw "Unable to stat directory!";
  
  //the ()? operator is probably redundant, but i want to emphasize the
  //c to c++ barrier. remove if we are sure it's all good.
  return ( S_ISREG(sb.st_mode) )? true : false;
}
  
std::string append_file_to_path(const std::string path, const std::string file)
{
  if( path[ path.size()-1 ] == '/' )
    return path + file;
  else
    return path + '/' + file;
}

#include <sstream>

std::string make_human_readable(long long unsigned number)
{
  const char* escalations = "\0kMGTP";
  unsigned escalated = 0;
  long long unsigned remainder = number;
  long long unsigned modulo = 0;
  std::ostringstream out;

  for(int cnt=0; cnt<5; cnt++) {
    if(remainder < 1024)
      break;
    
    modulo = remainder % 1024;
    remainder = remainder / 1024;
    escalated++; }
  
  int decimal_portion = (int)( 10.0*modulo/1024.0 );  

  out << remainder;  
  if(decimal_portion!=0) out << '.' << decimal_portion;
  if(escalated) out << escalations[escalated];
 
  return out.str();
}

#else 
#error "Need support for this system!"
#endif
