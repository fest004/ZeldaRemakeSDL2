#include "../include/zeldaEng.h"
#include "../include/logger.h"
#include "gameObject.cpp"
#include "textureManager.cpp"
#include "tilemap.cpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <bits/chrono.h>
#include <chrono>
#include <iostream>
#include <thread>

gameObject *player;

tilemap *map;

ZeldaEng::ZeldaEng(){};
ZeldaEng::~ZeldaEng(){};

SDL_Renderer *ZeldaEng::renderer = nullptr;

void ZeldaEng::Init(const char *title, int xpos, int ypos, int width,
                    int height, bool fullscreen) {

  LogManager.Init();
  ZeldaTrace("ZeldaEngine V{}.{}", 0, 1);

  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    ZeldaInfo("SDL Initiliazed");

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
      // Test errorcolor
      ZeldaInfo("Window created");
    } else {
      ZeldaError("Window could not be created. SDL Error:", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      // Test Warningcolor
      ZeldaInfo("Renderer Created");
    } else {
      ZeldaError("Renderer could not be created! SDL Error:", SDL_GetError());
    }
    isRunning = true;
  } else {
    isRunning = false;
  }
  map = new tilemap();
  player = new gameObject("../assets/spritesheets/zeldaleftTest.png", 200, 200);
}

void ZeldaEng::EventHandle() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  }
}

void ZeldaEng::Update() {}

void ZeldaEng::FixedUpdate() { player->Update(); }

void ZeldaEng::Render() {
  SDL_RenderClear(renderer);
  // Add stuff to render
  textureManager::setBackground(
      "../assets/backgrounds/CityBackground/city 1/10.png");

  map->DrawTileMap();
  player->Render();
  SDL_RenderPresent(renderer);
}

void ZeldaEng::Clean() {
  ZeldaCritical("ZeldaEngine Closed");
  LogManager.Shutdown();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
}
