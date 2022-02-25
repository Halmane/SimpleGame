#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

struct field {
    char point = '.';
    struct character {
        std::string name;
        int hp;
        int def;
        int attack;
        int x;
        int y;
        bool alive = 1;
    };
};

void arrangement(field field[20][20], field::character &enemy) {
    enemy.x = rand() % 20;
    enemy.y = rand() % 20;
    while (field[enemy.x][enemy.y].point != '.') {
        enemy.x = rand() % 20;
        enemy.y = rand() % 20;
    }
    field[enemy.x][enemy.y].point = 'E';
}

void show_field(field field[20][20]) {
    std::cout << "  ";
    for (int i = 0; i < 20; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < 20; i++) {
        std::cout << "||";
        for (int j = 0; j < 20; j++) {
            std::cout << field[i][j].point;
        }
        std::cout << "||";
        std::cout << std::endl;
    }
    std::cout << "  ";
    for (int i = 0; i < 20; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void arrangement_player(field field[20][20], field::character &player) {
    std::cout << "Enter character name: ";
    std::cin >> player.name;
    std::cout << "Enter character hp: ";
    std::cin >> player.hp;
    std::cout << "Enter character def: ";
    std::cin >> player.def;
    std::cout << "Enter character attack: ";
    std::cin >> player.attack;

    std::cout << "Enter the x and y coordinates for the character:";
    std::cin >> player.x >> player.y;
    while (field[player.x][player.y].point != '.') {
        std::cout << "Error!Try again!" << std::endl;
        std::cout << "Enter the x and y coordinates for the character:";
        std::cin >> player.x >> player.y;
    }
    field[player.x][player.y].point = 'P';

    show_field(field);
}

void attack(field::character &attacking, field::character &attacked) {
    attacked.def -= attacking.attack;
    if (attacked.def < 0) {
        attacked.hp += attacked.def;
    }
    if (attacked.hp <= 0) {
        attacked.alive = 0;
    }
}

void enemy_movement(field field[20][20], field::character enemy[5], field::character &player) {
    for (int i = 0; i < 5; i++) {
        if (enemy[i].alive == 1) {
            int move = rand() % 3;
            if (move == 0 and enemy[i].x - 1 >= 0) {
                if (field[enemy[i].x - 1][enemy[i].y].point == '.') {
                    field[enemy[i].x][enemy[i].y].point = '.';
                    enemy[i].x = enemy[i].x - 1;
                    field[enemy[i].x][enemy[i].y].point = 'E';
                } else if (field[enemy[i].x - 1][enemy[i].y].point == 'P') {
                    attack(enemy[i], player);
                    std::cout << enemy[i].name << " attacked " << player.name << std::endl;
                    if (player.alive == 0) {
                        std::cout << enemy[i].name << " kill " << player.name << std::endl;
                    } else std::cout << player.name << " have " << player.hp << " hp" << std::endl;
                }
            } else if (move == 1 and enemy[i].y + 1 < 20) {
                if (field[enemy[i].x][enemy[i].y + 1].point == '.') {
                    field[enemy[i].x][enemy[i].y].point = '.';
                    enemy[i].y = enemy[i].y + 1;
                    field[enemy[i].x][enemy[i].y].point = 'E';
                } else if (field[enemy[i].x][enemy[i].y + 1].point == 'P') {
                    attack(enemy[i], player);
                    std::cout << enemy[i].name << " attacked " << player.name << std::endl;
                    if (player.alive == 0) {
                        std::cout << enemy[i].name << " kill " << player.name << std::endl;
                    } else std::cout << player.name << " have " << player.hp << " hp" << std::endl;
                }
            } else if (move == 2 and enemy[i].x + 1 < 20) {
                if (field[enemy[i].x + 1][enemy[i].y].point == '.') {
                    field[enemy[i].x][enemy[i].y].point = '.';
                    enemy[i].x = enemy[i].x + 1;
                    field[enemy[i].x][enemy[i].y].point = 'E';
                } else if (field[enemy[i].x + 1][enemy[i].y].point == 'P') {
                    attack(enemy[i], player);
                    std::cout << enemy[i].name << " attacked " << player.name << std::endl;
                    if (player.alive == 0) {
                        std::cout << enemy[i].name << " kill " << player.name << std::endl;
                    } else std::cout << player.name << " have " << player.hp << " hp" << std::endl;
                }
            } else if (move == 3 and enemy[i].y - 1 >= 0) {
                if (field[enemy[i].x][enemy[i].y - 1].point == '.') {
                    field[enemy[i].x][enemy[i].y].point = '.';
                    enemy[i].y = enemy[i].y - 1;
                    field[enemy[i].x][enemy[i].y].point = 'E';
                } else if (field[enemy[i].x][enemy[i].y - 1].point == 'P') {
                    attack(enemy[i], player);
                    std::cout << enemy[i].name << " attacked " << player.name << std::endl;
                    if (player.alive == 0) {
                        std::cout << enemy[i].name << " kill " << player.name << std::endl;
                    } else std::cout << player.name << " have " << player.hp << " hp" << std::endl;
                }
            }
        }
    }
}

int enemy_find(field::character enemy[5], int x, int y) {
    for (int i = 0; i < 5; i++) {
        if (enemy[i].x == x and enemy[i].y == y) {
            return i;
        }
    }
    return -1;
}

void info(field::character enemy) {
    std::cout << enemy.name << std::endl;
    std::cout << "HP: " << enemy.hp << std::endl;
    std::cout << "Def: " << enemy.def << std::endl;
    std::cout << "Attack: " << enemy.attack << std::endl;
    if (enemy.alive == 1) {
        std::cout << "Coordinates: " << enemy.x << " " << enemy.y << std::endl;
    } else std::cout << "Dead" << std::endl;
}


void player_movement(field field[20][20], field::character &player, field::character enemy[5]) {
    if (player.alive == 1) {
        std::cout
                << "Enter direction(top, right, bottom, left) or enter info to find out your or enemies stats or save/load:";
        std::string command;
        std::cin >> command;
        if (command == "top" and player.x - 1 >= 0) {
            if (field[player.x - 1][player.y].point == '.') {
                field[player.x][player.y].point = '.';
                player.x = player.x - 1;
                field[player.x][player.y].point = 'P';
            } else if (field[player.x - 1][player.y].point == 'E') {
                int enemyNumber = enemy_find(enemy, player.x - 1, player.y);
                attack(player, enemy[enemyNumber]);
                std::cout << "The player attacked the enemy #" << enemyNumber << std::endl;
                if (enemy[enemyNumber].alive == 0) {
                    std::cout << "The player kill the enemy #" << enemyNumber << std::endl;
                    field[player.x - 1][player.y].point = '.';
                }
            }
        } else if (command == "right" and player.y + 1 < 20) {
            if (field[player.x][player.y + 1].point == '.') {
                field[player.x][player.y].point = '.';
                player.y = player.y + 1;
                field[player.x][player.y].point = 'P';
            } else if (field[player.x][player.y + 1].point == 'E') {
                int enemyNumber = enemy_find(enemy, player.x, player.y + 1);
                attack(player, enemy[enemyNumber]);
                std::cout << "The player attacked the " << enemy[enemyNumber].name << std::endl;
                if (enemy[enemyNumber].alive == 0) {
                    std::cout << "The player kill the " << enemy[enemyNumber].name << std::endl;
                    field[player.x][player.y + 1].point = '.';
                }
            }
        } else if (command == "bottom" and player.x + 1 < 20) {
            if (field[player.x + 1][player.y].point == '.') {
                field[player.x][player.y].point = '.';
                player.x = player.x + 1;
                field[player.x][player.y].point = 'P';
            } else if (field[player.x + 1][player.y].point == 'E') {
                int enemyNumber = enemy_find(enemy, player.x + 1, player.y);
                attack(player, enemy[enemyNumber]);
                std::cout << "The player attacked the " << enemy[enemyNumber].name << std::endl;
                if (enemy[enemyNumber].alive == 0) {
                    std::cout << "The player kill the " << enemy[enemyNumber].name << std::endl;
                    field[player.x + 1][player.y].point = '.';
                }
            }
        } else if (command == "left" and player.y - 1 >= 0) {
            if (field[player.x][player.y - 1].point == '.') {
                field[player.x][player.y].point = '.';
                player.y = player.y - 1;
                field[player.x][player.y].point = 'P';
            } else if (field[player.x][player.y - 1].point == 'E') {
                int enemyNumber = enemy_find(enemy, player.x, player.y - 1);
                attack(player, enemy[enemyNumber]);
                std::cout << "The player attacked the " << enemy[enemyNumber].name << std::endl;
                if (enemy[enemyNumber].alive == 0) {
                    std::cout << "The player kill the " << enemy[enemyNumber].name << std::endl;
                    field[player.x][player.y - 1].point = '.';
                }
            }
        } else if (command == "info") {
            std::cout << "Enter enemy number(or -1 player info): ";
            int enemyNumber;
            std::cin >> enemyNumber;
            if (enemyNumber >= 0 and enemyNumber < 5)
                info(enemy[enemyNumber]);
            else if (enemyNumber == -1) {
                info(player);
            } else std::cout << "Invalid number" << std::endl;
            player_movement(field, player, enemy);
        } else if (command == "save") {

        } else if (command == "load") {

        } else {
            std::cout << "Error command!!" << std::endl;
            player_movement(field, player, enemy);
        }
    }

}

int alive_enemy(field::character enemy[5]) {
    int alive_enemy = 0;
    for (int i = 0; i < 5; i++) {
        if (enemy[i].alive == 1)
            alive_enemy++;
    }
    return alive_enemy;
}


int main() {
    std::srand(std::time(nullptr));
    field field[20][20];
    field::character enemy[5];
    for (int i = 0; i < 5; i++) {
        enemy[i].name = "Enemy #" + std::to_string(i);
        enemy[i].attack = rand() % 16 + 15;
        enemy[i].hp = rand() % 101 + 50;
        enemy[i].def = rand() % 51;
        arrangement(field, enemy[i]);
    }
    show_field(field);

    field::character player;
    arrangement_player(field, player);

    while (player.alive != 0 or alive_enemy(enemy) != 0) {
        enemy_movement(field, enemy, player);
        if (player.alive == 0) {
            std::cout << "Game over!" << std::endl;
            return 1;
        } else {
            show_field(field);
            player_movement(field, player, enemy);
        }
        if (alive_enemy(enemy) == 0) {
            std::cout << "You win!" << std::endl;
            return 0;
        }
    }
}