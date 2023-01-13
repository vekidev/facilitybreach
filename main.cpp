#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <iostream>
#include "player.hpp"

float Pi=3.1415926535;
float P2=Pi/2;
float P3=3*Pi/2;
float RD=0.0174533;

sf::Color wallcolor;
sf::VertexArray quad(sf::Quads, 4);
sf::VertexArray lookline(sf::LineStrip, 2);
sf::VertexArray linepiece(sf::LineStrip, 2);
sf::VertexArray linepiece1(sf::LineStrip, 4);
sf::RectangleShape ground;
Player player1;
int mapwidth=10, mapheight=10, maps=128;
int map[10][10]={
{1,1,1,1,1,1,1,1,1,1},
{1,0,1,0,0,1,0,0,0,1},
{1,0,1,0,0,1,0,0,0,1},
{1,0,1,0,0,1,0,0,0,1},
{1,0,1,0,0,1,1,0,1,1},
{1,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1},
{1,0,1,0,0,0,0,0,0,1},
{1,0,1,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1}};

int floorgmap[10][10]={
{1,2,1,2,1,2,1,2,1,2},
{2,1,2,1,2,1,2,1,2,1},
{1,2,1,2,1,2,1,2,1,2},
{2,1,2,1,2,1,2,1,2,1},
{1,2,1,2,1,2,1,2,1,2},
{2,1,2,1,2,1,2,1,2,1},
{1,2,1,2,1,2,1,2,1,2},
{2,1,2,1,2,1,2,1,2,1},
{1,2,1,2,1,2,1,2,1,2},
{2,1,2,1,2,1,2,1,2,1}};

sf::Texture LineTex;
sf::Texture LineTex1;
sf::Sprite LineSprite;

void DrawMap2D(sf::RenderWindow &window)
{
    int x,y,xo,yo;
    for (y=0;y<mapheight;y++)
    {
        for (x=0;x<mapwidth;x++)
        {
            if (map[y][x]==1)
            wallcolor=sf::Color::Red;
            else
            wallcolor=sf::Color::Black;
            
            xo=x*maps;
            yo=y*maps;
            quad[0].color = wallcolor;
            quad[1].color = wallcolor;
            quad[2].color = wallcolor;
            quad[3].color = wallcolor;
            quad[0].position = sf::Vector2f(xo+1, yo+1);
            quad[1].position = sf::Vector2f(xo+1, yo+maps-1);
            quad[2].position = sf::Vector2f(xo+maps-1, yo+maps-1);
            quad[3].position = sf::Vector2f(xo+maps-1, yo+1);
            /*window.draw(quad);*/
        }
    }
}

float RayLenght(float ax,float ay,float bx,float by,float ang)
{ 
    return cos(ang)*(bx-ax)-sin(ang)*(by-ay);
}

