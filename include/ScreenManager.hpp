#include "Settings.hpp"
#include "Screen.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include "GameOver.hpp"
#include "Coop.hpp"
#include <raylib.h>
#include <memory>
#include <unordered_map>
class ScreenManager {
public:
    ScreenManager();
    void AddScreen(Screens type, std::unique_ptr<Screen> screen);
    void SetScreen(Screens type);
    void UpdateScreen();
    bool ShouldClose();
    Screens GetActualScreen() const;
    void ResetGameScreenIfNeeded(Board *board);
private:
    Screens actualScreen;
    Screens lastScreen;
    bool entered;
    void SetScoreInGameOver();
    std::unordered_map<Screens, std::unique_ptr<Screen>> screens;
};
