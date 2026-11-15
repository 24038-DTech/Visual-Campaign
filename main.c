/*
 * ============================================================================
 * Project:       Ben Staples Visual Campaign
 * File:          campaign.c
 * Narrative:     DND One-shot - Oakhaven village intro
 * Standard:      ISO C23
 * ============================================================================
 */

#include "gc_vn_engine.h"
#include <SDL3/SDL.h>
#include <windows.h>

/* Scene routing IDs */
enum SceneID {
    SCENE_BASEMENT_INTRO = 0,
    SCENE_SUPPLIES_YES   = 1,
    SCENE_SUPPLIES_NO    = 2,
    SCENE_CLASS_SELECT   = 3,
    SCENE_FIGHTER_INTRO  = 4,
    SCENE_WIZARD_INTRO   = 5,
    SCENE_ROGUE_INTRO    = 6,
    SCENE_RANGER_INTRO   = 7,
    SCENE_CLASS_CONFIRM  = 8,
    SCENE_OAKHAVEN_LORE  = 9,
    SCENE_ERRAND         = 10,
    SCENE_HOME           = 11,
    SCENE_CONVERSATION   = 12
};

/* Persistent memory flags */
enum FlagID {
    FLAG_HAS_SUPPLIES    = 0,
    FLAG_HAS_GROCERIES   = 1
};
enum ActorID {
    HARALD               = 0,
    ITEM_GROCERIES       = 1
};


/* ============================================================================
 * SCENE 1: Intro & Character Creation (Supplies Check)
 * ============================================================================ */
void scene_basement_intro(void) {
    vn_begin_scene(SCENE_BASEMENT_INTRO, "The Dungeon Master's Basement");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");
    vn_narrate("You descend down the stairs into the warm, well-lit basement.");
    vn_narrate("A long table stretches across the center, covered with various character sheets, dice, and miniature figurines.");
    vn_narrate("The Dungeon Master, a woman in her mid twenties with a stylized DND t-shirt, blue circle framed glasses and red frizzy hair, greets you with a nod and a warm smile.");
    
    vn_narrate("Dungeon Master");
    vn_dialogue("Hey! I'm glad you could make it! DND is a really fun game, I think it's cool that you decided to do this one-shot with me before joining my regular campaign group.", NULL);
    vn_dialogue("Before we start, we need to make you a character. Do you have your character sheets and dice?", NULL);

    vn_add_choice("Yes, I have them.", SCENE_SUPPLIES_YES);
    vn_add_choice("No, I need to borrow some.", SCENE_SUPPLIES_NO);
    vn_display_choices();

    vn_end_scene();
}
/* ============================================================================
 * SCENE 2 & 3: Supply Routing
 * ============================================================================ */
void scene_supplies_yes(void) {
    vn_begin_scene(SCENE_SUPPLIES_YES, "Supplies Ready");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");
    vn_set_flag(FLAG_HAS_SUPPLIES, true);
    vn_dialogue("Great! Let's get started then!", NULL);
    vn_dialogue("You already have your pencil and dice, so you are going to have a blast with this.", NULL);
    
    vn_transition(SCENE_CLASS_SELECT);
    vn_end_scene();
}

void scene_supplies_no(void) {
    vn_begin_scene(SCENE_SUPPLIES_NO, "Borrowing Supplies");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");
    
    vn_set_flag(FLAG_HAS_SUPPLIES, false);
    vn_dialogue("No worries! Here is your character sheet, and here is a set of matching dice and a pencil. You are going to have a blast with this.", NULL);
    
    vn_transition(SCENE_CLASS_SELECT);
    vn_end_scene();
}

/* ============================================================================
 * SCENE 4: Class Selection
 * ============================================================================ */
