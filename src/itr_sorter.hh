#ifndef ITR_SORTER_HH
# define ITR_SORTER_HH

# include <math.h>
# include "image.hh"

class ItrSorter
{
public:
  ItrSorter(Image img);
  void print_neurons();
  void process();
  void learn();
  int find_BMU(int pos);
  int get_dist(int img_pixel, int neuron_pixel);
  int neur_int_value(int i);
  void propag(int pos, int pos_img_pixel);
  void to_ppm(const char* path);


private:
  Image img_;
  int good_dist_;
  char* neurons_;
};
#endif /* !ITR_SORTER_HH */
