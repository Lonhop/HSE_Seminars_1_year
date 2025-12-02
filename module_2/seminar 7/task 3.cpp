#include <iostream>
#include <string>

class Character {
    struct Stats {
        int hp;
        int attack;
        int defense;
    };
    std::string name;
    Stats stats;
public:
    Character(std::string name, int hp, int attack, int defense) {
        this->name = name;
        this->stats.attack = attack;
        this->stats.hp = hp;
        this->stats.defense = defense;
    }
    Character(const Character& other) {
        this->name = other.name;
        this->stats.hp = other.stats.hp;
        this->stats.attack = other.stats.attack;
        this->stats.defense = other.stats.defense;
    }
    Character& operator=(const Character& other) {
        this->name = other.name;
        this->stats.attack = other.stats.attack;
        this->stats.hp = other.stats.hp;
        this->stats.defense = other.stats.defense;

        return *this;
    }

    void hit(Character& target) {
        int damage = this->stats.attack - target.stats.defense;
        damage = damage < 0 ? 0 : damage;
        target.stats.hp -= damage;
        target.stats.hp = target.stats.hp < 0 ? 0 : target.stats.hp;
        std::cout << this->name << " hits " << target.name << " for " << damage << " damage, " << target.name << " has " << target.stats.hp << " HP\n";

    }
    void heal(int amount) {
        this->stats.hp += amount;
        std::cout << this->name << " was healed for " << amount << " HP\n";
    }
    void print() const {
        std::cout << "Character: " << this->name << '\n'
        << "HP: " << this->stats.hp << '\n'
        << "Attack: " << this->stats.attack << '\n'
        << "Defense: " << this->stats.defense << "\n\n";
    }
};

int main() {
    Character a("Hero", 100, 15, 5);
    Character b("Goblin", 40, 8, 2);

    a.hit(b);
    b.print();
    return 0;
}