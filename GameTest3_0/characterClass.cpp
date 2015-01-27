#include "characterClass.hpp"


GameCharacter::GameCharacter(){
    //Name
    name                = "";

    //Movement
    posX                = 0.0f;
    posY                = 0.0f;
    moving              = false;
    direction           = Down;
    velocity            = 32;

    //Animation
    timeAnimation_ms    = 200;
    timeIdle_ms         = 1000;
    frameCurrent        = 0;

    //Image
    width               = 0;
    height              = 0;
    flipX               = false;
}

void GameCharacter::move(directionEnum dir){
    //Set moving
    moving      = true;

    //Set direction
    direction   = dir;

    //Mirror sprite?
    if(direction == Right){
        flipX = true;
    }else{
        flipX = false;
    }
}

void GameCharacter::update(float scaleX, float scaleY){
    //Create animation frame sequence
    int sequenceLength      = 3;
    int frameUp             = 0;
    int frameDown           = 3;
    int frameSide           = 6;
    bool frameUpdate        = false;
    int frameIdleOffset     = 1;
    int animationSequence[] = {1,0,1,2};
    int frame               = 0;
    sf::IntRect animationFrame;

    if(!moving){
        //Set sub rect according to direction and current frame
        switch (direction){
            case Up:
                //Set current walk up frame
                if(frame != frameUp + frameIdleOffset){
                    frame = frameUp + frameIdleOffset;
                    frameUpdate = true;
                }

                break;
            case Left:
                //Set current walk left frame
                if(frame != frameSide + frameIdleOffset){
                    frame = frameSide + frameIdleOffset;
                    frameUpdate = true;
                }

                break;
            case Right:
                //Set current walk right frame
                if(frame != frameSide + frameIdleOffset){
                    frame = frameSide + frameIdleOffset;
                    frameUpdate = true;
                }

                break;
            default:
                //Set current walk down frame
                if(frame != frameDown + frameIdleOffset){
                    frame = frameDown + frameIdleOffset;
                    frameUpdate = true;
                }

                break;
        }
    }else{
        //Check if animation timer is larger than time limit
        if(timerAnimation.getElapsedTime().asMilliseconds() > timeAnimation_ms){
            //Reset timer
            timerAnimation.restart();

            //Update frame counter
            if(frameCurrent >= sequenceLength){
                frameCurrent = 0;
            }else{
                frameCurrent++;
            }

            //Set sub rect according to direction and current frame
            switch (direction){
                case Up:
                    //Set current walk up frame
                    frame = frameUp + animationSequence[frameCurrent];
                    frameUpdate = true;

                    break;
                case Left:
                    //Set current walk left frame
                    frame = frameSide + animationSequence[frameCurrent];
                    frameUpdate = true;

                    break;
                case Right:
                    //Set current walk right frame
                    frame = frameSide + animationSequence[frameCurrent];
                    frameUpdate = true;

                    break;
                default:
                    //Set current walk down frame
                    frame = frameDown + animationSequence[frameCurrent];
                    frameUpdate = true;

                    break;
            }
        }
    }
    //Set rect
    if(frameUpdate){
        animationFrame.left = frame%(sprite.getTexture()->getSize().x/width)*width;
        animationFrame.top  = frame/(sprite.getTexture()->getSize().x/width)*height;
        //Set width and height
        animationFrame.width    = width;
        animationFrame.height   = height;

        //Set the sub rect of the texture
        sprite.setTextureRect(animationFrame);

        //Set origin
        sprite.setOrigin(width/2.0f, height/2.0f);
    }

    //Update sprite position
    sprite.setPosition(scaleX*posX, scaleY*posY);

    //Update scale
    if(flipX){
        sprite.setScale(-scaleX, scaleY);
    }else{
        sprite.setScale(scaleX, scaleY);
    }

    //Reset moving
    moving = false;
}
