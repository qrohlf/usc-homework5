#include "gamewidget.h"
#include <QPainter>
#include <iostream>
#include <cmath>
#include "explosion.h"
#include <QFontDatabase>
#include "fighter.h"
#include "kamikaze.h"
#include "heavy.h"
#include "seeker.h"
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include "detonator.h"
#include "lazerfighter.h"
#include "giantboss.h"
#include "swoopfighter.h"
/**
  Construct a new GameWidget showing the main menu
  @param parent The parent QT widget
  **/
GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    status(MENU),
    wave(1),
    menuSelection(1),
    background_rear(":/ships/res/stars1.png"),
    background_front(":/ships/res/stars2.png")
{
    //Setup window
    this->setFocus();
    this->setFixedSize(710, 710);
    this->setStyleSheet("background-color:black;");

    //Load custom font
    int id = QFontDatabase::addApplicationFont(":/ships/res/ka1.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(family, 20);

    //seed random
    srand(time(NULL));

    //Start timer
    timerId = startTimer(10);

}

/**
  Kick off the gam
  **/
void GameWidget::readyPlayerOne() {
    ticks = 600;
    status = MESSAGE;
    message = "READY PLAYER ONE";
}

/**
  Deprecated. Replaced by loadNextWave()
  @deprecated do not use
  **/
void GameWidget::startGame() {
    status = GAME;
    loadFirstWave();
}

/**
  Display the game over message and set status to GAMEOVER.
  The main menu will be displayed 2000ms after this is called.
  **/
void GameWidget::gameOver() {
    std::cout << "Game Over" << std::endl;
    status = GAMEOVER;
    ticks = 200;
}

/**
  Timer Event Handler
  Increment player/enemy locations, menu text, message text, or ticks based on the game status.
  Increments background locations.
  Will also repaint the scene.
  @param unused
  **/
void GameWidget::timerEvent(QTimerEvent *event) {
    background_rear_pos = (background_rear_pos+1)%2100;
    background_front_pos = (background_front_pos+1)%1400;
    player.move();
    switch (status) {
    case MENU:
        player.moveBullet();
        break;
    case MESSAGE:
        player.moveBullet();
        ticks--;
        if (ticks == 0) {
            nextWave();
            return;
        }
        break;
    case GAME:
        player.moveBullet();
        if (enemies.size() == 0) {
            ticks = 350;
            wave++;
            if (wave == 11 || wave==12) {
                nextWave();
                return;
            }
            message = "WAVE "+QString::number(wave)+" - GET READY";
            status=MESSAGE;
        }
        //do enemy stuff
        for (std::list<Enemy*>::iterator it = enemies.begin(); it!=enemies.end(); ) {
            Enemy *en = *it;
            if (en->getHealth() <=0) {
                enemies.erase(it++);
                continue;
            }
            en->move(player.getRawLocation());
            if (en->getType()=="Explosion") {
                //Ignore explosions
            }else if (checkCollision(en)) {
                int health = player.getHealth();
                player.takehit(en->getHealth());
                if (player.getHealth() <= 0) {
                    en->takehit(health); // The enemy takes an amount of damage equal to the player's health
                    player.loseLife();
                    if(player.getLives() <= 0) {
                        gameOver();
                        return;
                    }else {
                        player.setHealth(150);
                        Enemy* dummy = new Fighter(player.getRawLocation());
                        Explosion* ex = addExplosion(dummy);
                        player.blink(1000);
                        enemies.push_back(ex);
                        delete dummy;
                    }
                } else {
                    *it = addExplosion(en);
                    delete en;
                }
            } else if (checkHit(en)) {
                player.addToScore(en->takehit(15));
                player.resetBullet();
                if (en->getHealth() <=0) {
                    player.addToScore(en->killPoints());
                    *it = addExplosion(en);
                    delete en;
                }
            } else {
                Enemy* b = en->shoot(player.getRawLocation());

                //std::cout << "Shoot?" << std::endl;
                if (b!=NULL) {
                    enemies.push_back(b);
                }
            }
            it++;
        }
        break;
    case VICTORY:
        player.moveBullet();
        ticks--;
        if (ticks == 0) {
            mainMenu();
            return;
        }
        break;
    case GAMEOVER:
        break;
    }
    repaint();
}

/**
  Reset the game and display the main menu
  **/
void GameWidget::mainMenu() {
    status=MENU;
    resetGame();
}

/**
  Reset the game. Resets Player to default values, deletes all enemies, and sets wave to 1
  **/
void GameWidget::resetGame() {
    player = Player();
    enemies.clear();
    wave = 1;
}

/**
  Respond to key presses based on the game status.
  @param event The key event to respond to
  **/
void GameWidget::keyPressEvent(QKeyEvent *event) {
    if (status == MENU) {
        switch(event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            menuSelection = 1;
            return; //Don't let the player move up or down in the menu
        case Qt::Key_S:
        case Qt::Key_Down:
            menuSelection = 2;
            return; //Don't let the player move up or down in the menu
        case Qt::Key_Return:
            if(menuSelection==1) {
                std::cout << "Starting new game" << std::endl;
                readyPlayerOne();
                return;
            } else {
                exit(0);
            }
            break;
        }
    }
    player.keyInput(event, false);
    player.updateImage();
}

/**
  Respond to key releases based on the game status.
  @param event The key event to respond to
  **/
void GameWidget::keyReleaseEvent(QKeyEvent *event) {
    player.keyInput(event, true);
    player.updateImage();
}

/**
  Paint the screen based on the game status
  **/
void GameWidget::paintEvent(QPaintEvent *event) {
    //Setup resources
    QPainter painter(this);
    QPen pen(Qt::white);
    QBrush solid_brush(Qt::white);
    painter.setPen(pen);
    painter.setFont(font);
    QFontMetrics fm(font);
    int textWidth;
    //Draw background
    painter.drawImage(0, background_rear_pos/3, background_rear);
    painter.drawImage(0, background_rear_pos/3-700, background_rear);
    painter.drawImage(0, background_front_pos/2, background_front);
    painter.drawImage(0, background_front_pos/2-700, background_front);
    //Draw based on state of game
    switch (status) {
    case MENU: {
        textWidth = fm.width("MENU");
        painter.drawText(350-textWidth/2, 200, "MENU");
        int menu_x = 350-textWidth/2;
        QString newgame;
        QString exit;
        if (menuSelection == 1) newgame = "- NEW GAME";
        else newgame = "NEW GAME";
        if (menuSelection == 2) exit = "- EXIT";
        else exit = "EXIT";
        textWidth = fm.width(newgame);
        painter.drawText(350-textWidth/2, 250, newgame);
        textWidth = fm.width(exit);
        painter.drawText(350-textWidth/2, 280, exit);
        QFont small = font;
        small.setPointSize(12);
        painter.setFont(small);
        QFontMetrics sfm(small);
        textWidth = sfm.width("WASD keys to move or select");
        painter.drawText(350-textWidth/2, 350, "WASD keys to move or select");
        textWidth = sfm.width("Spacebar to shoot");
        painter.drawText(350-textWidth/2, 370, "Spacebar to shoot");
        textWidth = sfm.width("Press enter to begin");
        painter.drawText(350-textWidth/2, 390, "Press enter to begin");
        painter.setFont(font);
        break;}
    case MESSAGE:
        if (ticks%100 < 50) {
            textWidth = fm.width(message);
            painter.drawText(350-textWidth/2, 350, message);
            textWidth = fm.width(QString::number(ticks/100));
            if (message != "VICTORY!!") painter.drawText(350-textWidth/2, 400, QString::number(ticks/100));
        }
        break;
    case GAME:
        //Draw the enemies
        for (std::list<Enemy*>::const_iterator it = enemies.begin(); it!=enemies.end(); it++) {
            Enemy *en = *it;
            painter.drawImage(en->getLocation(), en->getImage());
        }
        break;
    case VICTORY:
        //Victory text
        textWidth = fm.width("Congratulations");
        painter.drawText(350-textWidth/2, 310, "Congratulations");
        textWidth = fm.width("Your final score was "+QString::number(player.getScore()));
        painter.drawText(350-textWidth/2, 350, "Your final score was "+QString::number(player.getScore()));
        break;
    case GAMEOVER:
        ticks --;
        if (ticks==0) mainMenu();
        textWidth = fm.width("GAME OVER");
        painter.drawText(350-textWidth/2, 350, "GAME OVER");
        textWidth = fm.width("Your final score was "+QString::number(player.getScore()));
        painter.drawText(350-textWidth/2, 380, "Your final score was "+QString::number(player.getScore()));
        break;
    }
    if (status != GAMEOVER) {
        //Always draw the player
        if (!player.getBlink()) painter.drawImage(player.getLocation(), player.getImage());

        //Draw the bullet
        if (player.bulletActive()) painter.drawImage(player.getBulletLoc(), player.getBulletImage());

        //Always draw the score
        textWidth = fm.width("Score "+QString::number(player.getScore()));
        painter.drawText(700-textWidth, 700, "Score "+QString::number(player.getScore()));
        //Always draw the lives
        painter.drawText(5, 700, "Lives "+QString::number(player.getLives()));
        //Always draw the health
        textWidth = fm.width("Health ");
        painter.drawText(5, 25, "Health ");
        painter.drawRect(QRect(textWidth+5, 5, 150, 25));
        painter.setBrush(solid_brush);
        painter.drawRect(QRect(textWidth+5, 5, player.getHealth(), 25));
    }
}

/**
  Helper method to replace dead Enemies with explosions
  @param en a pointer to the Enemy to replace
  @return an Explosion pointer which points to a properly sized 500ms explosion
  **/
Explosion* GameWidget::addExplosion(Enemy *en) {
    int duration = 500;
    if (en->getType()=="Bullet") duration = 100;
    Explosion* e = new Explosion(en->getRawLocation(), duration);
    e->setScale(en->getImage().width(), en->getImage().height());
    return e;
}

/**
  Helper method to check for collisions between the ship and Enemies
  @param en a pointer to the Enemy to check
  @return whether the Enemy collides with the Player
  **/
bool GameWidget::checkCollision(Enemy *en) {
    QPoint dist = en->getRawLocation()-player.getRawLocation();
    bool x_collide = false;
    bool y_collide = false;
    if (abs(dist.x()) < (en->getImage().width()/2))
        x_collide = true;
    if (abs(dist.x()) < (player.getImage().width()/2))
        x_collide = true;
    if (abs(dist.y()) < (player.getImage().height()/2))
        y_collide = true;
    if (abs(dist.y()) < (en->getImage().height()/2))
        y_collide = true;
    return x_collide&&y_collide;
}

/**
  Helper method to check if the player bullet has hit an Enemy
  @param en a pointer to the Enemy to check
  @return whether the Enemy has been hit by the Player
  **/
bool GameWidget::checkHit(Enemy *en) {
    QPoint dist = en->getRawLocation()-player.getBulletRawLoc();
    bool x_collide = false;
    bool y_collide = false;
    if (abs(dist.x()) < (en->getImage().width()/2))
        x_collide = true;
    if (abs(dist.x()) < (player.getBulletImage().width()/2))
        x_collide = true;
    if (abs(dist.y()) < (player.getBulletImage().height()/2))
        y_collide = true;
    if (abs(dist.y()) < (en->getImage().height()/2))
        y_collide = true;
    return x_collide&&y_collide;
}

/**
  Load the appropriate wave based on the value of wave
  **/
void GameWidget::nextWave() {
    status = GAME;
    switch (wave) {
    case 1:
        loadFirstWave();
        break;
    case 2:
        loadSecondWave();
        break;
    case 3:
        loadThirdWave();
        break;
    case 4:
        loadFourthWave();
        break;
    case 5:
        loadFifthWave();
        break;
    case 6:
        loadSixthWave();
        break;
    case 7:
        loadSeventhWave();
        break;
    case 8:
        loadEighthWave();
        break;
    case 9:
        loadNinthWave();
        break;
    case 10:
        loadFinalWave();
        break;
    case 11:
        ticks = 150;
        message = "VICTORY!!";
        status = MESSAGE;
        wave++;
        break;
    case 12:
        victory();
        break;
    default:
        break;
    }
}

/**
  Load Wave 1
  **/
void GameWidget::loadFirstWave() {
    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Boss(QPoint(350, 200)));
    enemies.push_back(new Fighter(QPoint(50, 100)));
    enemies.push_back(new Fighter(QPoint(150, 100)));
    enemies.push_back(new Fighter(QPoint(250, 100)));
    enemies.push_back(new Fighter(QPoint(350, 100)));
    enemies.push_back(new Fighter(QPoint(450, 100)));
    enemies.push_back(new Fighter(QPoint(550, 100)));
    enemies.push_back(new Fighter(QPoint(650, 100)));
}
/**
  Load Wave 2
  **/
