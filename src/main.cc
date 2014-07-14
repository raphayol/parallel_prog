#include "main.hh"

int main()
{
  Image img("img.ppm");
  ItrSorter itr(img);
  itr.process();
  itr.to_ppm("final.ppm");
//  itr.print_neurons();
}
