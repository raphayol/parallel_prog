#include "itr_sorter.hh"

ItrSorter::ItrSorter(Image img)
:img_(img)
{
  neurons_ = new char [img.get_width() * img.get_height() * 3];
  int i = 0;
  srand(time(0));
  while (i < img.get_width() * img.get_height() * 3)
  {
    neurons_[i++] = rand() % 255;
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

void ItrSorter::process()
{
  int i = 0;
  while (i++ < 100)
    learn();
}

void ItrSorter::learn()
{
  int i = 0;
  while (i < img_.get_width() * img_.get_height() * 3)
  {
    int bmu = find_BMU(i);
    bmu = bmu;
    propag(bmu, i);
    /* LEARN TODO */
    i += 3;
  }
}

static int vabs(int i)
{
  return (i < 0 ? -i : i);
}

void ItrSorter::propag(int pos, int pos_img_pixel)
{
  int z = pos_img_pixel;
  pos_img_pixel = z;
  for (int i = -(good_dist_ / 2); i < (good_dist_ / 2) + 1; ++i)
    for (int j = pos - 1 - (good_dist_ / 2) * 3; j < pos + (good_dist_ / 2 + 1) * 3; j += 3)
    {
      int act = j + (i * img_.get_width() * 3);
      if (act > 0 && act < img_.get_width() * img_.get_height() * 3 - 2)
      {
        neurons_[act] = (char) img_.get_int_value(pos_img_pixel);
        neurons_[act + 1] = (char) img_.get_int_value(pos_img_pixel + 1);
        neurons_[act + 2] = (char) img_.get_int_value(pos_img_pixel + 2);
      }
    }
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