void scene_class_select(void) {
    vn_begin_scene(SCENE_CLASS_SELECT, "Choose Your Class");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");

    vn_narrate("Dungeon Master");
    vn_dialogue("First, you need to choose your character. To keep it simple, I've taken the liberty of creating a few characters for you to choose from.", NULL);

    vn_add_choice("Fighter (Strong and tanky warrior)", SCENE_FIGHTER_INTRO);
    vn_add_choice("Wizard (Master of arcane magic)", SCENE_WIZARD_INTRO);
    vn_add_choice("Rogue (Stealthy and cunning)", SCENE_ROGUE_INTRO);
    vn_add_choice("Ranger (Skilled in ranged combat)", SCENE_RANGER_INTRO);
    vn_display_choices();

    vn_end_scene();
}

/* ============================================================================
 * SCENES 5-8: Class Descriptions
 * ============================================================================ */
void scene_fighter_intro(void) {
    vn_begin_scene(SCENE_FIGHTER_INTRO, "The Fighter");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");

    vn_narrate("Dungeon Master");
    vn_dialogue("You've chosen the Fighter! Your main job is to be the team's protector.", NULL);
    vn_dialogue("Because you have the highest health and the toughest armor, you stand right at the front to take the hits and keep the monsters away from your squishier friends.", NULL);
    vn_transition(SCENE_CLASS_CONFIRM);
    vn_end_scene();
}

void scene_wizard_intro(void) {
    vn_begin_scene(SCENE_WIZARD_INTRO, "The Wizard");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");

    vn_narrate("Dungeon Master");   
    vn_dialogue("You've chosen the Wizard! Your job is to bring the big, explosive solutions.", NULL);
    vn_dialogue("While you can't take many hits yourself, you can clear out entire rooms of monsters at once with giant bursts of magic, or use utility spells to solve tricky puzzles.", NULL);
    vn_transition(SCENE_CLASS_CONFIRM);
    vn_end_scene();
}

void scene_rogue_intro(void) {
    vn_begin_scene(SCENE_ROGUE_INTRO, "The Rogue");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");

    vn_narrate("Dungeon Master");
    vn_dialogue("You've chosen the Rogue! Your job is to be the problem-solver and the scout.", NULL);
    vn_dialogue("When the team finds a locked door, a hidden treasure chest, or a dangerous trap, you step up to handle it. In battle, you use stealth to deal massive surprise damage.", NULL);
    vn_transition(SCENE_CLASS_CONFIRM);
    vn_end_scene();
}

void scene_ranger_intro(void) {
    vn_begin_scene(SCENE_RANGER_INTRO, "The Ranger");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");

    vn_narrate("Dungeon Master");
    vn_dialogue("You've chosen the Ranger! Your job is to guide the team safely through the world and strike from a safe distance.", NULL);
    vn_dialogue("You make sure the party never gets lost in the wild, and you use your deadly bow and arrow to thin out the enemy ranks before they can even reach you.", NULL);
    vn_transition(SCENE_CLASS_CONFIRM);
    vn_end_scene();
}

/* ============================================================================
 * SCENE 9: Class Confirmation & Supply Check
 * ============================================================================ */
/* ============================================================================
 * SCENE 9: Class Confirmation
 * ============================================================================ */
void scene_class_confirm(void) {
    vn_begin_scene(SCENE_CLASS_CONFIRM, "Ready to Play");
    vn_set_background("assets/bg/vn_bg_basement.png", "FADE_IN");

    vn_dialogue("It's a good pick, and one of my absolute favourite classes to run.", NULL);
    vn_dialogue("Grab your character sheet and let's get started!", NULL);

    vn_transition(SCENE_OAKHAVEN_LORE);
    vn_end_scene();
}

/* ============================================================================
 * SCENE 10: Oakhaven Lore
 * ============================================================================ */
