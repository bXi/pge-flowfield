#pragma once
#include <vector>

#include "perlin.h"
#include "olcPixelGameEngine.h"

class flowField
{
public:
    std::vector<olc::vf2d> vectors;
    int cols, rows;
    float inc = 0.1;
    float zoff = 0;
    int scl;
    int width, height;

    siv::PerlinNoise perlin;   



    flowField(int res, olc::PixelGameEngine* pge);

    void update();
    void display(olc::PixelGameEngine* pge);
};
