#include "main.hh"

int main()
{
  Image img("img.ppm");
  ItrSorter itr(img);
  itr.process2();
  itr.to_ppm("final.ppm");
  
  parallel_for(blocked_range<size_t>(0, NB_PROCESS), ItrSorter(img));
//  itr.print_neurons();
}