void GameWidget::loadSecondWave() {
    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Boss(QPoint(350, 100)));
    enemies.push_back(new Fighter(QPoint(50, 100)));
    enemies.push_back(new Kamikaze(QPoint(150, 100), 200));
    enemies.push_back(new Fighter(QPoint(250, 100)));
    enemies.push_back(new Kamikaze(QPoint(350, 100), 250));
    enemies.push_back(new Fighter(QPoint(450, 100)));
    enemies.push_back(new Kamikaze(QPoint(550, 100), 450));
    enemies.push_back(new Fighter(QPoint(650, 100)));

    enemies.push_back(new Kamikaze(QPoint(50, 200), 600));
    enemies.push_back(new Fighter(QPoint(150, 200)));
    enemies.push_back(new Kamikaze(QPoint(250, 200), 300));
    enemies.push_back(new Fighter(QPoint(350, 200)));
    enemies.push_back(new Kamikaze(QPoint(450, 200), 200));
    enemies.push_back(new Fighter(QPoint(550, 200)));
    enemies.push_back(new Kamikaze(QPoint(650, 200), 360));
}
/**
  Load Wave 3
  **/
void GameWidget::loadThirdWave() {
    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Heavy(QPoint(200, 100)));
    enemies.push_back(new Heavy(QPoint(500, 100)));
    enemies.push_back(new Fighter(QPoint(50, 350)));
    enemies.push_back(new Fighter(QPoint(150, 350)));
    enemies.push_back(new Fighter(QPoint(250, 350)));
    enemies.push_back(new Fighter(QPoint(350, 350)));
    enemies.push_back(new Fighter(QPoint(450, 350)));
    enemies.push_back(new Fighter(QPoint(550, 350)));
    enemies.push_back(new Fighter(QPoint(650, 350)));

    enemies.push_back(new Kamikaze(QPoint(100, 450), 300));
    enemies.push_back(new Kamikaze(QPoint(200, 450), 300));
    enemies.push_back(new Kamikaze(QPoint(500, 450), 250));
    enemies.push_back(new Kamikaze(QPoint(600, 450), 350));
}
/**
  Load Wave 4
  **/
