#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ability {
protected:
    string name;
    int damage;
    int manaCost;

public:
    Ability(const string& name, int damage, int manaCost)
        : name(name), damage(damage), manaCost(manaCost) {}

    void execute() {
        cout << "Executing ability: " << name << endl;
    }

    string getName() const {
        return name;
    }

    int getDamage() const {
        return damage;
    }

    int getManaCost() const {
        return manaCost;
    }
};

class Character {
protected:
    string name;
    int health;
    int level;
    vector<Ability*> abilities;

public:
    Character(const string& name, int health, int level)
        : name(name), health(health), level(level) {}

    virtual void useAbility(int abilityIndex) {
        if (abilityIndex < 0 || abilityIndex >= abilities.size()) {
            cout << "Invalid ability index!" << endl;
            return;
        }

        Ability* ability = abilities[abilityIndex];

        if (ability->getManaCost() > 0) {
            cout << name << " used " << ability->getName() << " (Damage: " << ability->getDamage()
                 << ", Mana Cost: " << ability->getManaCost() << ")." << endl;
        } else {
            cout << name << " used " << ability->getName() << " (Damage: " << ability->getDamage()
                 << ")." << endl;
        }

        health -= ability->getDamage();
    }

    void addAbility(Ability* ability) {
        abilities.push_back(ability);
    }

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    int getLevel() const {
        return level;
    }

    const vector<Ability*>& getAbilities() const {
        return abilities;
    }
};

class Warrior : public Character {
public:
    Warrior(const string& name, int health, int level)
        : Character(name, health, level) {
        abilities.push_back(new Ability("Slash", 30, 0));
        abilities.push_back(new Ability("Bash", 40, 10));
    }
};

class Archer : public Character {
public:
    Archer(const string& name, int health, int level)
        : Character(name, health, level) {
        abilities.push_back(new Ability("Shoot", 25, 0));
        abilities.push_back(new Ability("Multi-shot", 35, 15));
    }
};

class Mage : public Character {
public:
    Mage(const string& name, int health, int level)
        : Character(name, health, level) {
        abilities.push_back(new Ability("Fireball", 50, 20));
        abilities.push_back(new Ability("Frostbolt", 45, 15));
    }
};

int main() {
    Warrior warrior("Garen", 100, 1);
    Archer archer("Varus", 80, 1);
    Mage mage("Jaina", 70, 1);

    warrior.useAbility(0);
    archer.useAbility(1);
    mage.useAbility(0);

    cout << warrior.getName() << "'s Health: " << warrior.getHealth() << endl;
    cout << archer.getName() << "'s Health: " << archer.getHealth() << endl;
    cout << mage.getName() << "'s Health: " << mage.getHealth() << endl;

    // Cleanup dynamically allocated abilities
    for (Ability* ability : warrior.getAbilities()) {
        delete ability;
    }
    for (Ability* ability : archer.getAbilities()) {
        delete ability;
    }
    for (Ability* ability : mage.getAbilities()) {
        delete ability;
    }

    return 0;
}