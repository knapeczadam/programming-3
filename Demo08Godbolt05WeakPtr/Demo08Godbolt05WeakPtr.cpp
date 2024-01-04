#include <iostream>
#include <memory>
#include <string>

struct Player{
    Player(std::string name) {std::cout << name << " created!\n"; m_name = name;};
    ~Player() {std::cout << m_name << " destroyed!\n";};
    std::string getName() {return m_name;};
    std::weak_ptr<Player> companion;
    std::string m_name;
};

int main() {
    std::shared_ptr<Player> Tom = std::make_shared<Player>("Tom");
    auto Kevin = std::make_shared<Player>("Kevin");
    std::cout << "use count Tom = " << Tom.use_count() << "\n";
    Tom->companion = Kevin;
    Kevin->companion = Tom;
    std::cout << "use count Tom = " << Tom.use_count() << "\n";
    std::cout << "use count Kevin = " << Kevin.use_count() << "\n";
    if (!Tom->companion.expired()) {
        auto test = Tom->companion.lock();
        std::cout << "use count Kevin = " << Kevin.use_count() << "\n";
        std::cout << test->getName() << "\n";
    }

}