void GameWidget::loadFourthWave() {
    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Seeker(QPoint(50, 250), true));
    enemies.push_back(new Seeker(QPoint(150, 150), true));
    enemies.push_back(new Seeker(QPoint(350, 150), true));
    enemies.push_back(new Seeker(QPoint(550, 150), true));
    enemies.push_back(new Seeker(QPoint(650, 250), true));
    enemies.push_back(new Fighter(QPoint(50, 100)));
    enemies.push_back(new Fighter(QPoint(150, 100)));
    enemies.push_back(new Fighter(QPoint(250, 100)));
    enemies.push_back(new Fighter(QPoint(350, 100)));
    enemies.push_back(new Fighter(QPoint(450, 100)));
    enemies.push_back(new Fighter(QPoint(550, 100)));
    enemies.push_back(new Fighter(QPoint(650, 100)));

}
/**
  Load Wave 5
  **/
void GameWidget::loadFifthWave() {
    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Seeker(QPoint(150, 150)));
    enemies.push_back(new Seeker(QPoint(550, 150)));
    //enemies.push_back(new Seeker(QPoint(550, 650)));
    //enemies.push_back(new Seeker(QPoint(150, 650)));

    enemies.push_back(new LazerFighter(QPoint(150, 200)));
    enemies.push_back(new LazerFighter(QPoint(550, 200)));

    enemies.push_back(new Boss(QPoint(350, 200)));
    enemies.push_back(new Heavy(QPoint(350, 100)));

}
/**
  Load Wave 6
  **/
