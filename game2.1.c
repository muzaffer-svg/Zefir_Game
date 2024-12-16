#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_TRAPS 4 

typedef struct {
    char name[50];
    int health;
    int attack_power;
    int inventory_count;
    char inventory[7][50];  
} Player;// oyuncu yapisi

typedef struct {
    char name[50];
    int health;
    int attack_power;
} Creature; // yaratıık(canavar) yapısı

Creature creatures[] = {
    {"Fire Spirit", 120, 35},
    {"Dragon", 170, 55},
    {"T-Rex", 190, 60},
    {"Optimus Prime", 220, 65},
    {"Anaconda", 250, 75}
}; //canavar listesi kartları

typedef struct {
    char* name;           
    int attack_boost;     
} Item; // item yapısı

typedef struct {
    char* description; 
    Item items[10];       
    int item_count;       
} Room; // oda yapısı

void initialize_room(Room* room, const char* description, Item items[], int item_count) {

    room->description = (char*)malloc(strlen(description) + 1);
    strcpy(room->description, description);
    room->item_count = item_count;

    for (int i = 0; i < item_count; i++) {
        room->items[i] = items[i];
    }
} // odaları bu fonksıyona göre baslatıyoruz

void look(Room* room) {
    printf("\nRoom Description: %s\n", room->description);
    if (room->item_count > 0) {
        printf("Items in the room:\n");
        for (int i = 0; i < room->item_count; i++) {
            printf("- %s (Attack Boost: +%d)\n", room->items[i].name, room->items[i].attack_boost);
        }
    } else {
        printf("There are no items in this room.\n");
    }
}// look metodu oyunuc odaya geldiğinde odadaki itemlere bakmak için


void remove_item(Player* player, const char* item_name) { // oyuncu istemediği itemleri bırakaır bu fonksiyon ile
    
    int found = 0;
    for (int i = 0; i < player->inventory_count; i++) {
        if (strcmp(player->inventory[i], item_name) == 0) {
            
            for (int j = i; j < player->inventory_count - 1; j++) {
                strcpy(player->inventory[j], player->inventory[j + 1]);
            }
            player->inventory_count--; 
            printf("Item '%s' has been removed from your inventory.\n", item_name);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Item '%s' not found in your inventory.\n", item_name);
    }
}

void cleanup_room(Room* room) {
    free(room->description); 
} // odalari bellekten tahsis etme serbest bırakma metodu



void pickup(Room* room, Player* player, const char* item_name) { // oyuncu envanteri boş isse odadaki itemleri almak için kullandıgı fonksiyon

    if (player->inventory_count >= 5) {
        printf("Your inventory is full! You cannot pick up any more items.\n");
        return;
    }

    int item_found = 0; 
    int attack_boost = 0; 

    for (int i = 0; i < room->item_count; i++) {
        if (strcmp(room->items[i].name, item_name) == 0) {
            
            item_found = 1;
            attack_boost = room->items[i].attack_boost; 

            if (player->inventory_count < 5) {
                strcpy(player->inventory[player->inventory_count], item_name);
                player->inventory_count++;  
                player->attack_power += attack_boost;
                printf("You picked up %s. It increased your attack power by +%d.\n", item_name, attack_boost);
            }

            for (int j = i; j < room->item_count - 1; j++) {
                room->items[j] = room->items[j + 1];
            }
            room->item_count--;
            return;  
        }
    }

    if (!item_found) {
        printf("The item '%s' is not in this room.\n", item_name);
    }
}

void clear_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}



