#ifndef XCP_HPP
#define XCP_HPP

#include <iostream>
#include <fstream>
#include <string>

struct CopyDescriptor
{
  std::string src;
  std::string dest;
};

#include "copier.hpp"
#include "display.hpp"
#include "copymanager.hpp"
#include "queuemanager.hpp"
#include "util.hpp"

#endif//XCP_HPP
