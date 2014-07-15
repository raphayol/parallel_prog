#include "itr_sorter.hh"
#include "tbb/tbb.h"

ItrSorter::ItrSorter(Image img)
:img_(img)
{
  neurons_ = new char [img.get_width() * img.get_height() * 3];
  int i = 0;
  srand(time(0));
  while (i < img.get_width() * img.get_height() * 3)
  {
    neurons_[i] = img.get_int_value(i);
    i++;
  }
  good_dist_ =/* (img.get_width() + 
                 img.get_height()) / */ 4;
}

void ItrSorter::print_neurons()
{
  int i = 0;
  while (i < img_.get_width() * img_.get_height() * 3)
  {
    if ((int) neurons_[i] < 0)
      std::cout << 255 + (int) neurons_[i++] << " ";
    else
      std::cout << (int) neurons_[i++] << " ";
    if (i % (img_.get_width() * 3) == 0)
      std::cout << std::endl;
  }
}

void ItrSorter::sort_column(int nb_col)
{
  int dist_min = INT_MAX;
  int min = 0;
  int height = img_.get_height();
  int width = img_.get_width();
  for (int i = 0; i < height - 1; ++i)
  {
    int act = nb_col * 3 + i * width * 3;
    for (int j = i + 1; j < height; ++j)
    {
      int act2 = nb_col * 3 + j * width * 3;
      /*std::cout << act << " " << act2 << std::endl;
        std::cout << "r:" << neur_int_value(act) << " " << neur_int_value(act2) << std::endl;
        std::cout << "g:" << neur_int_value(act + 1) << " " << neur_int_value(act2 + 1) << std::endl;
        std::cout << "b:" << neur_int_value(act + 2) << " " << neur_int_value(act2 + 2) << std::endl;
        std::cout << "dist " << act / 3 << " " << act2 / 3 << " = " << dist << std::endl << std::endl;*/
      int dist = get_dist2(act, act2);
      if (dist < dist_min)
      {
        min = act2;
        dist_min = dist;
      }
    }
    if (act + width * 3 != min)
      swap(act + width * 3, min);
  }
}


void ItrSorter::sort_line(int nb_line)
{
  int dist_min = INT_MAX;
  int min = 0;
  int width = img_.get_width();
  for (int i = 0; i < width - 1; ++i)
  {
    int act = nb_line * width * 3 + 3 * i;
    for (int j = i + 1; j < width; ++j)
    {
      int act2 = nb_line * width * 3 + 3 * j;
      /*      std::cout << act << " " << act2 << std::endl;
              std::cout << "r:" << neur_int_value(act) << " " << neur_int_value(act2) << std::endl;
              std::cout << "g:" << neur_int_value(act + 1) << " " << neur_int_value(act2 + 1) << std::endl;
              std::cout << "b:" << neur_int_value(act + 2) << " " << neur_int_value(act2 + 2) << std::endl;
              std::cout << "dist " << act / 3 << " " << act2 / 3 << " = " << dist << std::endl << std::endl;*/
      int dist = get_dist2(act, act2);
      if (dist < dist_min)
      {
        min = act2;
        dist_min = dist;
      }
    }
    if (act + 3 != min)
      swap(act + 3, min);
  }
}

int ItrSorter::get_dist2(int act, int neuron_pixel)
{
  int r1 = neur_int_value(act);
  int g1 = neur_int_value(act + 1);
  int b1 = neur_int_value(act + 2);
  int r2 = neur_int_value(neuron_pixel);
  int g2 = neur_int_value(neuron_pixel + 2);
  int b2 = neur_int_value(neuron_pixel + 3);
  /*  std::cout << act << " " << neuron_pixel << "ar"  << std::endl;
      std::cout << "r: " << r1 << "-" << r2 << "= " << r1 - r2 << std::endl
      << "g: " << g1 << "-" << g2 << "= " << g1 - g2 << std::endl
      << "b: " << b1 << "-" << b2 << "= " << b1 - b2 << std::endl;*/
  return sqrt(pow(r1 - r2, 2) + 
              pow(g1 - g2, 2) + 
              pow(b1 - b2, 2));
}


void ItrSorter::swap(int a, int c)
{
  char r = (char) neur_int_value(a);
  char g = (char) neur_int_value(a + 1);
  char b = (char) neur_int_value(a + 2);

  neurons_[a] = (char) neur_int_value(c);
  neurons_[a + 1] = (char) neur_int_value(c + 1);
  neurons_[a + 2] = (char) neur_int_value(c + 2);

  neurons_[c] = r;
  neurons_[c + 1] = g;
  neurons_[c + 2] = b;

  //  std::cout << "swap: " << a << ", " << c << std::endl;
}

