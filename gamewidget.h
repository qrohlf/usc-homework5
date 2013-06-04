#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "enemy.h"
#include "player.h"
#include "boss.h"
#include <vector>
#include "explosion.h"
#include <QFont>
#include <list>

/**
  @brief An enum used to keep track of the game state

  MENU - show the main menu, paint the player
  MESSAGE - show a message, paint the player
  GAME - run the game, paint the player and enemies
  GAMEOVER - display a GAME OVER screen
  VICTORY - display the Victory sequence befor returning to the MENU
  **/
enum gameStatus { MENU, MESSAGE, GAME, GAMEOVER, VICTORY};

/**
  @brief The QWidget that handles an entire game
  **/
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

protected:
    void readyPlayerOne();
    void mainMenu();
    void startGame();
    void gameOver();
    void victory();
    void resetGame();
    void timerEvent(QTimerEvent * event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void nextWave();
    void loadFirstWave();
    void loadSecondWave();
    void loadThirdWave();
    void loadFourthWave();
    void loadFifthWave();
    void loadSixthWave();
    void loadSeventhWave();
    void loadEighthWave();
    void loadNinthWave();
    void loadFinalWave();
    bool checkCollision(Enemy* en);
    bool checkHit(Enemy* en);
    Explosion* addExplosion(Enemy* en);
    ///Remember the ID of the timer running the game
    int timerId;
    ///Store all the Enemies which are currently active
    std::list<Enemy*> enemies;
    ///The Player object
    Player player;
    ///The cool retro font used to paint text
    QFont font;
    ///Track the game state
    gameStatus status;
    ///multi-purpose counter used for messages, victory, and gameover
    int ticks;
    ///Keep track of which wave the Player is on
    int wave;
    ///Message to be displayed
    QString message;
    ///Keep track of the selected menu item
    int menuSelection;
    ///Store the rear background image
    QImage background_rear;
    ///Store the front background image
    QImage background_front;
    ///Rolling counter to track the rear background positioning
    int background_rear_pos;
    ///Rolling counter to track the front background positioning
    int background_front_pos;
signals:

public slots:
    
};

#endif // GAMEWIDGET_H
