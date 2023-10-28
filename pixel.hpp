#pragma once

#include <cstdint>
#include <ostream>

class PixelDouble {
public:
    PixelDouble();
    PixelDouble(double red, double green, double blue);
    PixelDouble(uint8_t red, uint8_t green, uint8_t blue);

    void SetRed(double red);
    void SetGreen(double green);
    void SetBlue(double blue);

    double GetRed() const;
    double GetGreen() const;
    double GetBlue() const;

    static uint8_t DoubleToUInt8T(double brightness);

    friend std::ostream& operator<<(std::ostream& os, const PixelDouble& pixel);

private:
    double red_;
    double green_;
    double blue_;
};
