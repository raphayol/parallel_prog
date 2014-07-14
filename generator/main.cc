#include "main.hh"

void create_ppm_file(const char* pathname, int width, int height)
{
  std::ofstream of;
  of.open(pathname);
  of << "P3\n";
  of << height << " " << width << " " << std::endl;
  of << "255\n";
  srand(time(0));
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
      of << rand() % 255 << " " << rand() % 255 << " " << rand() % 255 << " ";
    of << "\n";
  }
}


int main()
{
  create_ppm_file(std::string("img.ppm").c_str(), 25, 25);
}
