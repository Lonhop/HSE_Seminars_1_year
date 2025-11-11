#include <iostream>
#include<vector>
#include<string>

enum class StatusEffect{
    POISONED = 0,
    STUNNED = 1 << 0,
    INVISIBLE = 1 << 1,
    INVINCIBLE = 1 << 2,
    BURNING = 1 << 3,
    FROZEN = 1 << 4,
    BLESSED = 1 << 5,
    CURSED = 1 << 6

};

StatusEffect operator|(StatusEffect per_1, StatusEffect per_2) {
    return (StatusEffect)((int) (per_1) | (int) (per_2));
}

StatusEffect operator&(StatusEffect per_1, StatusEffect per_2) {
    return (StatusEffect)((int) (per_1) & (int) (per_2));
}

StatusEffect operator~(StatusEffect per_1) {
    return (StatusEffect)(~(int) (per_1));
}

bool is_allowed(StatusEffect a, StatusEffect b) {
    if (a == StatusEffect::BURNING && b == StatusEffect::FROZEN
        || a == StatusEffect::FROZEN && b == StatusEffect::BURNING
        || a == StatusEffect::INVINCIBLE && b == StatusEffect::CURSED
        || b == StatusEffect::INVINCIBLE && a == StatusEffect::CURSED)
        return false;
    return true;
}

struct Character {
    std::string name;
    std::vector<StatusEffect> status_effect;
};

bool HasStatus ( const StatusEffect& got, const StatusEffect& check) {
    if ((got & check) == check) {
        return true;
    }
    return false;
}

void AddStatus(std::vector<Character>& characters) {
    StatusEffect add = StatusEffect::BURNING;
    for (auto& character : characters) { // reference
        std::vector<StatusEffect> to_add;
        for (auto got : character.status_effect) {
            if (is_allowed(got, add))
                to_add.push_back(add);
        }
        character.status_effect.insert(
            character.status_effect.end(),
            to_add.begin(), to_add.end()
        );
    }
}

void PrintStatus(const std::vector<Character>& characters) {
    for (const auto& character : characters) {
        std::cout << character.name << ": ";
        for (auto const effect : character.status_effect) {
            switch (effect) {
                case StatusEffect::POISONED:
                    std::cout << "Poisoned\t";
                    break;
                case StatusEffect::STUNNED:
                    std::cout << "Stunned\t";
                    break;
                case StatusEffect::INVISIBLE:
                    std::cout << "Invisible\t";
                    break;
                case StatusEffect::INVINCIBLE:
                    std::cout << "Invincible\t";
                    break;
                case StatusEffect::BURNING:
                    std::cout << "Burning\t";
                    break;
                case StatusEffect::FROZEN:
                    std::cout << "Frozen\t";
                    break;
                case StatusEffect::BLESSED:
                    std::cout << "Blessed\t";
                    break;
                case StatusEffect::CURSED:
                    std::cout << "Cursed\t";
                    break;
                default:
                    std::cout << "No effects";

            }
        }
        std::cout << '\n';
    }
}


int main() {
    std::vector<Character> characters = {
        {"Mike", {StatusEffect::BURNING}},
        {"Winston", {StatusEffect::FROZEN}},
        {"SoldierBoy", {StatusEffect::INVINCIBLE}}
    };
    AddStatus(characters);
    PrintStatus(characters);
    return 0;
}