void save_game(Player* player,int* completed_traps) { // oyunu burda kaydediyoruz
    FILE* file = fopen("save_game.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }
    fprintf(file, "%s\n", player->name);   // oyuncu özelliklir kaydediliyor
    fprintf(file, "%d\n", player->health);  
    fprintf(file, "%d\n", player->attack_power);  
    fprintf(file, "%d\n", player->inventory_count); 

    for (int i = 0; i < player->inventory_count; i++) {
        fprintf(file, "%s\n", player->inventory[i]);  
    }

    for (int i = 0; i < MAX_TRAPS; i++) { // geçtiği tamamladığı tuzaklar kaydedilir
        fprintf(file, "%d\n", completed_traps[i]); 
    }
    fclose(file);  
    printf("Game saved successfully!\n");
}

int load_game(Player* player,int* completed_traps) { // önceki oynadığı kaydettiği oyun tekrardan yüklenir
    FILE* file = fopen("save_game.txt", "r");
    if (file == NULL) {
        printf("No saved game found! Starting a new game.\n");
        return 0;
    }

    fgets(player->name, sizeof(player->name), file);
    player->name[strcspn(player->name, "\n")] = '\0'; 

    fscanf(file, "%d", &player->health); 
    fscanf(file, "%d", &player->attack_power);  
    fscanf(file, "%d", &player->inventory_count); 
    for (int i = 0; i < player->inventory_count; i++) {
        fscanf(file, "%s", player->inventory[i]); 
    }

    for (int i = 0; i < MAX_TRAPS; i++) {
        fscanf(file, "%d", &completed_traps[i]);
    }

    fclose(file); 
    printf("Game loaded successfully!\n");
    return 1; 
}


int room5_traps(Player* player, Room* room,int* completed_traps) { // tuzak odası
    printf("\n*** Room 5: Trap Room .The trap room. be careful every step of the way, boooom, you could get caught in a trap.***\n");
    char look_choice[10];
    printf("Do you want to take a closer look at the room? You can write 'look' : ");
    fgets(look_choice, sizeof(look_choice), stdin);
    look_choice[strcspn(look_choice, "\n")] = '\0'; 
    
    if (strcmp(look_choice, "look") == 0) {
        look(room);
    } else {
        printf("You didn't want to look at the room, you were a big novice..\n");
    }

   int correct_answer = 9;  
   int player_guess;

  printf("\nTrap 1: Solve the following logic question:\n");
  printf("If a farmer has 17 sheep and all but 9 run away, how many are left?\n");

  while (1) {
    printf("Enter your answer: ");
    if (scanf("%d", &player_guess) != 1) {
        clear_buffer();
        printf("If you continue to make invalid entries, you will lose 5 health points. You've already lost .\n");
        player->health -= 5;
        continue;
    }
    clear_buffer();

    if (player_guess == correct_answer) {
        printf("Correct! Trap 1 deactivated.\n");
        printf("Your health is now: %d\n", player->health);
        if(!(completed_traps[0])){
            completed_traps[0]= 1;
            pickup(room, player, "Helmet of Wisdom");
            
        }else{
            printf("You've already taken the Helmet of Wisdom ");
        }
        break;
       
    } else {
        printf("You should think a little more logically\n");
        printf("Wrong! You lost -5 health points.\n");
        player->health -= 5;
    }
  }

         
char correct_box = 'A' + (rand() % 3); 
char chosen_box;

while (1) {
    printf("\nTrap 2: Listen to your heart and choose the right box (A, B, or C): ");
    scanf(" %c", &chosen_box);
    clear_buffer();
    if (chosen_box >= 'a' && chosen_box <= 'z') {
        chosen_box -= 32; 
    }

    if (chosen_box == 'A' || chosen_box == 'B' || chosen_box == 'C') {
        if (chosen_box == correct_box) {
            printf("Correct! Trap 2 deactivated.\n");
            printf("The box contains a health boost! You've been kissed by health magic.\n");
            player->health += 10; 
            printf("Your health is now: %d\n", player->health);
            if(!(completed_traps[1])){
               completed_traps[1] = 1;
               pickup(room, player, "Shield of Valor");
            
        }else{
            printf("You've already taken the Shield of Valor");
        }
        break;
            
        } else {
            printf("Wrong! You opened the box and found a bomb! run runn 3 2 1 .... It exploded!\n");
            printf("You lost 5 health points.\n");
            player->health -= 5; 
        }
    } else {
        printf("Invalid input! You lost 8 health points.\n");
        player->health -= 8;
    }
}

const char* symbols[] = {"@", "#", "$","&"};
const char* correct_sequence[3];
char player_guess_sequence[3][10];


for (int i = 0; i < 3; i++) {
    correct_sequence[i] = symbols[rand() % 3];
}

while (1) {
    printf("\nTrap 3:We will learn my strength of memory ability. Enter the correct sequence of symbols (e.g., @ # £ $):\n");

    for (int i = 0; i < 3; i++) {
        printf("Enter symbol %d: ", i + 1);
        if (scanf("%s", player_guess_sequence[i]) != 1) {
            clear_buffer();
            printf("You used a symbol that we don't have, be a little more careful.You lost 5 health points.\n");
            player->health -= 5; 
            continue; 
        }
    }
    clear_buffer();

    int correct = 1;
    for (int i = 0; i < 3; i++) {
        if (strcmp(player_guess_sequence[i], correct_sequence[i]) == 0) {
            printf("Symbol %d is correct: %s\n", i + 1, correct_sequence[i]);
        } else {
            printf("Symbol %d is incorrect. Try again.\n", i + 1);
            correct = 0; 
        }
    }

    if (correct) {
        printf("Correct! Trap 3 deactivated.\n");
        printf("Your health is now: %d\n", player->health);
        if(!(completed_traps[2])){
            completed_traps[2] = 1;
            pickup(room, player, "Armor of Light");
            
        }else{
            printf("You've already taken the Armor of Light ");
        }
        break;
    } else {
        printf("You feel weaker as the toxic air takes its toll on your health.\n");
        printf("Wrong! You lost 5 health points.\n");
        player->health -= 5;  
    }
}

    while (1) {
        printf("\nWhere would you like to go next?\n");
        printf(" 'move6' to go to Room 6 or 'moveup' to return to the starting room: ");
        char move_choice[20];
        scanf("%s", move_choice);
        clear_buffer();

        if (strcmp(move_choice, "move6") == 0) {
            printf("You chose to move to Room 6. Good luck! , BEWARE OF MONSTERS :)\n");
            return 6; 
        } else if (strcmp(move_choice, "moveup") == 0) {
            printf("You chose to return to the starting room.\n");  
            return -1;  
        } else {
            printf("I don't understand where you want to go, please write another 'move6' or 'moveup'.\n");
        }
    }
}


int room6_creature_cards(Player* player, Room* room, Creature** selected_creature_from_room6,int* completed_traps) {// yaratık secme odası ve elmas kılıc alma sansı
    printf("\n*** Room 6: Creature Card Room ***\n");
    printf("Each creature has its own health and attack power. Choose wisely!\n");
    char look_choice[10];
    printf("Do you want to take a closer look at the room? You can write'look' to examine: ");
    fgets(look_choice, sizeof(look_choice), stdin);
    look_choice[strcspn(look_choice, "\n")] = '\0';
    
    if (strcmp(look_choice, "look") == 0) {
        look(room); 
    } else {
        printf("You didn't want to look at the room, you were a big novice..\n");
    }

    for (int i = 0; i < 5; i++) {
        printf("%d. Card %d\n", i + 1, i + 1);
    }

    int card_choice;
    while (1) {
        printf("Enter the number of the card you choose (1-5): ");
        if (scanf("%d", &card_choice) != 1 || card_choice < 1 || card_choice > 5) {
            clear_buffer(); 
            printf("Invalid choice. Please choose a card between 1 and 5.\n");
        } else {
            clear_buffer();
            break;
        }
    }

    *selected_creature_from_room6 = &creatures[card_choice - 1];
    printf("\nYou chose Card %d: You will fight %s (Health: %d, Attack Power: %d)\n",
           card_choice, (*selected_creature_from_room6)->name, (*selected_creature_from_room6)->health, (*selected_creature_from_room6)->attack_power);

    printf("\nBefore leaving the room, solve the following riddle to earn the Diamond Sword!\n");
    printf("You have 3 chances to get it right.\n");
    printf("\nRiddle: I'm not alive, but I can grow. I don't have lungs, but I need air. What am I?\n");

int attempts = 3;  
char correct_answer[] = "fire";  
char player_answer[20];

while (attempts > 0) {
    printf("Your answer: ");
    scanf("%19s", player_answer); 
    clear_buffer();

    for (int i = 0; player_answer[i]; i++) {
        if (player_answer[i] >= 'A' && player_answer[i] <= 'Z') {
            player_answer[i] += 32;
        }
    }

    if (strcmp(player_answer, correct_answer) == 0) {
        printf(" WOOW Correct! You solved the riddle, you're a smart guy..\n");
        printf("You gain 10 health points!\n");
        player->health += 10; 
        printf("Your current health: %d\n", player->health);
        if(!(completed_traps[3])){
            completed_traps[3] = 1;
            pickup(room, player, "Diamond Sword");  
            
        }else{
            printf("You've already taken the Diamond Sword");
        }
        break;
    } else {
        attempts--;
        if (attempts > 0) {
            printf("Wrong answer! You have %d attempts left.\n", attempts);
        } else {
            printf("Wrong answer! You have no attempts left.\n");
        }
    }
}

if (attempts == 0) {
    printf(" Ovvv, it seems that you haven't solved the riddle and you missed the chance to get the Diamond Sword.\n");
}

    while (1) {
        printf("\nWhere would you like to go next?\n");
        printf("Type 'move3' to go to Room 3 or 'moveup' to return to the starting room: ");
        char move_choice[20];
        scanf("%19s", move_choice);
        clear_buffer();

        if (strcmp(move_choice, "move3") == 0) {
            printf("You chose to move to Room 3. Good luck!\n");           
            return 3; 
        } else if (strcmp(move_choice, "moveup") == 0) {
            printf("You chose to return to the starting room.\n"); 
            return -1;
        } else {
            printf("I don't understand where you want to go, please write another 'move3' or 'moveup'.\n");
        }
    }
}

int selected_items[10] = {0};

// Room 3
int room3_chest(Player* player, Room* room, Item room3_items[]) { // istediği itemleri alır veya bırakır
     printf("\n*** Room 3: Treasure Chest ***\n");
    printf("You have unlocked the chest! Inside, you find some items.\n");

    char look_choice[10];
    printf("Do you want to take a closer look at the chest? You can write 'look' to examine: ");
    fgets(look_choice, sizeof(look_choice), stdin);
    look_choice[strcspn(look_choice, "\n")] = '\0';

    if (strcmp(look_choice, "look") == 0) {
        printf("\nInside the chest, you  will see valuable items from each other:\n");
        for (int i = 0; i < 10; i++) {
            printf("%d. %s (Attack Boost: %d)\n", i + 1, room3_items[i].name, room3_items[i].attack_boost);
        }
    }
    else {
        printf("You didn't want to look at the room, you were a big novice..\n");
    }
        
        while (player->inventory_count < 5 && player->health > 0) {
            int item_choice;
            printf("\nEnter the number of the item you want to take (1-10), or 0 to stop: ");
            scanf("%d", &item_choice);
            getchar(); 

            if (item_choice == 0) {
                printf("You decided not to take any more items.\n");
                break;
            }

            if (item_choice < 1 || item_choice > 10) {
                printf("There is no item belonging to that number, please enter a valid number (between 1 and 10).\n");
                continue;
            }

            Item selected_item = room3_items[item_choice - 1];
            const char* item_name = selected_item.name;
            int attack_boost = selected_item.attack_boost;

            
            if (player->health < attack_boost) {
                printf("You don't have enough health to take %s.\n", item_name);
                continue;
            }

           
            player->health -= 5;
            pickup(room, player, item_name);

            printf("You have taken the item: %s (Attack Boost: %d)\n", item_name, attack_boost);

            if (player->inventory_count == 5) {
                printf("Your inventory is now full. No more items can be added.\n");
                break;
            }
        }
     
    if (player->inventory_count > 0) {
        char remove_choice[10];
        printf("\nWould you like to remove any item from your inventory? Type 'yes' or 'no': ");
        fgets(remove_choice, sizeof(remove_choice), stdin);
        remove_choice[strcspn(remove_choice, "\n")] = '\0'; 

        if (strcmp(remove_choice, "yes") == 0) {
            
            while (1) {
                printf("\nEnter the name of the item you want to remove (or type 'enouhg' to finish): ");
                char item_to_remove[50];
                fgets(item_to_remove, sizeof(item_to_remove), stdin);
                item_to_remove[strcspn(item_to_remove, "\n")] = '\0'; 
                if (strcmp(item_to_remove, "enough") == 0) {
                    break; 
                }

                remove_item(player, item_to_remove);
            }
        }
    }

    printf("\nYour inventory is now:\n");
    for (int i = 0; i < player->inventory_count; i++) {
        printf("- %s\n", player->inventory[i]);
    }
    printf("Your total attack power (including all items): %d\n", player->attack_power);
    printf("Your current health: %d\n", player->health);

    while (1) {
    printf("\nWhere would you like to go next?\n");
    printf("Type 'move2' to go to Room 2, 'moveup' to return to the starting room ");
    char move_choice[20];
    scanf("%s", move_choice);
    clear_buffer(); 

    if (strcmp(move_choice, "move2") == 0) {
        printf("You are moving to Room 2. Good luck!\n");
        return 2; 
    } else if (strcmp(move_choice, "moveup") == 0) {
        printf("You are returning to the starting room.\n");
        return -1; 
    } else {
        printf("I don't understand where you want to go, please write another  'move2'or 'moveup'.\n");
    }
}

}

int battle(Player* player, Creature* creature) { // oyuncunun canvarla savastıgı fonksıyon
    printf("\n*** Battle begins!. I believe that you will win this war ***\n");
    printf("You are fighting %s (Health: %d, Attack Power: %d)\n", creature->name, creature->health, creature->attack_power);
    printf("Your current health: %d, Attack Power: %d\n", player->health, player->attack_power);

    while (player->health > 0 && creature->health > 0) {

        creature->health -= player->attack_power;
        creature->health = creature->health < 0 ? 0 : creature->health;  
        printf("You attack the %s! It now has %d health.\n", creature->name, creature->health);

        if (creature->health <= 0) {
            printf("You defeated the %s!\n", creature->name);
            break;
        }

        player->health -= creature->attack_power;
        player->health = player->health < 0 ? 0 : player->health;
        printf("The %s attacks you! Your health is now %d.\n", creature->name, player->health);

        if (player->health <= 0) {
            printf("You have been defeated by the %s!\n", creature->name);
            break;
        }
    }

    if (player->health > 0) {
        printf("You've become our new hero .Congratulations, our hero\n");
        return 1; 
    } else {
        printf("No, no, you're dead.  We are proud of you even if you die .You will always be in our hearts..\n");
        return 0; 
    }
}

int room2_battle(Player* player, Room* room, Creature* selected_creature_from_room6) {
    printf("\n*** Room 2: Battle Room ***\n");
    
    
    char look_choice[10];
    printf("Do you want to take a closer look at the room? You can write 'look' to examine: ");
    fgets(look_choice, sizeof(look_choice), stdin);
    look_choice[strcspn(look_choice, "\n")] = '\0';
    
    if (strcmp(look_choice, "look") == 0) {
        look(room); 
    } else {
        printf("You didn't want to look at the room, you were a big novice..\n");
    }

    player->health += 10; // iksirin saglık ustundekı etkisi

    Creature* selected_creature = NULL;

    if (selected_creature_from_room6 != NULL) {
        selected_creature = selected_creature_from_room6;
        printf("You are fighting %s from Room 6.\n", selected_creature->name);
    } else {
        int num_creatures = sizeof(creatures) / sizeof(creatures[0]);
        int creature_choice = rand() % num_creatures;
        selected_creature = &creatures[creature_choice];
        printf("You are facing a random creature: %s\n", selected_creature->name);
    }

    char choice[10];
    printf("Do you want to attack the creature? Type 'attack' to fight: ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0'; 

    if (strcmp(choice, "attack") == 0) {
        int result = battle(player, selected_creature);
        if (result == 1) {
            printf("\nYou have successfully completed the battle in Room 2\n");
            return 1;
        } else {
            printf("\nYou were defeated in battle game over :(\n");
            return -1;
        }
    } else {
        printf("\nYou did not accept the challenge, I am sure you will come back stronger\n");
        return -1; 
    }
}



int main() {
    srand(time(NULL));

    Player player = {"You", 100, 10, 0};
    int completed_traps[MAX_TRAPS];
    int* ptr = completed_traps;  

    Item room5_items[] = { // odalarimdaki itemleri tanimliyoruz
        {"Helmet of Wisdom", 10},
        {"Shield of Valor", 10},
        {"Armor of Light", 10}
    };

    Item room6_items[] = {
        {"Diamond Sword", 25}
    };
    Item room2_items[] = {{"Potion",12}};
    Item room3_items[] = {
        {"Sword of Fury", 3},
        {"Ace of Spades", 5},
        {"Infinity Blade", 8},
        {"Alien Blaster", 7},
        {"Boots of Speed", 5},
        {"Ring of Strength", 8},
        {"Bow of Eternity", 10},
        {"Dagger of Shadows", 7},
        {"Amulet of Power", 6},
        {"Staff of Destiny",8}
    };

    Room room5, room6,room2,room3;
    
    room5.item_count = 3;
    room6.item_count = 1;
    room2.item_count = 1;
    room3.item_count = 10;
    initialize_room(&room5, "A the trap room. There may be many traps use your logic and luck to pass the traps.", room5_items, 3);
    initialize_room(&room6, "There are monsters in this room that are stronger than each other. I hope you can make the right decision.", room6_items, 1);
    initialize_room(&room2, "A battle room.We need your courage and strength.", room2_items, 1);
    initialize_room(&room3, "You're very lucky, this is an item chest room. hurry up and grab the items.", room3_items, 10);
    
    char load_choice;
    printf("Do you want to load a saved game? (y/n): ");
    scanf(" %c", &load_choice);
    clear_buffer();

    if (load_choice == 'y' || load_choice == 'Y') {
        if (!load_game(&player,ptr)) {
            for (int i = 0; i < MAX_TRAPS; i++) {
                    completed_traps[i] = 0; // kaydedilmiş oyun bulamazsa geçilen tuzaklar sıfırlanıyor
            }
            printf("No saved game found! Starting a new game.\n");
        }
    } else {
        printf("Starting a new game...\n");
        for (int i = 0; i < MAX_TRAPS; i++) {
                completed_traps[i] = 0;
            }
    }

   Creature *selected_creature_from_room6=NULL; 
    
    while (1) {
        printf("\nSet forth, with courage in your stride,\n");
        printf("Unlock the secrets with each guide.\n");
        printf("Obstacles cant stand in your way,\n");
        printf("Adventure calls, go without delay!\n");
        printf("\n");
        printf("\nYou are in the starting room(Room 1). Where would you like to go?\n");
        printf("2. Move to Room 2 (Battle Room)\n");
        printf("3. Move to Room 3 (Inventory Chest Room)\n");
        printf("5. Move to Room 5 (Trap Room)\n");
        printf("6. Move to Room 6 (Creature Card Room)\n");
        printf("4. Save game and exit\n");

        int choice;
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clear_buffer();
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        clear_buffer();

        if (choice == 5) {
            printf("Moving to Room 5...\n");
            int result = room5_traps(&player, &room5,ptr);
            if (result == 6) {
                printf("You are moving to Room 6!\n");
                int room6_result = room6_creature_cards(&player, &room6,&selected_creature_from_room6,ptr);
                if (room6_result == 3) {
                    printf("You are moving to Room 3!\n");
                    int room3_result = room3_chest(&player, &room3,room3_items);
                    if (room3_result == 2) {
                        printf("You are moving to Room 2 for a battle!\n");
                        int room2_result = room2_battle(&player, &room2, selected_creature_from_room6);
                        if (room2_result == 1) {
                            break; 
                        } else if (room2_result == -1) {
                            break; 
                        }
                    }
                }
            }
        } else if (choice == 3) {
            printf("Moving to Room 3...\n");
            int result = room3_chest(&player, &room3,room3_items);
            if (result == 2) {
                printf("You are moving to Room 2!\n");
                int room2_result = room2_battle(&player, &room2, selected_creature_from_room6);
                if (room2_result == 1) {
                    break;  
                } else if (room2_result == -1) {
                    break;  
                }
            }
        } else if (choice == 2) {
            printf("Moving to Room 2...\n");
            int result = room2_battle(&player, &room2, selected_creature_from_room6);
            if (result == 1) {
                break;
            } else if (result == -1) {
                break; 
            }
        }else if(choice==6){
            printf("Moving to Room 6...\n");
            int room6_result = room6_creature_cards(&player, &room6,&selected_creature_from_room6,ptr);
                if (room6_result == 3) {
                    printf("You are moving to Room 3!\n");
                    int room3_result = room3_chest(&player, &room3,room3_items);
                    if (room3_result == 2) {
                        printf("You are moving to Room 2 for a battle!\n");
                        int room2_result = room2_battle(&player, &room2, selected_creature_from_room6);
                        if (room2_result == 1) {
                            break;
                        } else if (room2_result == -1) {
                            break; 
                        }
                    }
                }
        }
         else if (choice == 4) {
            save_game(&player,ptr);
            char start_new_game;
            printf("Would you like to start a new game? (y/n): ");
            scanf(" %c", &start_new_game);
            clear_buffer();

            if (start_new_game == 'y' || start_new_game == 'Y') {
                printf("Starting a new game...\n");
                player = (Player){"Alice", 100, 10, 0, 0};
                 for (int i = 0; i < MAX_TRAPS; i++) {
                    completed_traps[i] = 0;
                }               
                continue;
            } else {
                printf("Exiting the game...\n");
                break;
            }
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }
    cleanup_room(&room5);
    cleanup_room(&room6);
    cleanup_room(&room2);
    cleanup_room(&room3);
    return 0;
}