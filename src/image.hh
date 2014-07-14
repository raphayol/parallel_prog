#ifndef IMAGE_HH
# define IMAGE_HH

# include <iostream>
# include <fstream>
# include <cstdlib>
# include <climits>

class Image
{
public:
  Image(const char* path);
  void print_pixels();
  void to_ppm(const char* path);
  int get_width();
  int get_height();
  int get_int_value(int i);
//  int get_dist(int a, int b);

private:
  int width_;
  int height_;
  const char* path_;
  char* pixel_;
};
#endif /* !IMAGE_HH */
