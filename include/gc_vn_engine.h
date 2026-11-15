/*
 * ============================================================================
 * Project:       Glenfield College Visual Novel Engine (GC VN Engine)
 * File:          include/gc_vn_engine.h
 * Description:   Public Student API Surface & Narrative Declarative Boundary
 * Standard:      ISO C23
 * Target:        Year 11 Digital Technology (Glenfield College)
 * ============================================================================
 */

#ifndef GC_VN_ENGINE_H
#define GC_VN_ENGINE_H

#include <stdint.h>
#include <stdbool.h>

#define GCVN_MAX_CHOICES 4
#define GCVN_MAX_ACTORS 16
#define GCVN_TEXT_CAPACITY 480

/* --- Visual Enums --- */

enum SpritePosition {
    POS_LEFT,
    POS_CENTER,
    POS_RIGHT,
    POS_CUSTOM
};

enum SpriteAnimation {
    ANIM_NONE,
    ANIM_HOP,
    ANIM_SHAKE
};

/* ============================================================================
 * 1. Engine Lifecycle & Execution Loop
 * ============================================================================ */

/* Initializes the SDL3 hardware backbuffer, audio bus, and static memory arenas. */
void vn_init(const char* window_title, int32_t width, int32_t height);

/* Cleans up hardware devices, textures, audio streams, and resets engine state. */
void vn_cleanup(void);

/* Enters the hardware event loop, launching the procedural intro and scene router. */
void vn_run(void);

/* Sets an optional background environment image for the main title menu screen.
 * apply_dark_wash: true to apply a dark ambient wash for bright/sunlit artwork;
 *                  false to display the background art without an overlay. */
void vn_set_title_background(const char* image_path, bool apply_dark_wash);

/* Sets an optional background music track (48 kHz stereo WAV) for the title menu. */
void vn_set_title_bgm(const char* audio_path);

/* ============================================================================
 * 2. Scene Graph Construction
 * ============================================================================ */

/* Opens a declarative scene buffer block in static memory for the given scene ID. */
void vn_begin_scene(int32_t scene_id, const char* scene_title);

/* Closes the active scene buffer declaration. */
void vn_end_scene(void);

/* Transitions the router to the target scene ID at runtime. */
void vn_transition(int32_t target_scene_id);

/* ============================================================================
 * 3. Visual Staging & Compositor Directives
 * ============================================================================ */

/* Stages a background environment texture with an optional transition effect. */
void vn_set_background(const char* image_path, const char* transition_type);

/* Smoothly applies the full-viewport ambient reading wash (RGBA: 6, 10, 16, 150). */
void vn_darken_overlay(void);

/* Temporarily hides the text reading wash and prose stream to reveal artwork. */
void vn_hide_text_overlay(void);

/* Restores the text reading wash and active prose stream. */
void vn_restore_text_overlay(void);

/* Blits an actor sprite at the specified anchor slot behind the reading plane. */
/* char_id: Integer identifier from 0 to (GCVN_MAX_ACTORS - 1). */
void vn_show_sprite(int32_t char_id, const char* sprite_path, enum SpritePosition pos);

/* Executes procedural kinematics on an active sprite (parabolic hop or confrontation shake). */
/* char_id: Integer identifier from 0 to (GCVN_MAX_ACTORS - 1). */
void vn_animate_sprite(int32_t char_id, enum SpriteAnimation anim);

/* Hot-swaps the emotional expression sprite for an active character slot. */
/* char_id: Integer identifier from 0 to (GCVN_MAX_ACTORS - 1). */
void vn_set_expression(int32_t char_id, const char* sprite_path);

/* Focuses a key item graphic centered on the foreground layer. */
void vn_show_key_item(const char* image_path);

/* Removes the focused key item graphic from the foreground layer. */
void vn_hide_key_item(void);

/* ============================================================================
 * 4. Tsukihime NVL Text Stream & Audio Bus
 * ============================================================================ */

/* Appends a 1st-person narration paragraph flush to NVL_MARGIN_LEFT. */
void vn_narrate(const char* text);

/* Appends an in-line dialogue line in quotes, with optional voice-line preemption. */
void vn_dialogue(const char* text, const char* voice_audio_path);

/* Flushes cumulative prose paragraphs from the viewport. */
void vn_clear_text(void);

/* Starts seamless background music playback on Channel A. */
void vn_play_bgm(const char* audio_path);

/* Fires a non-blocking one-shot sound effect on Channel C. */
void vn_play_sfx(const char* audio_path);

/* ============================================================================
 * 5. Interactive In-Line Choices & Branching
 * ============================================================================ */

/* Stages an unconditional branching option appended in-line below active prose. */
void vn_add_choice(const char* label, int32_t target_scene_id);

/* Stages a state-qualified branching option with prerequisite checks. */
void vn_add_conditional_choice(
    const char* label,
    int32_t target_scene_id,
    int32_t req_flag_id,
    int32_t req_char_id,
    int32_t req_threshold,
    int32_t req_item_id
);

/* Renders all staged choices in-line and yields control until the player confirms. */
void vn_display_choices(void);

/* ============================================================================
 * 6. Persistent Player State (Binary Storage)
 * ============================================================================ */

/* Updates an event flag bit in the player's persistent bitmask (IDs: 0 to 127). */
void vn_set_flag(int32_t flag_id, bool value);

/* Returns the Boolean state of an event flag. */
bool vn_get_flag(int32_t flag_id);

/* Mutates a character relationship metric by a signed integer delta. */
void vn_modify_relationship(int32_t char_id, int32_t delta);

/* Returns the current score for a character relationship slot (IDs: 0 to 15). */
int32_t vn_get_relationship(int32_t char_id);

/* Adds an item ID into the 32-slot static inventory array. */
void vn_give_item(int32_t item_id);

/* Returns true if the specified item ID exists within the active inventory. */
bool vn_has_item(int32_t item_id);

/* Sets an entry bit in the persistent diary database bitmask (IDs: 0 to 63). */
void vn_update_diary(int32_t entry_id);

/* ============================================================================
 * 7. Audio Bus Calibration & Runtime Volume Settings
 * ============================================================================ */

/* Sets baseline acoustic ceilings for project audio takes (Clamped: 0.0f to 3.0f). */
void vn_set_baseline_gains(float bgm_gain, float voice_gain, float sfx_gain);

/* Sets the runtime master audio volumes (Normalized: 0.0f to 1.0f). */
void vn_set_volume_bgm(float volume);
void vn_set_volume_voice(float volume);
void vn_set_volume_sfx(float volume);

/* Queries active runtime volume scalars. */
float vn_get_volume_bgm(void);
float vn_get_volume_voice(void);
float vn_get_volume_sfx(void);

#endif /* GC_VN_ENGINE_H */