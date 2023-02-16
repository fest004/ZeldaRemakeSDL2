#include "../include/zeldaEng.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

ZeldaEng *engine = nullptr;

int main(int argc, const char *argv[]) {
  engine = new ZeldaEng();
  engine->Init("Zelda", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
               600, false);

  auto lastUpdate = std::chrono::high_resolution_clock::now();
  const float updatesPerSecond = 50.0f;

  while (engine->Running()) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<float>(currentTime - lastUpdate).count();
    Timestep timestep = time;

    engine->EventHandle();
    engine->Update();
    engine->Render();

    if (timestep.GetSeconds() >= 1.0f / updatesPerSecond) {
      engine->FixedUpdate();
      lastUpdate = currentTime;
    }
  }

  engine->Clean();
  return 0;
}