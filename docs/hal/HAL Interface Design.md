## HAL Interface Design

The Hardware Abstraction Layer (AKA "HAL") is the lowest layer of engine code which abstracts hardware calls away from direct graphics API calls to allow for easier API consumption and also makes the engine de-coupled from any specific graphics API.


## High Level Design

The high level design of the HAL is an interface level (and no deeper) specification of how engine code can interact with the graphics APIs.

### Groupings - Class Level Design

##### Global Singletons

- Window
- Surface
- Device

##### Pipeline Instanced

- Pipeline
  - Shaders
  - Commands
  - Layouts
