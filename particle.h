#pragma once

#include "olcPixelGameEngine.h"
#include "flowfield.h"

class particle
{
public:
    olc::vf2d pos;
    olc::vf2d vel;
    olc::vf2d acc;
    olc::vf2d prevPos;
    float maxSpeed;
    int width, height;

    particle(olc::vf2d start, float maxspeed, olc::PixelGameEngine* pge);

    void run(olc::PixelGameEngine* pge);
    void update();

    void applyForce(olc::vf2d force);

    void show(olc::PixelGameEngine *pge);

    void edges();
    void updatePreviousPos();

    void follow(flowField flowfield);
};
