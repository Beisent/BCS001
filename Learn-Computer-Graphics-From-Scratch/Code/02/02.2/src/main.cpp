#include <iostream>
#include <string>
#include <fstream>

static const int width = 256;
static const int height = 256;
int size = width * height;

int *r = new int[size];
int *g = new int[size];
int *b = new int[size];

void SetPixel(int x, int y, int ColorR, int ColorG, int ColorB)
{
    int index = x + y * width;
    r[index] = ColorR;
    g[index] = ColorG;
    b[index] = ColorB;
}

bool Render(std::string filename)
{
    std::ofstream f(filename);
    if (!f)
    {
        std::cerr << "Error: Cannot open file for writing." << std::endl;
        return false;
    }

    f << "P3\n"
      << width << ' ' << height << "\n255\n";
    for (int i = 0; i < size; ++i)
    {
        f << r[i] << ' ' << g[i] << ' ' << b[i] << ' ';
    }
    f << '\n';

    std::cout << "PPM image written to output.ppm" << std::endl;
    return true;
}

void BresenhamLine(int x0, int y0, int x1, int y1, int R, int G, int B)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    int d = 2 * dy - dx;   
    int y = y0;

    for (int x = x0; x <= x1; x++)
    {
        SetPixel(x, y, R, G, B);

        if (d > 0)
        {
            y += 1;
            d -= 2 * dx;
        }

        d += 2 * dy;
    }
}
int main()
{

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            SetPixel(x, y, 0, 0, 0);
        }
    }
    BresenhamLine(0, 0, 100, 49, 255, 0, 0);
    Render("output.ppm");

    delete[] r;
    delete[] g;
    delete[] b;
    return 0;
}