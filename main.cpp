#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Collision Detection", sf::Style::Close | sf::Style::Titlebar);

    float gridSize = 50.f;
    sf::RectangleShape player(sf::Vector2f(gridSize, gridSize));
    player.setPosition(sf::Vector2f((window.getSize().x - gridSize)/ 2.f, (window.getSize().y - gridSize)/ 2.f));
    player.setFillColor(sf::Color::Green);
    float speed = .5f;

    std::vector<sf::RectangleShape> walls;
    sf::RectangleShape wall(sf::Vector2f(gridSize, gridSize));
    wall.setFillColor(sf::Color::Red);

    //std::ifstream file("/home/tim/Development/C++/SFML_CollisionDetection/map.txt");
    std::ifstream file("../map.txt");
    if(!file) exit(1);
//    GetCurrentDirectory
    sf::Vector2f position;
    while (!file.eof()) {
        char c;
        file >> c;

        if(c == '#'){
            wall.setPosition(sf::Vector2f(gridSize * position.x, gridSize * position.y));
            walls.push_back(wall);
        }

        ++position.x;
        if(position.x == window.getSize().x / gridSize) {
            position.x = 0;
            ++position.y;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Player movement
        sf::Vector2f movement = {0.f, 0.f};
        // Left movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= speed;
        }
        // Right movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += speed;
        }
        // Up movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= speed;
        }
        // Down movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += speed;
        }

        // Screen collision
        // Left collision
        if(player.getPosition().x < 0.f){
            player.setPosition(0.f, player.getPosition().y);
        }
        // Right collision
        if(player.getPosition().x + player.getGlobalBounds().width > window.getSize().x){
            player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getPosition().y);
        }
        // Top collision
        if(player.getPosition().y < 0.f){
            player.setPosition(player.getPosition().x, 0.f);
        }
        // Bottom collision
        if(player.getPosition().y + player.getGlobalBounds().height > window.getSize().y){
            player.setPosition(player.getPosition().x, window.getSize().y - player.getGlobalBounds().height);
        }

        for(auto& w: walls){
            sf::FloatRect playerBounds = player.getGlobalBounds();
            sf::FloatRect wallBounds = w.getGlobalBounds();

            sf::FloatRect nextPositionX = playerBounds;
            nextPositionX.left += movement.x;
            sf::FloatRect nextPositionY = playerBounds;
            nextPositionY.top += movement.y;

            if(wallBounds.intersects(nextPositionX)){
                movement.x = 0.f;
            }
            if(wallBounds.intersects(nextPositionY)){
                movement.y = 0.f;
            }
        }


        player.move(movement);

        window.clear();
        for(auto& w: walls) {
            window.draw(w);
        }
        window.draw(player);
        window.display();
    }

    return 0;
}
