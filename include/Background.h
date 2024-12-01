#pragma once
#include <raylib.h>
#include "raylib.h"
#include "../lib/bits/stdc++.h"

class Animation;

//Background tiling modes.
enum BackgroundTiling {
    HORIZONTAL, //Horizontal tiling mode.
    VERTICAL,   // Vertical tiling mode.
    BOTH       // Tiling in both horizontal and vertical directions.
};

class Background {
private:
    const Texture& texture;        // Reference to the texture used for the background
    Animation* backgroundAnimation; // Pointer to the background animation
    BackgroundTiling tilingMode;   // Tiling mode for rendering the background

public:
    /*
     * Constructs a new background.
     * texture Reference to the Texture to be used.
     * animation Pointer to the Animation to be used.
     * tiling The tiling mode to be applied when rendering.
    */
    Background(const Texture& texture, Animation* animation = nullptr, BackgroundTiling tiling = BackgroundTiling::BOTH);

    ~Background();

    // Returns the Animation associated with the background.
    const Animation& getAnimation() const;

    // Returns the Texture associated with the background.
    const Texture& getTexture() const;

    // Returns the tiling mode used for rendering.
    BackgroundTiling getTiling() const;
};