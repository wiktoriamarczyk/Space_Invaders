//export module Module_Common;
//
//export import <SDL_image.h>;
//export import <SDL.h>;
//export import <SDL_Mixer.h>;
//
//import "vec2.h";
//
//export import <iostream>;
//export import <vector>;
//export import <string>;
//export import <fstream>;
//export import <memory>;
//export import <stdlib.h>;
//export import <time.h>;
//export import <algorithm>;
//export import <optional>;
//export import <functional>;
//export import <regex>;
//export import <filesystem>;
//export import <mutex>;
//export import <thread>;
//export import <chrono>;
//export import <sstream>;
//export using std::vector;
//export using std::unique_ptr;
//export using std::make_unique;
//export using std::shared_ptr;
//export using std::make_shared;
//export using std::move;
//export using std::string;
//export using std::fstream;
//export using std::optional;
//export using std::nullopt;
//export using std::function;
//export using std::none_of;
//export using std::dynamic_pointer_cast;
//export using std::regex;
//export using std::regex_match;
//export using std::filesystem::path;
//export using std::mutex;
//export using std::thread;
//export using std::scoped_lock;
//export using std::ofstream;
//export using std::getline;
//export using std::pair;
//
//export extern const path DataPath = "../Data";
//
//export enum : int
//{
//    SCREEN_WIDTH = 800,
//    SCREEN_HEIGHT = 800,
//    //WINDOW_WIDTH = 1520,
//    //WINDOW_HEIGHT = 900,
//    OBJECT_HEIGHT = 50,
//    OBJECT_WIDTH = 50,
//    SHOT_SPEED = 500,
//    SHOT_WIDTH = 3,
//    SHOT_HEIGHT = 9,
//};
//
//export enum class eStateID
//{
//    UNKNOWN,
//    MAINMENU,
//    INGAME,
//    VICTORY,
//    HOWTOPLAY,
//    HIGHSCORE,
//    SETUP,
//};
//
//export enum class eTeamID
//{
//    UNKNOWN,
//    PLAYER,
//    INVADER,
//    SUICIDE,
//};
//
//export enum class eInvaderDirection
//{
//    RIGHT,
//    LEFT
//};
//
//export enum class eDrawMode
//{
//    NORMAL,
//    ADDITIVE,
//};
//
//export enum class ePowerUpType
//{
//    UNKNOWN = 0,
//    GUN_IMPROVMENT,
//    HEALTH,
//    SHIELD,
//    ANGRY_INVADER,
//};
//
//export struct Color
//{
//    unsigned char R = 255;
//    unsigned char G = 255;
//    unsigned char B = 255;
//    unsigned char A = 255;
//
//    Color() = default;
//    //Color(float r, float g, float b, float a = 1.f) : R(r), G(g), B(b), A(a) {}
//    Color(int r, int g, int b, int a = 255) : R(r), G(g), B(b), A(a) {}
//
//    static const Color RED;
//    static const Color WHITE;
//    static const Color YELLOW;
//};
//
//export const Color Color::RED(255, 0, 0);
//export const Color Color::WHITE(255, 255, 255);
//export const Color Color::YELLOW{ 249, 215, 28 };
//
//export struct DisplayParameters
//{
//    optional<vec2i> DisplaySize;
//    eDrawMode DrawMode = eDrawMode::NORMAL;
//    vec2 DrawScale = vec2(1.0f, 1.0f);
//    vec2 SrcTopLeft = vec2(0, 0);
//    vec2 SrcSize = vec2(1, 1);
//    Color DrawColor;
//};
//
//export struct Vec2Rect
//{
//    vec2 TopLeft;
//    vec2 Size;
//};
//
//export bool SDL_IsKeyPressed(SDL_Scancode Code)
//{
//    const Uint8* Keys = SDL_GetKeyboardState(NULL);
//    return Keys[Code] != 0;
//}
//
//export int GetRandInt(int Min, int Max)
//{
//    if (Min == Max)
//    {
//        return Max;
//    }
//    return rand() % (Max - Min + 1) + Min;
//}
//
//export float GetNormalizedFloat()
//{
//    return rand() / float(RAND_MAX);
//}
//
//export float GetRandFloat(float Min, float Max)
//{
//    float FloatDiff = Max - Min;
//    if (FloatDiff <= 1)
//        return Min + (FloatDiff)*GetNormalizedFloat();
//
//    const int IntDiff = int(FloatDiff);
//    return Min + GetRandInt(0, IntDiff - 1) + (1 + FloatDiff - IntDiff) * GetNormalizedFloat();
//}