#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

/* Google Play */
#define LINK "https://play.google.com/store/apps/details?id=com.wry.phantomstar"

/* DELAY */
#define DELAY_SPLASH_SCENE 1
#define DELAY_TRANSITION 0.5f

/* TAG */
#define GAME_OBJECT 1
#define DIALOG_OBJECT 2

/* ITEM */
#define REPAIR_ITEM 1

/* INTENSITY */
#define LEVEL_ONE -5.0f
#define LEVEL_TWO -10.0f
#define LEVEL_THREE -15.0f

/* COLLISION BITMAP */
#define COLLISION_SHIP 0x000001
#define COLLISION_METEOR 0x000002
#define COLLISION_BULLET 0x000003
#define COLLISION_STAR 0x000004
#define COLLISION_ITEM 0x000005

/* PHYSICS BODY */
#define BODY_SHIP1 "PhysicsBodies/shipType1.json"
#define BODY_SHIP2 "PhysicsBodies/shipType2.json"
#define BODY_SHIP3 "PhysicsBodies/shipType3.json"

/* AUDIO */
#define AUDIO_STAR "Audio/star.wav"
#define AUDIO_REPAIR "Audio/shipRepair.wav"
#define AUDIO_COLLISION "Audio/collisionShip.wav"
#define AUDIO_EXPLOSION "Audio/explosion.wav"
#define AUDIO_SHIP_EXPLOSION "Audio/explosionShip.wav"
#define AUDIO_BACKGROUND "Audio/bgm.mp3"
#define AUDIO_GAMEOVER "Audio/gameover.mp3"

/* FONT */
#define FONT "Fonts/kenvector_future_thin.ttf"

/* SPRITE */
#define BACKGROUND "Backgrounds/background%i.png"
#define SHIP "ship%i.png"
#define SHIP_LIFE "ship%i_life.png"
#define EMITTER "fire13.png"
#define DAMAGE_1_1 "playerShip1_damage1.png"
#define DAMAGE_2_1 "playerShip2_damage1.png"
#define DAMAGE_3_1 "playerShip3_damage1.png"
#define DAMAGE_1_2 "playerShip1_damage2.png"
#define DAMAGE_2_2 "playerShip2_damage2.png"
#define DAMAGE_3_2 "playerShip3_damage2.png"
#define DAMAGE_1_3 "playerShip1_damage3.png"
#define DAMAGE_2_3 "playerShip2_damage3.png"
#define DAMAGE_3_3 "playerShip3_damage3.png"
#define LASER_1 "laser1.png"
#define LASER_2 "laser2.png"
#define LASER_3 "laser3.png"
#define METEOR "meteor%i.png"
#define STAR "star%i.png"
#define RED_PILL "pill_red.png"

/* PARTICLE */
#define SHIP_REPAIR "Particles/shipRepair.plist"
#define SHIP_COLLISION "Particles/shipCollision.plist"
#define SHIP_EXPLOSION "Particles/shipExplosion.plist"
#define BULLET_COLLISION "Particles/bulletCollision.plist"
#define METEOR_EXPLOSION "Particles/meteorExplosion.plist"
#define STAR_EFFECT "Particles/star%i.plist"

/* UI */
#define OPTION "UI/option.png"
#define MUSIC_ON "UI/musicOn.png"
#define MUSIC_OFF "UI/musicOff.png"
#define BGM_KEY "BGM_MUTED"
#define HIGHSCORE_KEY "HIGHSCORE"
#define GAME_MENU "GameMenu.csb"
#define GAME_DIALOG "GameDialog.csb"
#define GAMEOVER_DIALOG "GameOverDialog.csb"

#endif // __DEFINITIONS_H__
