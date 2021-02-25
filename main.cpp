#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <vector>
#include "flowfield.h"
#include "particle.h"

#define WIDTH 1920
#define HEIGHT 1080
#define PIXELSIZE 1
#define PARTICLES 2000

class appFlowField : public olc::PixelGameEngine
{
private:
	//mutable std::vector<particle> particles;
	particle particles[PARTICLES];

	flowField flowfield = flowField(10, this);

public:
	appFlowField()
	{
		sAppName = "Flowfield";
	}


public: 
	bool OnUserCreate() override
	{
		flowfield = flowField(15, this);

		flowfield.update();

		for (int i = 0; i < PARTICLES; i++)
		{
			int x = std::rand() % ScreenWidth();
			int y = std::rand() % ScreenHeight();
			particle p = particle(x, y, std::rand() % 20 + 4, this);
			particles[i] = p;
		}

		Clear(olc::WHITE);
		
		SetPixelMode(olc::Pixel::ALPHA);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		flowfield.update();

		//flowfield.display(this);
		//SetPixelMode(olc::Pixel::ALPHA);
		for (int i = 0; i < PARTICLES; i++) {
			particles[i].run(this, flowfield);
		}
		//SetPixelMode(olc::Pixel::NORMAL);
		//DrawRect(0, 0, WIDTH, HEIGHT, olc::Pixel(255, 0, 255));
		return true;
	}
};

int main()
{
	appFlowField app;
	if (app.Construct(WIDTH, HEIGHT, PIXELSIZE, PIXELSIZE))
		app.Start();
	return 0;
}
