#ifndef _ANIMATION_H
#define _ANIMATION_H

struct Animation
{
    int frames;

    int speed;

    Animation() = default;

    Animation(int frames_, int speed_)
        : frames(frames_), speed(speed_) {}
};

#endif // _ANIMATION_H
