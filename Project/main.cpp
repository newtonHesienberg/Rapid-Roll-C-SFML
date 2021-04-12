#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include "Player.h"
#include "Platform.h"


static const sf::Color platformColor(58, 58, 58);
static const float VIEW_HEIGHT = 1024.0f;
static const float VIEW_WIDTH = 1024.0f;


void ResizeView(sf::RenderWindow& window , sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_WIDTH * aspectRatio);
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_WIDTH), "My First SFML Project", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(200.0f, 50.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_WIDTH));
    sf::View viewText(sf::Vector2f(200.0f, 50.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_WIDTH));
    /*sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));
    player.setFillColor(sf::Color::White);
    player.setOrigin(sf::Vector2f(50.0f, 50.0f));
    player.setPosition(sf::Vector2f(256, 256));*/

    //Texturing
    /*sf::Texture playerTexture;
    playerTexture.loadFromFile("Woodcutter_run.png");
    player.setTexture(&playerTexture);*/

    //Font and Text----------------------------------------------------------------------------------------------
    sf::Font font;
    if (!font.loadFromFile("Electrolize-Regular.ttf"))
    {
        std::cout << "Error loading form file" << std::endl;
        system("pause");
    }

    sf::Text text;
    text.setFont(font);
    text.setString("TIME : 999s");
    text.setPosition(sf::Vector2f(-150.0f, -350.0f));
    //------------------------------------------------------------------------------------------------------------

    //Animation and Player
    Player player(nullptr, sf::Vector2u(6, 1), 0.1f, 200.0f, 200.0f);

    //Platform
    Platform platform1(nullptr, sf::Vector2f(810.0f, 30.0f), sf::Vector2f(200.0f, 550.0f), platformColor);
    Platform platform1f(nullptr, sf::Vector2f(810.0f, 30.0f), sf::Vector2f(200.0f, -450.0f), platformColor);
    Platform platform2(nullptr, sf::Vector2f(30.0f, 1500.0f), sf::Vector2f(590.0f, -200.0f), platformColor);
    Platform platform3(nullptr, sf::Vector2f(30.0f, 1500.0f), sf::Vector2f(-190.0f, -200.0f), platformColor);

    //For Small Platforms
    std::vector<Platform> platforms;

    for (int i = 0; i < 6; i++)
    {
        int randomNumber = rand() % 400;
               
            Platform platform(nullptr, sf::Vector2f(100.0f, 30.0f), sf::Vector2f(randomNumber, 350.0f - i * 150), sf::Color(rand() % 255, rand() % 255, rand() % 255));
            platforms.push_back(platform);      
    }

    /*sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x /= 6;
    textureSize.y /= 1;
    player.setTextureRect(sf::IntRect(textureSize.x * 5, textureSize.y * 0, textureSize.x, textureSize.y));*/

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
        {
            deltaTime = 1.0f / 20.0f;
        }

        sf::Event evnt;

        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case  sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                ResizeView(window, viewText);
                break;		
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Space && player.GetCanJump())
                    player.Jump();
                break;
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128)
                {
                    printf("%c", evnt.text.unicode);
                }
                break;
            }
        }

        player.Update(deltaTime);

        sf::Vector2f direction;


        if (platform1.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
            player.OnCollision(direction);
        if (platform1f.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
            player.OnCollision(direction);
        if (platform2.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
            player.OnCollision(direction);
        if (platform3.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
            player.OnCollision(direction);

        //Small Platforms [collision]
        for (int i = 0; i < platforms.size(); i++)
        {
            if (platforms[i].GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);
            platforms[i].Move(0.0f, -100.0f * deltaTime);
        }

        //view.setCenter(player.GetPosition());

        //Player Input [Mouse]
       /* if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float)mousePos.x, (float)mousePos.y);
        }*/

        //Rendering------------------------------------------------------------------------------------------
        window.clear(sf::Color ::Color(0, 0, 0));
        //window.draw(text);
        //window.setView(view);
        //window.setView(viewText);
        window.setView(view);
        player.Draw(window);
        platform2.Draw(window);
        platform3.Draw(window);
        platform1.Draw(window);   

        for (int i = 0; i < platforms.size(); i++)
        {
            platforms[i].Draw(window);
        }
        platform1f.Draw(window);

        window.display();

    }

    return 0;
}