# Introduction

Simple DirectMedia Layer.

<https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer>

<https://www.libsdl.org/>

Cross platform library for user input (mouse, keyboard, touch), graphics, sound, haptics. Basically a huge wrapper on top of tons of incompatible APIs.

There is some support for hardware acceleration it seems: <https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html>

Started by venerable Loki software <https://en.wikipedia.org/wiki/Loki_Software>

Widely cross platform: Windows, Mac, Linux, Android, [iOS](http://stackoverflow.com/questions/23063659/porting-sdl-app-to-ios).

Widely popular. Steam for Linux embeds it, and the lead dev is working for them as of 2016. 2014 Steam talk <https://www.youtube.com/watch?v=MeMPCSqQ-34>

## Contribute

- issue tracker <https://bugzilla.libsdl.org>
- unofficial GitHub mirror: <https://github.com/spurious/SDL-mirror>

## Bugs

2.0.4: with `~/.Xmodmap` key remapping, `SDL_GetKeyboardState(NULL)` + `SDL_SCANCODE_ESCAPE` does not work (uses old key) while `SDL_PollEvent(&event)` + `SDLK_ESCAPE` does.

- http://forums.libsdl.org/viewtopic.php?p=42784&sid=c6f3d4c6aa9c0c9faf1d9d031c9a2c98