void scene_oakhaven_lore(void) {
    vn_begin_scene(SCENE_OAKHAVEN_LORE, "The World of Oakhaven");
    vn_set_background("assets/bg/vn_bg_oakhaven.png", "FADE_IN");

    /* Each line's voicing will be labled from into_0 to into_8 */
    vn_narrate("Dungeon Master");
    vn_dialogue("Your story begins in Oakhaven, a peaceful trading village nestled tightly between the protective canopy of the Whispering Woods and the jagged, mist-shrouded peaks of the Dragon-Teeth Mountains.", NULL);
    vn_dialogue("For generations, your people have lived through trade and commerce, isolated from the grand, dangerous politics of the sprawling empires beyond.", NULL);
    vn_dialogue("The village itself is a sanctuary of thatched-roof cottages, winding stone paths, and the constant, comforting scents of burning hearth-fires and exotic goods.", NULL);

    vn_dialogue("Life here moves to the rhythm of trade, far away from the wars of kings and the greed of sorcerers.", NULL);
    vn_dialogue("Its people are simple folk: merchants, weavers, and woodcarvers who look out for one another.", NULL);
    vn_dialogue("To the north, the looming mountains keep out the harsh northern wastes, while the Whispering Woods to the south supply lumber, game, and a boundary line that nobody dares to cross after dark.", NULL);

    vn_dialogue("It is a place where you have always felt safe; a place where the biggest worry was an early frost or a fox in the chicken coop.", NULL);
    vn_dialogue("Until today...", NULL);

    vn_transition(SCENE_ERRAND);
    vn_end_scene();
}

/* ============================================================================
 * SCENE 11: First Quest
 * ============================================================================ */
void scene_errand(void) {
    vn_begin_scene(SCENE_ERRAND, "The First Quest");
    vn_set_background("assets/bg/vn_bg_oakhaven.png", "FADE_IN");
    /* Each line's voicing will be labled from quest_0 to quest_6 */
    vn_narrate("Dungeon Master");
    vn_dialogue("The day that would change everything began like any other. ", NULL);    
    vn_set_background("assets/bg/vn_bg_market.png", "FADE_IN");

    vn_dialogue("The sun rose over the village, casting a warm glow on the cobblestone streets and the bustling market square.", NULL);
    vn_dialogue("You are running an errand for your father, picking up his weekly groceries from Harald, the village greengrocer.", NULL);
    vn_dialogue("However, as you make your way through the market, you notice whispers running from one end of the square to the other." , NULL);
    vn_dialogue("Unsettled, you push it to the back of your mind as you arrive at Harald's stall.", NULL);

    vn_show_sprite(HARALD, "assets/characters/vn_char_harald.png", POS_LEFT);
    vn_narrate("Harald");
    vn_dialogue("Ah, there you are! Here are your father's groceries, as always.", NULL);

    vn_narrate("GAME UPDATE: RECIEVED ITEM_GROCERIES");
    /* Update the engine's memory to show the player owns the item */
    vn_set_flag(FLAG_HAS_GROCERIES, true);
    vn_show_sprite(ITEM_GROCERIES, "assets/items/vn_item_groceries.png", POS_RIGHT);

    vn_add_choice("Thanks Harald, have a good day!", SCENE_HOME);
    vn_add_choice("Thank you Harald, but what is going on? Why is everyone whispering?", SCENE_CONVERSATION);
    vn_display_choices();
    vn_end_scene();
}
void scene_home(void){ 

}
void scene_conversation(void){ 

}
/* ============================================================================
 * MAIN EXECUTION OF GAME
 * ============================================================================ */
int main (void) {
    FreeConsole();

    vn_init("Visual Campaign", 1920, 1080);

    int count = 0;
    SDL_Window **windows = SDL_GetWindows(&count);
    if (windows && count > 0) {
        SDL_SetWindowFullscreen(windows[0], true);
        SDL_Renderer *renderer = SDL_GetRenderer(windows[0]);
        SDL_SetRenderLogicalPresentation(renderer, 1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }
    
    /* Registration of scenes */
    scene_basement_intro();
    scene_supplies_yes();
    scene_supplies_no();
    scene_class_select();
    scene_fighter_intro();
    scene_wizard_intro();
    scene_rogue_intro();
    scene_ranger_intro();
    scene_class_confirm();
    scene_oakhaven_lore();
    scene_errand();
    scene_home();
    scene_conversation();

    vn_run();

    return 0;
}