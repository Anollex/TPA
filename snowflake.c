#include <stdio.h>
#include <math.h>

typedef struct
{
    double x, y;
} coordinates;

void drawline(coordinates c0, coordinates c1)
{
    printf("M %.1f %.1f ", c0.x, c0.y);	// move to origin of figure
    printf("l %.1f %.1f ", c1.x - c0.x, c1.y - c0.y);
}

coordinates rotatie(double x0, double y0, double x, double y, double ang)
{
    int dx = x - x0, dy = y - y0;
    coordinates n;
    n.x = dx * cos(ang) - dy * sin(ang) + x0;
    n.y = dx * sin(ang) + dy * cos(ang) + y0;

    return n;
}

coordinates drawkoch(coordinates c, int s3, double ang, double f)
{   
    coordinates c0, c1;
    c0 = c;
    c1 = rotatie(c0.x, c0.y, c0.x + s3, c0.y, ang * M_PI / 180 * f);
    drawline(c0, c1);

    c0 = c1;
    c1 = rotatie(c0.x, c0.y, c0.x + s3, c0.y, (ang - 60) * M_PI / 180 * f);
    drawline(c0, c1);

    c0 = c1;
    c1 = rotatie(c0.x, c0.y, c0.x + s3, c0.y, (ang + 60) * M_PI / 180 * f);
    drawline(c0, c1);

    c0 = c1;
    c1 = rotatie(c0.x, c0.y, c0.x + s3, c0.y, ang * M_PI / 180 * f);
    drawline(c0, c1);

    return c1;
}

coordinates drawfig(coordinates c, int size, double ang, double f)
{   
    double s3 = size / 3;
    coordinates c0 = c;

    if(s3 == 9)
    {
        drawkoch(c0, s3, ang, f);
        c0 = rotatie(c0.x, c0.y, c0.x - s3, c0.y, (ang - 60) * M_PI / 180 * f);
    }
    else
    {
    c0 = drawfig(c0, s3, ang, f);

    c0 = rotatie(c0.x, c0.y, c0.x + s3, c0.y, (ang) * M_PI / 180 * f);
    c0 = drawfig(c0, s3, ang - 60, f);

    c0 = rotatie(c0.x, c0.y, c0.x + s3, c0.y, (ang - 60) * M_PI / 180 * f);
    c0 = drawfig(c0, s3, ang + 60, f);

    c0 = rotatie(c0.x, c0.y, c0.x + s3, c0.y, (ang + 60) * M_PI / 180 * f);
    c0 = drawfig(c0, s3, ang, f);
    }

    return c0;
}



int main(void)
{
    // string constant followed by string constant = concatenated constrants
    printf("<?xml version=\"1.0\"?>\n"
        "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n"
        "<path fill=\"none\" stroke=\"red\" d=\"");

    coordinates c;
    c.x = 0; c.y = 729 * sqrt(3) / 2;
    c = drawfig(c, 729, 0, 1);
    //c = drawfig(c, 729, 120, 1);
    //drawfig(c, 729, -120, 1);

    printf("z\"/>\n</svg>\n");
    return 0;
}

