# Engine Config

What -> Engine config defines (per project/game) whether to enable certain features and how to setup features ready for the game.
Why -> Engine config provides a simple way to define and control different aspects of the game engine without directly exposing core engine code to the game developer.
How -> Game devs with load a json file before initializing the engine and they will pass the loaded config into the engine to setup the engine and its functionality as per definitions in the json file.
