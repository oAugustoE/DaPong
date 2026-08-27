cmake_minimum_required(VERSION 4.3)
project(DaPong C)

set(CMAKE_C_STANDARD 11)

add_executable(DaPong
        main.c
        Player/player.c
        config/config.h
        Ball/Ball.c
        Canvas/Canvas.c
        Player/player.h
        Canvas/Canvas.h
        Ball/Ball.h
        Render/render.c
        Render/render.h
        Input/Input.c
        Input/Input.h)