void CastRay(sf::RenderWindow &window)
{
    float rayy, rayx, yoff, xoff, finaldis, ceilingrdrawdistance;
    float raya=player1.angle-30;
    if (raya<0)raya+=360;if (raya>359)raya-=360;

    for (int rep=0; rep<1280; rep++)
    {
        sf::RectangleShape Shape;
        sf::RectangleShape FloorShape;
        float horx, hory, hordis=10000, multiply=1;
        //--HORIZONTALNO--//
        if (raya<180)
        {
            rayy=(int (player1.posy/128)*128)-0.0001;
            rayx=(player1.posx)+(player1.posy-rayy)/tan(raya*0.0174532925);
            yoff=-128;xoff=-yoff/tan(raya*0.0174532925);
        }
        else if (raya>180)
        {
            rayy=(int (player1.posy/128)*128)+128;
            rayx=player1.posx+(player1.posy-rayy)/tan(raya*0.0174532925);
            yoff=128;xoff=-yoff/tan(raya*0.0174532925);
        }
        else if (raya==0 || raya==180)
        {
            rayy=player1.posy;rayx=player1.posx;
        }
        for (int r=0;r<10;r++)
        {
            int mapx=int (rayx/128);
            int mapy=int (rayy/128);
            if (mapx>-1 && mapx<10 && map[mapy][mapx]==1)
            {
                horx=rayx;hory=rayy;
                hordis=sqrt(((player1.posx-rayx)*(player1.posx-rayx))+((player1.posy-rayy)*(player1.posy-rayy)));
                r=10;
            }
            else
            {
                rayy=rayy+yoff;
                rayx=rayx+xoff;
            }
        }
        
        //--VERTIKALNO--//
        float verx, very, verdis=10000;
        if (raya<90 || raya>270)
        {
            rayx=(int (player1.posx/128)*128)+128;
            rayy=player1.posy+(player1.posx-rayx)*tan(raya*0.0174532925);
            xoff=128;yoff=-xoff*tan(raya*0.0174532925);
        }
        else if (raya>90&&raya<270)
        {
            rayx=(int (player1.posx/128)*128)-0.0001;
            rayy=player1.posy+(player1.posx-rayx)*tan(raya*0.0174532925);
            xoff=-128;yoff=-xoff*tan(raya*0.0174532925);
        }
        else if (raya==90 || raya==270)
        {
            rayy=player1.posy;rayx=player1.posx;
        }
        for (int r=0;r<10;r++)
        {
            int mapx=int (rayx/128);
            int mapy=int (rayy/128);
            if (mapy>-1 && mapy<10 && map[mapy][mapx]==1)
            {
                verx=rayx;very=rayy;
                verdis=sqrt(((player1.posx-rayx)*(player1.posx-rayx))+((player1.posy-rayy)*(player1.posy-rayy)));
                r=10;
            }
            else
            {
                rayy=rayy+yoff;
                rayx=rayx+xoff;
            }
        }

        FloorShape.setFillColor(sf::Color::Cyan);

        if (verdis>hordis){rayx=horx;rayy=hory;finaldis=hordis;Shape.setFillColor(sf::Color::Red);}
        else if (verdis<hordis){rayx=verx;rayy=very;finaldis=verdis;Shape.setFillColor(sf::Color::Blue);}

        //--ZIDOVI--//

        float beta=player1.angle-raya;if (beta<0)beta+=360;if (beta>359)beta-=360;
        finaldis=finaldis*cos(beta*0.0174532925);
        int wallprojection=(128/finaldis)*1000;

        Shape.setSize(sf::Vector2f(1,wallprojection));
        Shape.setPosition(sf::Vector2f(1280-rep, (player1.eyes+player1.height)-(wallprojection/2)));
        window.draw(Shape);

        /*Shape.setSize(sf::Vector2f(1,wallprojection));
        Shape.setPosition(sf::Vector2f(1280-rep, (player1.eyes+player1.height)-(wallprojection)));
        window.draw(Shape);*/

        //linepiece[0].position=sf::Vector2f((640-rep)+1000, 800-wallprojection);linepiece[1].position=sf::Vector2f((640-rep)+1000, wallprojection);//

        raya=raya+0.046875;
        if (raya<0)raya+=360;if (raya>359)raya-=360;
    }
}

main()
{
    ground.setFillColor(sf::Color(128,128,128));
    ground.setSize(sf::Vector2f(1280, 1000));
    sf::RenderWindow game(sf::VideoMode(1800, 800), "Facility Breach", sf::Style::Default);
    sf::Event gamevent;
    player1.init();
    game.setFramerateLimit(30);

    sf::Clock clock;
    float lastTime = 0;

    while (game.isOpen())
    {
        ground.setPosition(sf::Vector2f(0, 0+player1.eyes+player1.height));
        float currentTime = clock.restart().asSeconds();
        float fps = 1.f / (currentTime - lastTime);
        lastTime = currentTime;
        char c[10];
        sprintf(c, "%f", fps);
        game.setTitle(c);
        player1.Move(Pi, map, game);
        game.clear(sf::Color::White);
        while (game.pollEvent(gamevent))
        {
            switch (gamevent.type)
            {
                case sf::Event::Closed:
                game.close();
                std::exit(1);
            }
        }
        game.draw(ground);
        CastRay(game);
        DrawMap2D(game);
        //game.draw(player1.player);
        game.display();
    }
}