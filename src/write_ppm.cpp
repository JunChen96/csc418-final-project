#include "write_ppm.h"
#include <fstream>
#include <cassert>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::ofstream file;
  file.open(filename);
  if (!file) {
    return false;
  }

  file<<"P3"<<"\n";
  file<<std::to_string(width)<<" ";
  file<<std::to_string(height)<<"\n";
  file<<"255"<<"\n";

  int index = 0;

  for (int i=0; i<width*height; i++) {
    if (num_channels == 3) {
      file<<std::to_string(data[index++])<<" ";
      file<<std::to_string(data[index++])<<" ";
      file<<std::to_string(data[index++])<<"\n";
    } else {
      unsigned char gray = data[index++];
      file<<std::to_string(gray)<<" ";
      file<<std::to_string(gray)<<" ";;
      file<<std::to_string(gray)<<"\n";
    }
  }

  file.close();
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
