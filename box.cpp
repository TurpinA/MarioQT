#include "box.h"

Box::Box()
{
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-0.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-1.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-2.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));
    texture.append(QPixmap(loadTexture(":/resources/graphics/blocs/box-used.bmp")).scaled(BLOCSIZE,BLOCSIZE,Qt::IgnoreAspectRatio));

    setCurrentTexture(texture[0]);

    boxContent = EMPTYBOX;
    used = false;
    needToSpawnItem = false;
}

void Box::collisionOnBottomHandler(ObjectModel *o){
    if(dynamic_cast<Mario*>(o) && !used){
        setCurrentTexture(texture[3]);
        needToSpawnItem = true;
        used = true;
        startBlockBounceAnimation();
    }
}

void Box::startBlockBounceAnimation()
{
    if(!timerBounceAnimation.isValid()){
        timerBounceAnimation.start();
    }
    else{
        timerBounceAnimation.restart();
    }
}

void Box::animate()
{
    if(timerBounceAnimation.isValid() && timerBounceAnimation.elapsed() < animationDuration){
        if(timerBounceAnimation.elapsed() < animationDuration/2){
            setPositionY(position.y()-1.5);
        }
        else{
            setPositionY(position.y()+1.5);
        }
    }
    else{
        setPositionY(getHitbox().y());
    }
}

CollectableItem* Box::spawnMushroom(){
    playSound(":/resources/sounds/mushroom-appear.wav");
    CollectableItem * mushroom = new CollectableItem(MUSHROOMCOLLECTABLE, position);
    setBoxNeedToSpawnItem(false);
    return mushroom;
}

CollectableItem* Box::spawnFlower(){
    playSound(":/resources/sounds/mushroom-appear.wav");
    CollectableItem * flower = new CollectableItem(FLOWERCOLLECTABLE, position);
    setBoxNeedToSpawnItem(false);
    return flower;
}

Coin * Box::spawnCoin(){
    playSound(":/resources/sounds/coin.wav");
    Coin * coin = new Coin(true);
    coin->moveTo(position.x()+(BLOCSIZE-coin->getCurrentTexture().width())/2, position.y()-BLOCSIZE);
    setBoxNeedToSpawnItem(false);
    return coin;
}

CollectableItem* Box::spawnStar(){
    playSound(":/resources/sounds/mushroom-appear.wav");
    CollectableItem * star = new CollectableItem(STARCOLLECTABLE, position);
    setBoxNeedToSpawnItem(false);
    return star;
}

void Box::playSound(QString soundPath){
    QSoundEffect * test = new QSoundEffect();
    test->setSource(QUrl::fromLocalFile(soundPath));
    test->setVolume(0.05);
    test->play();
}
