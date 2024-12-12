#include "TXLib.h"

struct Mario
{
    int x;
    int y;
    int vx;
    HDC image_r;
    HDC image_l;
    HDC image;
    int x_cadr;
    int y_cadr;

    void draw()
    {
        txTransparentBlt(txDC(), x, y, 84, 107, image, 84*x_cadr, 107*y_cadr, TX_WHITE);
    }

    void animation()
    {
        x_cadr += 1;
        if (x_cadr >= 5)
        {
            x_cadr = 0;
            y_cadr += 1;
            if (y_cadr >= 4)
            {
                y_cadr = 0;
            }
        }
    }

};

struct Barrier
{
    int x;
    int y;

    void draw()
    {
       txSetColor(TX_BLACK);
       txSetFillColor(TX_RED);
       txRectangle(x, y, x+20, y+50);
    }
};

int main()
{
txCreateWindow (800, 600);
txTextCursor (false);

Mario mario = {0, 300, 5, txLoadImage("Pictures/mario_r.bmp"), txLoadImage("Pictures/mario_l.bmp"), txLoadImage("Pictures/mario_r.bmp"), 0, 0};

Mario mario_bot[5];
mario_bot[0] = {100, 250, 2, mario.image, mario.image_l, mario.image_r, 0, 0};
mario_bot[1] = {200, 200, 3, mario.image, mario.image_l, mario.image_r, 0, 0};
mario_bot[2] = {300, 150, 7, mario.image, mario.image_l, mario.image_r, 0, 0};
mario_bot[3] = {400, 100, 5, mario.image, mario.image_l, mario.image_r, 0, 0};
mario_bot[4] = {500, 50, 10, mario.image, mario.image_l, mario.image_r, 0, 0};

Barrier bar[2];
bar[0] = {200, 50};
bar[1]= {600, 50};

    while(!GetAsyncKeyState(VK_ESCAPE))
    {

       txSetFillColor(TX_WHITE);
        txClear();
        txBegin();

        for(int i=0; i<2; i++)
        {
            bar[i].draw();
        }

        //Гл. герой
        mario.draw();
        if (GetAsyncKeyState(VK_RIGHT))
        {
            mario.x += mario.vx;
            mario.image = mario.image_r;
            mario.animation();
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            mario.x -= mario.vx;
            mario.image = mario.image_l;
            mario.animation();
        }

        //Боты
        for (int i=0; i<4; i++)
        {
            mario_bot[i].draw();

            mario_bot[i].animation();

            mario_bot[i].x += mario_bot[i].vx;

            if (mario_bot[i].x>800-84 )
            {
                mario_bot[i].vx = -mario_bot[i].vx;
                mario_bot[i].image = mario_bot[i].image_l;
            }
            if (mario_bot[i].x<0)
            {
                mario_bot[i].vx = -mario_bot[i].vx;
                mario_bot[i].image = mario_bot[i].image_r;
            }
        }

        mario_bot[4].draw();
        mario_bot[4].animation();
        mario_bot[4].x += mario_bot[4].vx;
        if(mario_bot[4].x+87>bar[1].x)
        {
            mario_bot[4].vx = -mario_bot[4].vx;
            mario_bot[4].image = mario_bot[4].image_l;
        }
        if(mario_bot[4].x<bar[0].x+20)
        {
            mario_bot[4].vx = -mario_bot[4].vx;
            mario_bot[4].image = mario_bot[4].image_r;
        }

        txEnd();
        txSleep(50);
    }

txDeleteDC(mario.image);
txDeleteDC(mario.image_r);
txDeleteDC(mario.image_l);

txDisableAutoPause();
return 0;
}

