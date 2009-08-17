#ifndef DISPLAY_HPP
#define DISPLAY_HPP

class Display
{
public:
  virtual void before(const CopyDescriptor desc, const unsigned length, const unsigned offset) = 0;
  virtual void step(const CopyDescriptor desc, const unsigned length, const unsigned offset) {};
  virtual void after(const CopyDescriptor desc, const unsigned length, const unsigned offset) {};
};

class NullDisplay : public Display
{
public:
  void before(const CopyDescriptor desc, const unsigned length, const unsigned offset) {}
  void step(const CopyDescriptor desc, const unsigned length, const unsigned offset) {}
  void after(const CopyDescriptor desc, const unsigned length, const unsigned offset) {}
};

class SimpleDisplay : public Display
{
public:
  void before(const CopyDescriptor desc, const unsigned length, const unsigned offset);
  void step(const CopyDescriptor desc, const unsigned length, const unsigned offset);
  void after(const CopyDescriptor desc, const unsigned length, const unsigned offset);
};

class ProgressDisplay : public Display
{
private:
  unsigned _line_length;
public:
  ProgressDisplay(unsigned line_length=100) : _line_length(line_length) {}
  void before(const CopyDescriptor desc, const unsigned length, const unsigned offset);
  void step(const CopyDescriptor desc, const unsigned length, const unsigned offset);
  void after(const CopyDescriptor desc, const unsigned length, const unsigned offset);
};



#endif//DISPLAY_HPP
