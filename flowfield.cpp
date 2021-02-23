#include "flowfield.h"

constexpr double TWO_PI = 3.14159265358979323846;

flowField::flowField(int res, olc::PixelGameEngine* pge)
{
    // std::uint32_t seed = 1;
    const siv::PerlinNoise perlin();
    scl = res;
    
    width = pge->ScreenWidth();
    height = pge->ScreenHeight();
    cols = floor(width / res) + 1;
    rows = floor(height / res) + 1;

    for (int i = 0; i < cols * rows; i++) {
        olc::vf2d v = {0.0f, 0.0f};
        vectors.push_back(v);
    }
    
}

void flowField::update()
{
    float xoff = 0;
    for (int y = 0; y < rows; y++)
    {
        float yoff = 0;
        for (int x = 0; x < cols; x++)
        {
            float angle = ((2.0f * perlin.noise3D(xoff, yoff, zoff)) - 1.0f) * TWO_PI * 4;

            olc::vf2d v = { std::cos(angle), std::sin(angle) };
            
            int index = x + y * cols;
            vectors[index] = v.norm();

            xoff += inc;
        }
        yoff += inc;
    }
    zoff += 0.004;
}

void flowField::display(olc::PixelGameEngine *pge)
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            int index = x + y * cols;
            olc::vf2d v = vectors[index];

        }
    }
}