void GameWidget::loadSixthWave() {

    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Boss(QPoint(350, 200)));

    enemies.push_back(new Fighter(QPoint(50, 100)));
    enemies.push_back(new Fighter(QPoint(150, 100)));
    enemies.push_back(new Fighter(QPoint(250, 100)));
    enemies.push_back(new Fighter(QPoint(350, 100)));
    enemies.push_back(new Fighter(QPoint(450, 100)));
    enemies.push_back(new Fighter(QPoint(550, 100)));
    enemies.push_back(new Fighter(QPoint(650, 100)));

    enemies.push_back(new Seeker(QPoint(200, 150)));
    enemies.push_back(new Seeker(QPoint(500, 150)));


    enemies.push_back(new Fighter(QPoint(50, 200)));
    enemies.push_back(new Fighter(QPoint(150, 200)));
    enemies.push_back(new Fighter(QPoint(250, 200)));
    enemies.push_back(new Fighter(QPoint(350, 200)));
    enemies.push_back(new Fighter(QPoint(450, 200)));
    enemies.push_back(new Fighter(QPoint(550, 200)));
    enemies.push_back(new Fighter(QPoint(650, 200)));


    enemies.push_back(new Fighter(QPoint(50, 300)));
    enemies.push_back(new Fighter(QPoint(150, 300)));
    enemies.push_back(new Fighter(QPoint(250, 300)));
    enemies.push_back(new Fighter(QPoint(350, 300)));
    enemies.push_back(new Fighter(QPoint(450, 300)));
    enemies.push_back(new Fighter(QPoint(550, 300)));
    enemies.push_back(new Fighter(QPoint(650, 300)));

}
/**
  Load Wave 7
  **/
