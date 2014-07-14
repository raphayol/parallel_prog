#include <string>
#include "image.hh"

Image::Image(const char* path)
:path_(path)
{
  std::ifstream ifs(path);
  std::string str;
  std::getline(ifs, str);
  if (str != "P3")
  {
    std::cout << "Bad file format" << std::endl;
    exit(1);
  }

  std::getline(ifs, str);
  int space = str.find(' ');
  height_ = atoi((str.substr(0, space)).c_str());
  width_ = atoi((str.substr(space, '\n')).c_str());
  std::getline(ifs, str);
  if (str != "255")
  {
    std::cout << "Bad file format" << std::endl;
    exit(1);
  }

  pixel_ = new char[height_ * width_ * 3];
  int i = 0;
  while (ifs.good() && i < width_ * height_ * 3)
  {
    std::getline(ifs, str);
    int space1 = 0;
    int space2 = str.find(' ');
    int j = 0;
    while (j < width_ * 3 && i < 3 * width_ * height_)
    {
      j++;

      int c = atoi((str.substr(space1, space2)).c_str());
      pixel_[i++] = (char)c;
           space1 = space2 + 1;
      space2 = str.find(' ', space1);
    }
  }
  ifs.close();
}

void Image::print_pixels()
{
  int i = 0;
  while (i < width_ * height_ * 3)
  {
    if ((int)pixel_[i] < 0)
    {
      std::cout << 256 + (int)pixel_[i] << " "; 
    }
    else
    {
      std::cout << (int)pixel_[i] << " ";
    }
    i++;
    if (i % (width_ * 3) == 0)
      std::cout << std::endl;
  }
}

void Image::to_ppm(const char* path)
{
  std::ofstream of;
  of.open(path);
  of << "P3\n";
  of << height_ << " " << width_ << " " << std::endl;
  of << "255" << std::endl;
  int i = 0;
  while (i < width_ * height_ * 3)
  {
    if ((int)pixel_[i] < 0)
    {
      of << 256 + (int)pixel_[i] << " "; 
    }
    else
    {
      of << (int)pixel_[i] << " ";
    }
    i++;
    if (i % (width_ * 3) == 0)
      of << std::endl;
  }
}

int Image::get_width()
{
  return width_;
}

int Image::get_height()
{
  return height_;
}

int Image::get_int_value(int i)
{
  if (pixel_[i] < 0)
    return (255 + pixel_[i]);
  return pixel_[i];
}