void ItrSorter::process2()
{
  int i = 0;
  while (i++ < NB_PROCESS)
  {
    for (int j = 0; j < img_.get_height(); j++)
      sort_line(j);

    for (int t = 0; t < img_.get_width(); t++)
      sort_column(t);

  }
}
/*
void ItrSorter::operator()(const blocked_range<size_t>& r) const
{
  for(size_t i=r.begin(); i!=r.end(); ++i); 
    sort_line(i);

  for(size_t j=r.begin(); j!=r.end(); ++j) 
    sort_column(j);
}
*/

void ItrSorter::testy(int i) const
{
  std::cout << i << std::endl;
}

void ItrSorter::process()
{
  int i = 0;
  while (i++ < 1)
    learn();
}

void ItrSorter::learn()
{
  int i = 0;
  while (i < img_.get_width() * img_.get_height() * 3)
  {
    int bmu = find_BMU(i);
    propag(bmu, i);
    i += 3;
  }
}

/*static int vabs(int i)
  {
  return (i < 0 ? -i : i);
  }*/


void ItrSorter::propag(int pos, int pos_img_pixel)
{
  for (int i = -2; i < 3; ++i)
    for (int j = pos - 6; j < pos + 9; j += 3)
    {
      int act = j + (i * img_.get_width() * 3);
      if (act > 0 && act < img_.get_width() * img_.get_height() * 3 - 2)
      {
        pos_img_pixel = pos_img_pixel;
        int dist = sqrt(pow((pos - j) / 3, 2) + pow(i, 2)) + 1;
        //std::cout << (int) img_.get_int_value(pos_img_pixel) << std::endl;
        neurons_[act] = (char)compute_modiff(neur_int_value(act), dist, pos_img_pixel);
        neurons_[act + 1] = (char)compute_modiff(neur_int_value(act + 1), dist, pos_img_pixel + 1);
        neurons_[act + 2] = (char)compute_modiff(neur_int_value(act + 2), dist, pos_img_pixel + 2);
      }
    }
}

int ItrSorter::compute_modiff(int act_color, int dist, int pos_img_pixel)
{
  int ret = act_color + 0.1 * exp(-pow(dist, 2) / 16) * (img_.get_int_value(pos_img_pixel) - act_color);
  //int ret = act_color + (0.2 * (img_.get_int_value(pos_img_pixel) - act_color));
  dist = dist;
  return ret;
}

int ItrSorter::find_BMU(int image_pixel)
{
  int i = 0;
  int dist_min = INT_MAX;
  int min = 0;
  while (i < img_.get_width() * img_.get_height() * 3)
  {
    int dist = get_dist(image_pixel, i);
    if (dist < dist_min)
    {
      min = i;
      dist_min = dist;
    }
    i += 3;
  }
  return min;
}

int ItrSorter::neur_int_value(int i)
{
  if (neurons_[i] < 0)
    return (255 + neurons_[i]);
  return neurons_[i];
}


int ItrSorter::get_dist(int img_pixel, int neuron_pixel)
{
  int r1 = img_.get_int_value(img_pixel);
  int g1 = img_.get_int_value(img_pixel + 1);
  int b1 = img_.get_int_value(img_pixel + 2);
  int r2 = neurons_[neuron_pixel];
  int g2 = neurons_[neuron_pixel + 2];
  int b2 = neurons_[neuron_pixel + 3];
  std::cout << img_pixel << " " << neuron_pixel<< " " 
    << "r: " << r1 << "-" << r2 << "= " << r1 - r2 << std::endl
    << "g: " << g1 << "-" << g2 << "= " << g1 - g2 << std::endl
    << "b: " << b1 << "-" << b2 << "= " << b1 - b2 << std::endl;
  return sqrt(pow(r1 - r2, 2) + 
              pow(g1 - g2, 2) + 
              pow(b1 - b2, 2));
}

void ItrSorter::to_ppm(const char* path)
{
  std::ofstream of;
  of.open(path);
  of << "P3\n";
  of << img_.get_height() << " " << img_.get_width() << " " << std::endl;
  of << "255" << std::endl;
  int i = 0;
  while (i < img_.get_width() * img_.get_height() * 3)
  {
    if ((int)neurons_[i] < 0)
    {
      of << 256 + (int)neurons_[i] << " "; 
    }
    else
    {
      of << (int)neurons_[i] << " ";
    }
    i++;
    if (i % (img_.get_width() * 3) == 0)
      of << std::endl;
  }
}