void GameWidget::loadSeventhWave() {

    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Detonator(QPoint(100, 100), 100));
    enemies.push_back(new Detonator(QPoint(350, 100), 100));
    enemies.push_back(new Detonator(QPoint(600, 100), 100));

    enemies.push_back(new Detonator(QPoint(100, 100), 400));
    enemies.push_back(new Detonator(QPoint(350, 100), 400));
    enemies.push_back(new Detonator(QPoint(600, 100), 400));

    enemies.push_back(new Detonator(QPoint(150, 200), 600));
    enemies.push_back(new Detonator(QPoint(550, 200), 600));
    enemies.push_back(new Detonator(QPoint(150, 200), 900));
    enemies.push_back(new Detonator(QPoint(550, 200), 900));

    enemies.push_back(new Heavy(QPoint(200, 200)));
    enemies.push_back(new Heavy(QPoint(500, 200)));

    enemies.push_back(new Fighter(QPoint(50, 200)));
    enemies.push_back(new Fighter(QPoint(150, 200)));
    enemies.push_back(new Fighter(QPoint(250, 200)));
    enemies.push_back(new Fighter(QPoint(350, 200)));
    enemies.push_back(new Fighter(QPoint(450, 200)));
    enemies.push_back(new Fighter(QPoint(550, 200)));
    enemies.push_back(new Fighter(QPoint(650, 200)));


    enemies.push_back(new Fighter(QPoint(50, 300)));
    enemies.push_back(new Fighter(QPoint(150, 300)));
    enemies.push_back(new Fighter(QPoint(250, 300)));
    enemies.push_back(new Fighter(QPoint(350, 300)));
    enemies.push_back(new Fighter(QPoint(450, 300)));
    enemies.push_back(new Fighter(QPoint(550, 300)));
    enemies.push_back(new Fighter(QPoint(650, 300)));

}
/**
  Load Wave 8
  **/
void GameWidget::loadEighthWave() {
    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Boss(QPoint(350, 100)));
    enemies.push_back(new Detonator(QPoint(100, 100), 300));
    enemies.push_back(new Detonator(QPoint(350, 100), 600));
    enemies.push_back(new Detonator(QPoint(600, 100), 700));

    enemies.push_back(new LazerFighter(QPoint(50, 200)));
    enemies.push_back(new LazerFighter(QPoint(150, 200)));
    enemies.push_back(new LazerFighter(QPoint(250, 200)));
    enemies.push_back(new LazerFighter(QPoint(350, 200)));
    enemies.push_back(new LazerFighter(QPoint(450, 200)));
    enemies.push_back(new LazerFighter(QPoint(550, 200)));
    enemies.push_back(new LazerFighter(QPoint(650, 200)));

}
/**
  Load Wave 9
  **/
void GameWidget::loadNinthWave() {

    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Detonator(QPoint(100, 75), 400));
    enemies.push_back(new Detonator(QPoint(350, 75), 400));
    enemies.push_back(new Detonator(QPoint(600, 75), 400));

    enemies.push_back(new Detonator(QPoint(150, 150), 600));
    enemies.push_back(new Detonator(QPoint(550, 150), 600));
    enemies.push_back(new Detonator(QPoint(150, 150), 900));
    enemies.push_back(new Detonator(QPoint(550, 150), 900));

    enemies.push_back(new Fighter(QPoint(50, 200)));
    enemies.push_back(new Swoopfighter(QPoint(150, 200)));
    enemies.push_back(new Fighter(QPoint(250, 200)));
    enemies.push_back(new Swoopfighter(QPoint(350, 200)));
    enemies.push_back(new Fighter(QPoint(450, 200)));
    enemies.push_back(new Swoopfighter(QPoint(550, 200)));
    enemies.push_back(new Fighter(QPoint(650, 200)));


}
/**
  Load Last Wave
  **/
void GameWidget::loadFinalWave() {
    player.setLocation(QPoint(350, 600));
    enemies.push_back(new Fighter(QPoint(50, 100)));
    enemies.push_back(new Swoopfighter(QPoint(150, 100)));
    enemies.push_back(new Fighter(QPoint(250, 100)));
    enemies.push_back(new Swoopfighter(QPoint(350, 100)));
    enemies.push_back(new Fighter(QPoint(450, 100)));
    enemies.push_back(new Swoopfighter(QPoint(550, 100)));
    enemies.push_back(new Fighter(QPoint(650, 100)));

    enemies.push_back(new GiantBoss(QPoint(0, 250)));

}

/**
  Display victory message
  **/
void GameWidget::victory() {
    status = VICTORY;
    ticks = 250;
}

/**
  Destructor.
  **/
GameWidget::~GameWidget() {
    enemies.clear();
}
