#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <vector>
#include "flowfield.h"
#include "particle.h"

class appFlowField : public olc::PixelGameEngine
{
public:
	std::vector<particle> particles;
	flowField flowfield = flowField(10, this);

	appFlowField()
	{
		sAppName = "Flowfield";
	}

public:
	bool OnUserCreate() override
	{

		flowfield.update();

		for (int i = 0; i < 1000; i++)
		{
			olc::vf2d start = {(float)(std::rand() % ScreenWidth()), (float)(std::rand() % ScreenHeight())};
			particle p = particle(start, std::rand() % 6 + 2, this);
			particles.push_back(p);
		}

		Clear(olc::WHITE);
		

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		flowfield.update();

		for (auto p : particles)
		{
			p.follow(flowfield);
			p.run(this);
		}
		return true;
	}
};

int main()
{
	appFlowField app;
	if (app.Construct(1024, 960, 1, 1))
		app.Start();
	return 0;
}
