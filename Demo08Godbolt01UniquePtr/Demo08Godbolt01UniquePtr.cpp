#include <memory>
#include <iostream>

struct Widget{
    Widget() {std::cout << "Widget\n";}
    ~Widget() {std::cout << "~Widget()\n";}
};

class Trinket{
    Trinket() {m_widgets = new Widget[10]();};
    ~Trinket() {delete[] m_widgets;};
    Widget * m_widgets;
};

struct autoTrinket {
    autoTrinket() {m_widgets = std::make_unique<Widget[]>(10);}
    std::unique_ptr<Widget[]> m_widgets; 
};

auto makeWidgets(int n_Widgets) {
    return std::make_unique<Widget[]>(n_Widgets);
}

void absorbWidgets(std::unique_ptr<Widget[]>& local_ptr){
    std::cout << "in absorbWidgets \n";
}

void sinkWidgets(std::unique_ptr<Widget[]> local_ptr){
    std::cout << "in sinkWidgets \n";
}


int main() {
    auto ptr = makeWidgets(10);
    std::cout << "Doing stuff!\n"; 
    absorbWidgets(ptr);
    std::cout << "The pointer is " << ptr.get() << "\n";
    sinkWidgets(std::move(ptr));
    std::cout << "After sink widget\n";
    autoTrinket tryout;
}