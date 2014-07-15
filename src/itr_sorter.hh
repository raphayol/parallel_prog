#ifndef ITR_SORTER_HH
# define ITR_SORTER_HH

# include <math.h>
# include "image.hh"
# include "tbb/tbb.h"

# define NB_PROCESS 100

using namespace tbb;

class ItrSorter
{
public:
  ItrSorter(Image img);
  void print_neurons();
  void process();
  void process2();
  void learn();
  int find_BMU(int pos);
  int get_dist(int img_pixel, int neuron_pixel);
  int get_dist2(int img_pixel, int neuron_pixel);
  int neur_int_value(int i);
  void propag(int pos, int pos_img_pixel);
  void to_ppm(const char* path);
  int compute_modiff(int act_color, int dist, int pos_img_pixel);

  void sort_line(int nb_line);
  void sort_column(int nb_col);
  void swap(int a, int b);

  void testy(int i) const;
  void parallele_process();
  void operator()(const blocked_range<size_t>& r) const
  {
    for(size_t i=r.begin(); i!=r.end(); ++i)
      testy(i); 
//      Foo(a[i]);
  }

private:
  Image img_;
  int good_dist_;
  char* neurons_;
};
#endif /* !ITR_SORTER_HH */
