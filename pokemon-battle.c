#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// struct recebe o nome dos golpes e o dano deles
typedef struct
{
    char name[50], move_1[50], move_2[50], move_3[50], move_4[50];
    int hp, hpMax, move_1dmg, move_2dmg, move_3dmg, move_4dmg;
} Pokemon;

// declaracao das funcoes
Pokemon * create_pokemon(char name[], int hp, char move_1[], int move_1dmg, char move_2[], int move_2dmg, char move_3[], int move_3dmg, char move_4[], int move_4dmg);
int battle(Pokemon * pokemon_1, Pokemon * pokemon_2);
int fight(Pokemon * pokemon_1, Pokemon * pokemon_2);
int bag(Pokemon * pokemon_1);
int rng(int randomNumber);
int attack(Pokemon * pokemon_1, Pokemon * pokemon_2, int option);
int opponentAtks(Pokemon * pokemon_1, Pokemon * pokemon_2);
bool didPokeFaint(Pokemon * pokemon_1);

int main (void)
{
    // pokemons criados
    Pokemon * pikachu = create_pokemon("Pikachu", 500, "Volt Tackle", 120, "Thunderbolt", 90, "Surf", 80, "Quick Attack", 40);
    Pokemon * charmander = create_pokemon("Charmander", 500, "Flamethrower", 90, "Thunderpunch", 75, "Dragonpulse", 85, "Crunch", 80);

    // BATALHA!!
    battle(pikachu, charmander);

    // libera os malloc da struct
    free(pikachu);
    free(charmander);

    return 0;
}

// tipo um construtor, pra criar os pokemons e passar os dados dele
Pokemon * create_pokemon(char name[], int hp, char move_1[], int move_1dmg, char move_2[], int move_2dmg, char move_3[], int move_3dmg, char move_4[], int move_4dmg)
{
    Pokemon * created_pokemon = malloc(sizeof(Pokemon)); // reserva espaco para o novo pokemon na memoria com ponteiro
    strcpy(created_pokemon->name, name);
    created_pokemon->hp = hp;
    strcpy(created_pokemon->move_1, move_1);
    strcpy(created_pokemon->move_2, move_2);
    strcpy(created_pokemon->move_3, move_3);
    strcpy(created_pokemon->move_4, move_4);

    created_pokemon->move_1dmg = move_1dmg;
    created_pokemon->move_2dmg = move_2dmg;
    created_pokemon->move_3dmg = move_3dmg;
    created_pokemon->move_4dmg = move_4dmg;

    created_pokemon->hpMax = 0;
    created_pokemon->hpMax += hp;

    return created_pokemon;
}

// inicia a batalha
int battle(Pokemon * pokemon_1, Pokemon * pokemon_2)
{
    printf("\nYou are challenged by a Pokemon Trainer, the trainer sent out %s.\nYou sent out your %s.\n-Go %s!", pokemon_2->name, pokemon_1->name, pokemon_1->name);
    printf("\n\n %s x %s \n", pokemon_1->name, pokemon_2->name);

    // loop infinito
    int option, i;
    i = 0;

    while(pokemon_1->hp > i || pokemon_2->hp > i)
    {   
        if(didPokeFaint(pokemon_1) == true)
        {
            printf("\n%s has fainted, you're out of Pokemon.\nPaid 500$ to Pokemon Trainer.\nNeed to run to Pokemon Center.\n", pokemon_1->name);
            return 0;
        }
        if(didPokeFaint(pokemon_2) == true)
        {
            printf("\nThe foe's %s has fainted.\n%s gained 230 Exp. Points!\nPokemon Trainer defeated! 500$ earned.\n\n", pokemon_2->name, pokemon_1->name);
            return 0;
        } 

        printf("\nCurrent life:\n\n%s = %d\t%s = %d\n\n", pokemon_1->name, pokemon_1->hp, pokemon_2->name, pokemon_2->hp);
        printf("What will %s do?\n", pokemon_1->name);
        printf("1. Fight\n");
        printf("2. Bag\t");
        printf("3. Run\n\n");
        scanf("%d", &option);

        if(option == 1)
        {
            fight(pokemon_1, pokemon_2);
        }
        else if(option == 2)
        {
            bag(pokemon_1);
            opponentAtks(pokemon_2, pokemon_1);
        }
        else if(option == 3)
        {
            printf("\nYou can't run from a Pokemon Battle.\n");
        }
        else
        {
            printf("\ninvalid option, try again:\n");
        }
    }

    return 0;
}

