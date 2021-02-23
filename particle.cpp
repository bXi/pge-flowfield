#include "particle.h"

particle::particle(olc::vf2d start, float maxspeed, olc::PixelGameEngine* pge)
{
    width = pge->ScreenWidth();
    height = pge->ScreenHeight();
    maxSpeed = maxspeed;
    pos = start;
    vel = olc::vf2d(0.0f, 0.0f);
    acc = olc::vf2d(0.0f, 0.0f);
    prevPos = pos;
}

void particle::run(olc::PixelGameEngine* pge)
{
    update();
    edges();
    show(pge);
}

void particle::update()
{
    pos += vel;
    olc::vf2d velNorm = vel.norm();

    vel = velNorm;
    vel += acc;
    acc *= 0;
}
void particle::applyForce(olc::vf2d force)
{
    acc.x += force.x * 100;
    acc.y += force.y * 100;
}

void particle::show(olc::PixelGameEngine *pge)
{
    //stroke(0, 5);
    //strokeWeight(1);
    pge->DrawLine(pos.x, pos.y, prevPos.x, prevPos.y, olc::BLACK);

    //point(pos.x, pos.y);
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
    int x = floor(pos.x / (flowfield.scl * flowfield.scl));
    int y = floor(pos.y / (flowfield.scl * flowfield.scl));
    int index = x + y * flowfield.cols;

    olc::vf2d force = flowfield.vectors[index];
    applyForce(force);
}
