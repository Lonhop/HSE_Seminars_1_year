#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <utility>

struct Dish {
    std::string name;
    std::set<std::string> ingredients;
};

using Ingredients = std::map<std::string, int>;
using Dishes = std::vector<Dish>;
using DishesIngredients = std::pair<Dishes&, Ingredients&>;

Ingredients readIngredients(std::istream& is) {
    Ingredients result;
    size_t m = 0;
    if (!(is >> m)) {
        return result;
    }
    for (size_t i = 0; i < m; ++i) {
        std::string name;
        int calories = 0;
        is >> name >> calories;
        result[name] = calories;
    }
    return result;
}

Dishes readDishes(std::istream& is) {
    Dishes result;
    size_t n = 0;
    if (!(is >> n)) {
        return result;
    }
    for (size_t i = 0; i < n; ++i) {
        Dish dish;
        size_t k = 0;
        is >> dish.name >> k;
        for (size_t j = 0; j < k; ++j) {
            std::string ingredient;
            is >> ingredient;
            dish.ingredients.insert(ingredient);
        }
        result.push_back(dish);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Dish& dish) {
    os << dish.name << ": ";
    bool first = true;
    for (const std::string& ingr : dish.ingredients) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << ingr;
    }
    return os;
}

int calcCalories(const Dish& dish, const Ingredients& ingredients) {
    int total = 0;
    for (const std::string& ingr : dish.ingredients) {
        auto it = ingredients.find(ingr);
        if (it != ingredients.end()) {
            total += it->second;
        }
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const DishesIngredients& di) {
    const Dishes& dishes = di.first;
    const Ingredients& ingredients = di.second;

    for (size_t i = 0; i < dishes.size(); ++i) {
        os << dishes[i] << "; " << calcCalories(dishes[i], ingredients);
        if (i + 1 < dishes.size()) {
            os << '\n';
        }
    }
    return os;
}

struct Comparator {
    const Ingredients& ingrs;
    Comparator(const Ingredients& i) : ingrs(i) {}
    bool operator()(const Dish& a, const Dish& b) const {
        return calcCalories(a, ingrs) > calcCalories(b, ingrs);
    }
};

void sortDishesByCalories(DishesIngredients& di) {
    std::sort(di.first.begin(), di.first.end(), Comparator(di.second));
}