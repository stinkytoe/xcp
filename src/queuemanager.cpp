#include "xcp.hpp"

void QueueManager::process()
{
  ProgressDisplay d; //!!!!!!!!!!!!
  for(CopiesList::iterator iter=_copies_list.begin(); 
      iter!=_copies_list.end(); 
      iter++)
    CopyManager(*iter,1024*32,d).copy();
}
