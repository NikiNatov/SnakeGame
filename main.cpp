#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include "Engine/Game.h"

using namespace sf;
int width = 20;
int height = 20;
int _size = 40;

int _score = 0;
std::ostringstream ssScore;

bool isGameOver = false;

enum Direction{UP, DOWN, LEFT, RIGHT};

Direction dir = DOWN;

int num = 4;

struct Snake
{
    int x, y;
}snake[100];



struct Fruit
{
    int x, y;
}fruit;


void Tick(Text &score)
{
    for(int i = num; i > 0 ; --i)
    {
        snake[i].x = snake[i-1].x;
        snake[i].y = snake[i-1].y;
    }

    switch(dir)
    {
    case UP:
        snake[0].y--;
        break;
    case DOWN:
        snake[0].y++;
        break;
    case LEFT:
        snake[0].x--;
        break;
    case RIGHT:
        snake[0].x++;
        break;
    }

    if(snake[0].x == fruit.x && snake[0].y == fruit.y)
    {
        num++;
        fruit.x = rand() % width;
        fruit.y = rand() % height;
        _score++;
        ssScore.str("");
        ssScore<<"Score: "<<_score;
        score.setString(ssScore.str());


    }

    for(int i = 1; i < num; i++)
    {
        if(snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            num = i;
            if(i == num)
            {
                isGameOver = true;
            }
        }
    }
}


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(800, 800), "Snake!", Style::Default);

    Text gameOver, score;
    Font font;

    if(!font.loadFromFile("Fonts/arial.ttf"))
    {
        std::cout<<"Image can't be loaded!"<<std::endl;
    }


    ssScore << "Score: "<<_score;

    gameOver.setString("Game Over!");
    gameOver.setColor(Color::Yellow);
    gameOver.setStyle(Text::Bold);
    gameOver.setFont(font);
    gameOver.setPosition(250, 350);
    gameOver.setCharacterSize(54);

    score.setFont(font);
    score.setString(ssScore.str());


    Texture grassTexture;
    Texture snakeTexture;
    Texture fruitTexture;
    Texture backGTexture;

    if(!backGTexture.loadFromFile("Textures/background.jpg"))
    {
        std::cout<<"Image can't be loaded!"<<std::endl;
    }
    if(!grassTexture.loadFromFile("Textures/grass.png"))
    {
        std::cout<<"Image can't be loaded!"<<std::endl;
    }
    if(!snakeTexture.loadFromFile("Textures/snakeSprite2.png"))
    {
        std::cout<<"Image can't be loaded!"<<std::endl;
    }
    if(!fruitTexture.loadFromFile("Textures/snakeSprite2.png"))
    {
        std::cout<<"Image can't be loaded!"<<std::endl;
    }

    Sprite grassSprite(grassTexture);
    Sprite snakeSprite(snakeTexture);
    Sprite fruitSprite(fruitTexture);
    Sprite backGSprite(backGTexture);

    Clock clock;
    double timer = 0, delay = 0.13;

    fruit.x = 10;
    fruit.y = 10;

    while(window.isOpen())
    {
        double _time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer = timer + _time;

        Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                    window.close();
                    break;
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Left))
        {
            if(dir == RIGHT)
            {
                dir = RIGHT;
            }
            else
            {
                dir = LEFT;
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Right))
        {
            if(dir == LEFT)
            {
                dir = LEFT;
            }
            else
            {
                dir = RIGHT;
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Up))
        {
            if(dir == DOWN)
            {
                dir = DOWN;
            }
            else
            {
                dir = UP;
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Down))
        {
            if(dir == UP)
            {
                dir = UP;
            }
            else
            {
                dir = DOWN;
            }
        }


        if(timer>delay)
        {
            timer = 0;
            Tick(score);
        }

        if(snake[0].x == -1 || snake[0].y == -1 || snake[0].x == width || snake[0].y == height)
        {
            isGameOver = true;
        }


        window.clear(Color::Black);


        for(int i = 0 ; i < width ; i++)
        {
            for(int j = 0 ; j < height ; j++)
            {
                grassSprite.setPosition(_size * i, _size * j);
                window.draw(grassSprite);
            }
        }



        for(int i = 0 ; i < num ; i++)
        {
            int tx = 0, ty = 0;

            ///HEAD
            if(i == 0)
            {
                int nsegX = snake[i+1].x;
                int nsegY = snake[i+1].y;

                if(snake[i].y < nsegY)
                {
                    ///UP
                    tx = 3;
                    ty = 0;
                }
                else if(snake[i].y >  nsegY)
                {
                    ///DOWN
                    tx = 4;
                    ty = 1;
                }
                else if(snake[i].x < nsegX)
                {
                    ///LEFT
                    tx = 3;
                    ty = 1;
                }
                else if(snake[i].x > nsegX)
                {
                    ///RIGHT
                    tx = 4;
                    ty = 0;
                }
            }
            ///TAIL///
            else if( i == (num - 1))
            {
                int prevSegX = snake[num - 2].x;
                int prevSegY = snake[num - 2].y;


                if(snake[i].y < prevSegY)
                {
                    ///Moving DOWN
                    tx = 4;
                    ty = 3;
                }
                else if(snake[i].y > prevSegY)
                {
                    ///Moving UP
                    tx = 3;
                    ty = 2;
                }
                else if(snake[i].x < prevSegX)
                {
                    ///Moving RIGHT
                    tx = 4;
                    ty = 2;
                }
                else if(snake[i].x > prevSegX)
                {
                    ///Moving LEFT
                    tx = 3;
                    ty = 3;
                }

            }
            ///BODY
            else
            {
                int prevSegX = snake[i - 1].x;
                int prevSegY = snake[i - 1].y;
                int nextSegX = snake[i + 1].x;
                int nextSegY = snake[i + 1].y;

                if((prevSegX < snake[i].x && nextSegX > snake[i].x) || (nextSegX < snake[i].x && prevSegX > snake[i].x))
                {
                    ///HORIZONTAL
                    tx = 1;
                    ty = 0;
                }
                else if((prevSegY < snake[i].y && nextSegY > snake[i].y) || (nextSegY < snake[i].y && prevSegY > snake[i].y))
                {
                    ///VERTICAL
                    tx = 2;
                    ty = 1;
                }
                else if((prevSegX > snake[i].x && nextSegY > snake[i].y) || (prevSegY > snake[i].y && nextSegX > snake[i].x))
                {
                    ///RIGHT-DOWN
                    tx = 0;
                    ty = 0;
                }
                else if((prevSegX > snake[i].x && nextSegY < snake[i].y) || (prevSegY < snake[i].y && nextSegX > snake[i].x))
                {
                    ///RIGHT-UP
                    tx = 0;
                    ty = 1;
                }
                else if((prevSegX < snake[i].x && nextSegY > snake[i].y) || (prevSegY > snake[i].y && nextSegX < snake[i].x))
                {
                    ///LEFT-DOWN
                    tx = 2;
                    ty = 0;
                }
                else if((prevSegX < snake[i].x && nextSegY < snake[i].y) || (prevSegY < snake[i].y && nextSegX < snake[i].x))
                {
                    ///LEFT-UP
                    tx = 2;
                    ty = 2;
                }
            }
            snakeSprite.setTextureRect(IntRect(tx * 40, ty * 40, 40, 40));
            snakeSprite.setPosition(snake[i].x * _size, snake[i].y * _size);

            window.draw(snakeSprite);
        }

        fruitSprite.setTextureRect(IntRect(0, 3*40, 40, 40));
        fruitSprite.setPosition(fruit.x * _size, fruit.y * _size);
        window.draw(fruitSprite);

        window.draw(score);

        if(isGameOver == true)
        {

            window.clear();

            window.draw(backGSprite);
            window.draw(gameOver);

            window.display();

            system("PAUSE");

            break;
        }

        window.display();
    }
    return 0;
}
