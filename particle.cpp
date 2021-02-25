#include "particle.h"
#include <math.h>

particle::particle() {

}

particle::particle(int x, int y, float maxspeed, olc::PixelGameEngine* pge)
{
    width = pge->ScreenWidth();
    height = pge->ScreenHeight();
    maxSpeed = maxspeed;
    pos = olc::vf2d(x, y);
    vel = olc::vf2d(3.0f, 0.0f);
    acc = olc::vf2d(0.0f, 0.0f);
    prevPos = olc::vf2d(pos.x, pos.y);
}

void particle::run(olc::PixelGameEngine* pge, flowField ff)
{

    float t = pge->GetElapsedTime();
    follow(ff);
    update(t);
    edges();
    //pge->DrawString(olc::vf2d(2.0f, 2.0f),  "pos.x: " + std::to_string(pos.x) + ", pos.y: " + std::to_string(pos.y), olc::BLACK);
    //pge->DrawString(olc::vf2d(2.0f, 10.0f), "vel.x: " + std::to_string(vel.x) + ", vel.y: " + std::to_string(vel.y), olc::BLACK);
    //pge->DrawString(olc::vf2d(2.0f, 18.0f), "acc.x: " + std::to_string(acc.x) + ", acc.y: " + std::to_string(acc.y), olc::BLACK);
    //pge->DrawString(olc::vf2d(2.0f, 26.0f), "prp.x: " + std::to_string(prevPos.x) + ", prp.y: " + std::to_string(prevPos.y), olc::BLACK);
    show(pge);
}

void particle::update(float t)
{
   
    pos += vel * t * 20;
    

    float w = sqrt(vel.x * vel.x + vel.y * vel.y);
    if (w > 0) {
        vel.x /= w;
        vel.y /= w;
    }

    

    //velNorm = vel.norm();
    vel *= maxSpeed;

    //vel = velNorm;
    vel += acc;
    
    acc *= 0;

}
void particle::applyForce(olc::vf2d force)
{
    acc += force;
}

void particle::show(olc::PixelGameEngine *pge)
{
    pge->DrawLine(pos, prevPos, olc::Pixel(0, 0, 0, 5));
    updatePreviousPos();
}
void particle::edges()
{
    if (pos.x > width)
    {
        pos.x = 0;
        updatePreviousPos();
    }
    if (pos.x < 0)
    {
        pos.x = width;
        updatePreviousPos();
    }
    if (pos.y > height)
    {
        pos.y = 0;
        updatePreviousPos();
    }
    if (pos.y < 0)
    {
        pos.y = height;
        updatePreviousPos();
    }
}
void particle::updatePreviousPos()
{
    prevPos.x = pos.x;
    prevPos.y = pos.y;
}
void particle::follow(flowField flowfield)
{
    int x = floor(pos.x / flowfield.scl);
    int y = floor(pos.y / flowfield.scl);
    int index = x + y * flowfield.cols;

    olc::vf2d force = flowfield.vectors[index];
    applyForce(force);
}
