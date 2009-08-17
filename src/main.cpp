#include "xcp.hpp"


#include <list>
#include <string>

typedef std::list<std::string> param_list;


param_list make_param_list(int nargs, char** args)
{
  param_list params;
  for(int cnt=0; cnt<nargs; cnt++)
    params.push_back(std::string(args[cnt]));
  
  return params;
}

void parse_param_list(param_list params)
{
  //let's get the call name to start
  std::string call_path = params.front();
  params.pop_front();
  
  //now let's get just the file name.
  //strip after the last /, if there is one.
  //i'l need this later when we will assume
  //that if the call name is 'xmv', that
  //we want to move instead of copy
  // unsigned last_slash = call_path.find_last_of('/');
  // std::string call_name = call_path.substr(last_slash+1);
  std::string call_name = get_file_part(call_path);

  //now let's find the first element in params 
  //which does not start with a -
  //indicating the start of the file arguments.
  //after this block, params will only contain the
  //switches, and files will contain the filenames
  param_list::iterator files_start = params.begin();
  for(;;) 
    if( files_start == params.end() )
      //possibly report the error here? there should be
      //at least 2 file names, but if we get here, there
      //weren't any.
      break; 
    else if( (*files_start)[0] != '-' )
      break; //we have a winner!
    else
      files_start++;
  param_list files;
  files.splice(files.begin(), params, files_start, params.end());

  QueueManager qm;
  
  //now let's process switches
  //we don't have any, so any switch is an error!
  for(param_list::iterator iter = params.begin();
      iter != params.end();
      iter++)
    throw "No flags recognized yet!";

  //there better be at least a src and dest, or 
  //a list of sources and a dest dir.
  if(files.size() < 2)
    throw "Need at least 2 args!";
  else if(files.size() == 2) {
    CopyDescriptor desc;
    desc.src = files.front().c_str();
    desc.dest = files.back().c_str();
    if(!is_file(desc.src))
      throw "Source file no good!";
    if(!is_file(desc.dest))
      throw "Destination file no good!";
    qm.add(desc);
  }
  else {
    //let's get the dest dir out of the list
    //and make sure it's good.
    std::string dest_dir = files.back();
    files.pop_back();
    if(!is_directory(dest_dir))
      throw "Destination not a directory";
    
    //ok. now let's populate the queue manager.
    for(param_list::iterator iter = files.begin();
	iter != files.end();
	iter++)
      {
	if(is_directory(*iter))
	  throw "Source file is a directory!";
	
	std::string file_part = get_file_part(*iter);
	std::string this_dest = append_file_to_path(dest_dir,file_part);
	CopyDescriptor desc;
	desc.src = iter->c_str();
	desc.dest = this_dest.c_str();
	
	//this test needs improvement!!!!!!!!!!!!!!!
	//are they the same file?
	if( desc.src == desc.dest ) 
	  throw "Dest and src same file!";
	
	qm.add(desc);
      }
  }
  
  qm.process();
}
#include <popt.h>
#include <stdio.h>

void usage(poptContext optCon, int exitcode, char *error, char *addl) {
  poptPrintUsage(optCon, stderr, 0);
  if (error) fprintf(stderr, "%s: %s", error, addl);
  throw exitcode;
}

typedef std::list<std::string> SourcesList;

struct Arguments
{
  bool recursive;
  bool no_clobber;
  SourcesList sources;
  std::string destination;
};

Arguments parse_args(int argc, const char** argv)
{
  //must be int due to the weirdness of the
  //c/c++ barrier. just treat and use like a bool.
  int recursive=false;
  int no_clobber=false;
  
  struct poptOption optionsTable[] = {
    { "recursive", 'r', 0, &recursive, 0,
      "Copy directories recursively", NULL },
    { "no-clobber", 'n', 0, &no_clobber, 0,
      "Do not overwrite an existing file", NULL },
    POPT_AUTOHELP
    { NULL, 0, NULL, 0, 0 }
  };

  poptContext optCon = poptGetContext(NULL, argc, argv, optionsTable, 0);
  poptSetOtherOptionHelp(optCon, "[OPTIONS] [SOURCE]* [DEST]");

  //this line for options which aren't automatically handled
  //we still need to cycle through all the opts, however.
  char opt;
  while( (opt=poptGetNextOpt(optCon)) >= 0 ) {}
  
  // TODO: add error checking here for popt

  SourcesList sources;
  
  //sometimes it's amazing how well c and c++
  //work together. other times it's insane.
  //i'm not sure which this one is.
  const char** arguments = poptGetArgs(optCon);
  
  if(arguments == NULL)
    throw "Need args!";
  
  while(*arguments != NULL)
    {
      sources.push_back( *arguments );
      ++arguments;
    }
  
  if( sources.size() < 2 )
    throw "need at least 2 args!";
  
  std::string destination = sources.back();
  sources.pop_back();
  
  Arguments args = { recursive, no_clobber, sources, destination };
  
  //poptFreeContext(optCon);

  return args;
  
  // std::cout << "Currently we " << ((recursive)? "are":"are not") << " recursive: " << recursive << std::endl;
  // std::cout << "Currently we " << ((no_clobber)? "are":"are not") << " no-clobber: " << no_clobber << std::endl;

  
}

int main(int argc, const char** argv)
{
  
  try {
  //   param_list params = make_param_list(nargs,args);
  //   parse_param_list(params); 
    Arguments args = parse_args(argc, argv);
    std::cout << args.sources.front() << " " << args.destination << std::endl;
  } 
  catch(const char* error) {
    std::cout << "const char* caught!: " << error << std::endl; 
  }
  
  //std::cout << make_human_readable(1024ll*1024ll*1024*1024*(1024 + 1024)) << std::endl;

  return 0;
}
