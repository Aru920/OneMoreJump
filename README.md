# One More Jump

A small 2D platformer prototype made in Unreal Engine 5 using Paper2D and C++.

The goal is simple: reach the door, collect coins, avoid hazards, and use checkpoints to recover after mistakes. I made this as a focused gameplay prototype to practice clean platformer systems, Paper2D setup, simple UI flow, and C++ gameplay actors.

## Gameplay

The player moves through a short side-scrolling level with hazards and platforming objects.

Features include:

- Left/right movement
- Jump and double jump
- Coins with pickup feedback
- Checkpoints
- Spike and hazard death volumes
- Slime blocks that bounce the player upward
- Propeller belts that launch the player forward
- Moving platforms
- Moving spike platforms
- Win door
- Start menu, player HUD, death menu, and win screen

## Main Systems

### Player

The player character is built from a C++ `PaperCharacter` base.

It handles:

- Basic movement
- Jumping
- Double jump
- Flipbook switching for idle, run, jump, and fall
- Death state
- Respawning from checkpoint
- Win state
- Coin tracking
- Elapsed time tracking

### Level Actors

Most level objects are made as small C++ actor bases so they can be reused in Blueprints.

Examples:

- `OMJDeathVolume`
- `OMJSlimeBlock`
- `OMJMovingPlatform`
- `OMJMovingDeathPlatform`
- `OMJCoin`
- `OMJCheckpoint`
- `OMJWinDoor`
- `OMJPropellerBelt`

The idea was to keep the logic simple in C++ and leave visuals, flipbooks, effects, and tuning to Blueprint.

### UI

The UI is intentionally simple.

It includes:

- Start menu
- HUD with coins and elapsed time
- Death menu
- Win screen

The C++ side exposes small helper functions and events so the widgets can stay easy to wire.

## What I Practiced

This project helped me practice:

- Paper2D character setup
- Tile map collision workflow
- Reusable C++ gameplay actors
- Blueprint events from C++
- Simple UI flow
- Checkpoint and respawn logic
- Clean gameplay state handling
- Keeping systems small instead of overbuilding them

## Tech

- Unreal Engine 5
- C++
- Blueprint
- Paper2D

## Status

Prototype complete.