// mostra os golpes
int fight(Pokemon * pokemon_1, Pokemon * pokemon_2)
{
    int option;

    printf("\n1. %s\t2. %s\n3. %s\t4. %s\n5. Back \n\n", pokemon_1->move_1, pokemon_1->move_2, pokemon_1->move_3, pokemon_1->move_4);
    scanf("\n%d", &option);

    if(option == 5)
    {
        return 0;
    }

    attack(pokemon_1, pokemon_2, option);

    if(didPokeFaint(pokemon_2) == true)
    {
        // printf("\nThe foe's %s has fainted.\n%s gained 230 Exp. Points!\nPokemon Trainer defeated! 500$ earned.\n\n", pokemon_2->name, pokemon_1->name);
        return 0;
    }

    opponentAtks(pokemon_2, pokemon_1);

    return pokemon_2->hp;
}

// mostra os itens da mochila
int bag(Pokemon * pokemon_1)
{   
    int potion;
    int rest;
    rest = 0;
    potion = 150;

    pokemon_1->hp += potion;

    if(pokemon_1->hp < pokemon_1->hpMax)
    {
        printf("\nPotion used, restored %d HP of your poke.\n", potion);
    }

    else if(pokemon_1->hp > pokemon_1->hpMax)
    {
        rest = pokemon_1->hp - pokemon_1->hpMax;
        potion -= rest;
        printf("\nPotion used, restored %d, your poke is full again!\n", potion);
        pokemon_1->hp = pokemon_1->hpMax;
    }
    return pokemon_1->hp;
}

/*
calculos malucos feitos ate chegar na conclusao de como mostrar a diferenca de cura das pocoes

hpmax = 500
hpmax - hp = 50
hp(damaged) + potion
450(damaged) + 150 = 600 hp
                                                          
600 - 500 = 100     hp - maxhp = 100
150 - 100 = 50      potion - rest = 50
*/

// rng pra gerar os ataques inimigos
int rng(int randomNumber)
{
    srand(time(NULL));
    randomNumber = rand() % 4 + 1;

    return randomNumber;
}

// calculo dos ataques
int attack(Pokemon * pokemon_1, Pokemon * pokemon_2, int option)
{
    if(option == 1)
    {
        printf("\n%s used %s!\n", pokemon_1->name, pokemon_1->move_1);
        pokemon_2->hp -= pokemon_1->move_1dmg;
    }
    else if(option == 2)
    {
        printf("\n%s used %s!\n", pokemon_1->name, pokemon_1->move_2);
        pokemon_2->hp -= pokemon_1->move_2dmg;
    }
    else if(option == 3)
    {
        printf("\n%s used %s!\n", pokemon_1->name, pokemon_1->move_3);
        pokemon_2->hp -= pokemon_1->move_3dmg;
    }
    else if(option == 4)
    {
        printf("\n%s used %s!\n", pokemon_1->name, pokemon_1->move_4);
        pokemon_2->hp -= pokemon_1->move_4dmg;
    }
    else
    {
        printf("\ninvalid option, try again:\n");
    }

    return pokemon_2->hp;
}

// ataque do adversario
int opponentAtks(Pokemon * pokemon_1, Pokemon * pokemon_2)
{
    int i;
    i = 0;
    i += rng(i);

    attack(pokemon_1, pokemon_2, i);

    return pokemon_2->hp;
}

// descobrir se o pokemon ainda esta vivo
bool didPokeFaint(Pokemon * pokemon_1)
{   
    int i = 0;
    bool x, y;
    x = true;
    y = false;

    if(pokemon_1->hp <= i)
    {      
        return x;
    }
    else
    {
        return y;
    }
}

// ideia: implementar a troca de pokemons