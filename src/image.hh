#ifndef IMAGE_HH
# define IMAGE_HH

# include <iostream>
# include <fstream>
# include <cstdlib>

class Image
{
public:
  Image(const char* path);
  void print_pixels();
  void to_ppm(const char* path);

private:
  int width_;
  int height_;
  const char* path_;
  char* pixel_;


};
#endif /* !IMAGE_HH */
