#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс Animal
class Animal abstract {
protected:
    string description;

public:
    Animal() {}
    Animal(const string& description) {
        SetDescription(description);
    }
    virtual ~Animal() {}

    void SetDescription(const string& description) {
        this->description = description;
    }

    const string& GetDescription() const {
        return description;
    }
};

// Класс травоядных животных
class Herbivore abstract  : public Animal {
protected:
    double weight;
    bool isAlive;

public:
    Herbivore() {
        SetWeight(0);
        SetLife(true);
    }

    virtual ~Herbivore() {
        cout << "Herbivore destroyed: " << description << "\n";
    }

    void SetWeight(double weight) {
       this->weight = weight;
    }

    double GetWeight() const {
        return weight;
    }

    void EatGrass() {
        weight += 10;
    }

    void SetLife(bool status) {
        isAlive = status;
    }

    bool IsAlive() const {
        return isAlive;
    }
};

// Разновидности травоядных
class Wildebeest : public Herbivore {
public:
    Wildebeest(double weight = 0, bool alive = true) {
        SetDescription("Wildebeest");
        SetWeight(weight);
        SetLife(alive);
    }

    ~Wildebeest() {
        cout << "Wildebeest destroyed\n";
    }

    void EatGrass() {
        Herbivore::EatGrass();
    }
};

class Bison : public Herbivore {
public:
    Bison(double weight = 0, bool alive = true) {
        SetDescription("Bison");
        SetWeight(weight);
        SetLife(alive);
    }

    ~Bison() {
        cout << "Bison destroyed\n";
    }

    void EatGrass() {
        Herbivore::EatGrass();
    }
};

// Класс плотоядных животных
class Carnivore abstract : public Animal {
protected:
    int power;

public:
    Carnivore() {
        SetPower(50);
    }

    virtual ~Carnivore() {
        cout << "Carnivore destroyed: " << description << "\n";
    }

    void SetPower(int power) {
        this->power = power;
    }

    int GetPower() const {
        return power;
    }

    void Eat(Herbivore* herbivore) {
        // Проверяем, что указатель на травоядного не нулевой и травоядное живо
        if (herbivore && herbivore->IsAlive()) {
            // Проверяем, сила хищника больше или равна весу травоядного
            if (power >= herbivore->GetWeight()) {
                // Если сила хищника достаточна, он съедает травоядного
                // Увеличиваем силу хищника на 10
                power += 10;
                // Устанавливаем травоядному статус мертвого
                herbivore->SetLife(false);
            }
            else {
                // Если сила хищника меньше веса травоядного, хищник теряет силу
                power -= 10;
                // Проверяем, чтобы сила хищника не стала отрицательной
                if (power < 0) {
                    // Если сила отрицательная, устанавливаем её в 0
                    power = 0; // Хищник не может иметь отрицательную силу
                }
            }
        }
    }
};

// Разновидности плотоядных
class Lion : public Carnivore {
public:
    Lion(int power = 50) {
        SetDescription("Lion");
        SetPower(power);
    }

    ~Lion() {
        cout << "Lion destroyed\n";
    }

    void Eat(Herbivore* herbivore) {
        Carnivore::Eat(herbivore);
    }
};

class Wolf : public Carnivore {
public:
    Wolf(int power = 50) {
        SetDescription("Wolf");
        SetPower(power);
    }

    ~Wolf() {
        cout << "Wolf destroyed\n";
    }

    void Eat(Herbivore* herbivore) {
        Carnivore::Eat(herbivore);
    }
};

class Continent abstract {
protected:
    string name;

public:
    Continent() {}
    Continent(const string& name) {
        SetName(name);
    }

    virtual ~Continent() {
        cout << "Continent destroyed: " << name << "\n";
    }

    void SetName(const string& name) {
        this->name = name;
    }

    const string& GetName() const {
        return name;
    }

    virtual void Populate(vector<Herbivore*>& herbivores, vector<Carnivore*>& carnivores) = 0;
};

// Разновидности континентов
class Africa : public Continent {
public:
    Africa() {
        SetName("Africa");
    }

    ~Africa() {
        cout << "Africa destroyed\n";
    }

    void Populate(vector<Herbivore*>& herbivores, vector<Carnivore*>& carnivores) {
        cout << "Populating Africa with animals...\n";
        Wildebeest* wildebeest = new Wildebeest(100, true);
        herbivores.push_back(wildebeest);

        Lion* lion = new Lion(80);
        carnivores.push_back(lion);
    }
};

class NorthAmerica : public Continent {
public:
    NorthAmerica() {
        SetName("North America");
    }

    ~NorthAmerica() {
        cout << "North America destroyed\n";
    }

    void Populate(vector<Herbivore*>& herbivores, vector<Carnivore*>& carnivores) {
        cout << "Populating North America with animals...\n";
        Bison* bison = new Bison(200, true);
        herbivores.push_back(bison);

        Wolf* wolf = new Wolf(60);
        carnivores.push_back(wolf);
    }
};

// Класс "Мир животных"
class AnimalWorld {
private:
    vector<Continent*> continents;
    vector<Herbivore*> herbivores;
    vector<Carnivore*> carnivores;

public:
    ~AnimalWorld() {
        cout << "Animal World destroyed\n";
        for (auto continent : continents) {
            delete continent;
        }
        for (auto herbivore : herbivores) {
            delete herbivore;
        }
        for (auto carnivore : carnivores) {
            delete carnivore;
        }
    }

    void AddContinent(Continent* continent) {
        continents.push_back(continent);
    }

    void PopulateWorld() {
        for (auto continent : continents) {
            continent->Populate(herbivores, carnivores);
        }
    }

    void MealsHerbivores() {
        cout << "Herbivores eat grass...\n";
        for (auto herbivore : herbivores) {
            if (herbivore->IsAlive()) {
                herbivore->EatGrass();
            }
        }
    }

    void NutritionCarnivores() {
        cout << "Harnivores hunting on herbivores...\n";
        for (auto carnivore : carnivores) {
            for (auto herbivore : herbivores) {
                if (herbivore->IsAlive()) {
                    carnivore->Eat(herbivore);
                }
            }
        }
    }
};

int main() {
    
    // Создание объекта мира животных
    AnimalWorld world;

    // Создание объектов континентов
    Africa* africa = new Africa;
    NorthAmerica* northAmerica = new NorthAmerica;

    // Добавление континентов в Мир животных
    world.AddContinent(africa);
    world.AddContinent(northAmerica);

    // Популяция континентов
    world.PopulateWorld();

    // Питание травоядных и плотоядных
    world.MealsHerbivores();
    world.NutritionCarnivores();

}

