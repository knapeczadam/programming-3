#include <iostream>
#include <memory>

struct Player{
    Player() {std::cout << "Player created!\n";};
    ~Player() {std::cout << "Player destroyed!\n";};
    std::shared_ptr<Player> companion;
};

int main() {
    std::shared_ptr<Player> Tom = std::make_shared<Player>();
    auto Kevin = std::make_shared<Player>();
    std::cout << "use count Tom = " << Tom.use_count() << "\n";
    Tom->companion = Kevin;
    Kevin->companion = Tom;
    std::cout << "use count Tom = " << Tom.use_count() << "\n";

}