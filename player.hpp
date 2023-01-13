#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <vector>
#include <iostream>

class Player
{
    public:
    float posx, posy, deltax, deltay, height=64, eyes, movedirection, strafeangle;
    int speed=2;
    int crouching=0, moff=0;
    float angle;
    int xoff, yoff, ipx, ipy, ipx_add_xo ,ipy_add_yo, ipx_sub_xo ,ipy_sub_yo;
    sf::RectangleShape player;

    void init()
    {
        posx=512;
        posy=256;
        angle=0;
        eyes=400;
        deltax=sin(angle*0.0174532925+90*0.0174532925)*5;
        deltay=cos(angle*0.0174532925+90*0.0174532925)*5;
        player.setSize(sf::Vector2f(2,2));
        player.setPosition(sf::Vector2f(posx, posy));
    }
    void Move(float Pi, int map[10][10], sf::RenderWindow &window)
    {
        int xo = 0;
        if (deltax < 0) { xo=-20; } else { xo=20; }
        int yo = 0;
        if (deltay < 0) { yo=-20; } else { yo=20; }
        ipx=posx/128.0; ipx_add_xo=(posx+xo)/128.0; ipx_sub_xo=(posx-xo)/128.0;
        ipy=posy/128.0; ipy_add_yo=(posy+yo)/128.0; ipy_sub_yo=(posy-yo)/128.0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && window.hasFocus())
        {
            if (map[ipy_add_yo][ipx]==0) {posy+=deltay*speed;}
            if (map[ipy][ipx_add_xo]==0) {posx+=deltax*speed;}
            movedirection=1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && window.hasFocus())
        {
            if (map[ipy_sub_yo][ipx]==0) {posy-=deltay*speed;}
            if (map[ipy][ipx_sub_xo]==0) {posx-=deltax*speed;}
            movedirection=2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && window.hasFocus())
        {
            strafeangle=angle+90;
            if (strafeangle>359)
            strafeangle=strafeangle-360;
            deltax=cos(strafeangle*0.0174532925)*5;
            deltay=sin(strafeangle*0.0174532925)*5;
            if (deltax < 0) { xo=-20; } else { xo=20; }
            if (deltay < 0) { yo=-20; } else { yo=20; }
            ipx=posx/128.0; ipx_add_xo=(posx+xo)/128.0;
            ipy=posy/128.0; ipy_sub_yo=(posy-yo)/128.0;
            if (map[ipy_sub_yo][ipx]==0) {posy-=deltay*speed;}
            if (map[ipy][ipx_add_xo]==0) {posx+=deltax*speed;}
            movedirection=3;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && window.hasFocus())
        {
            strafeangle=angle-90;
            if (strafeangle<0)
            strafeangle=strafeangle+360;
            deltax=cos(strafeangle*0.0174532925)*5;
            deltay=sin(strafeangle*0.0174532925)*5;
            if (deltax < 0) { xo=-20; } else { xo=20; }
            if (deltay < 0) { yo=-20; } else { yo=20; }
            ipx=posx/128.0; ipx_add_xo=(posx+xo)/128.0;
            ipy=posy/128.0; ipy_sub_yo=(posy-yo)/128.0;
            if (map[ipy_sub_yo][ipx]==0) {posy-=deltay*speed;}
            if (map[ipy][ipx_add_xo]==0) {posx+=deltax*speed;}
            movedirection=4;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && window.hasFocus())
        {
            angle=angle+10;
            if (angle>359)
            angle=angle-360;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && window.hasFocus())
        {
            angle=angle-10;
            if (angle<0)
            angle=angle+360;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && window.hasFocus())
        {
            eyes=eyes+10;
            if (eyes>800)
            eyes=800;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && window.hasFocus())
        {
            eyes=eyes-10;
            if (eyes<0)
            eyes=0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && window.hasFocus())
        {
            crouching=1;
            height=-128;
            speed=1;
        }
        deltax=sin(angle*0.0174532925+90*0.0174532925)*5;
        deltay=cos(angle*0.0174532925+90*0.0174532925)*5;
        if (crouching!=1)
        {
            speed=2;
            height=64;
        }
        crouching=0;
        player.setPosition(sf::Vector2f(posx, posy));
    }
};