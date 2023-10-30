#include "negative.hpp"

Negative::Negative()
    : ChangePixels([](const Pixel& pixel) {
          return Pixel(static_cast<Pixel::Channel>(1) - pixel.GetRed(),
                       static_cast<Pixel::Channel>(1) - pixel.GetGreen(),
                       static_cast<Pixel::Channel>(1) - pixel.GetBlue());
      }) {
}
