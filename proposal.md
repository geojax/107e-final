## Title of your project
The PiG (Pi Game)

## Team members
- Micha Rand
- Shizhe He

## Project description/Project Goals
Short description of the basic idea and end goal you are aiming for. 
Include stretch goals and/or fallback position to indicate how you 
might fine-tune the project scope if needed.

### Personal Goals:
- Explore and polish game design
- Examine interaction between Pi and user input sources
- Understand how Pi can output sound
- Write stunning modular game code
- HAVE FUN

### Project Goals:
- Develop a modular game library
- Audio
- Music
- Sprites (Graphics)
- Input: Keyboard/Controller
- Maps

-> put the Pi in a sexy game console case
- Develop Game using modular game library:
	- Either Zelda (RPG), Mario (harder)
	- Easier – Arcade games: Asteroid, Galaga, Space Invaders



## Hardware, budget
Itemize what hardware, if any, you need and your plan for acquiring it.
Rough budget for the project. We will reimburse up to $20 per person.
- Keyboard/Controller
- Speakers
- Basic connectors (cables, …)
- (case: 3D printed)

-> budget: $40

## Tasks, member responsibilities
- Shizhe He: Map, Graphics (faster display clear with standard libraries), User Input, Fonts
- Micha Rand: Game Development, Sound, Storage system

-> in collaboration: Sprites, Game console/library specifications and structure

-> since we are a team of two, we will remain quite flexible throughout the final project and will support each other on different tasks and will possibly have intersecting responsibilities

## Schedule, midpoint milestones
Midpoint milestones:
- Optional: Map: 2D array storing tiles/sprites

-> draw map (x, y in tiles)

=> depending on game
- Sprites (8x8 pixels for one sprite, four ints)

-> malloc sprite memory

-> 2D array of pixels
	- Screen size is 128x128 or 256x256 pixels
	- sprite init (num of sprites 256)
	- Sprite draw(num sprite and x, y of screen)
	- Sprite make(num sprite and array)
- Font: pico8 font
- Fixed color palette using pico8
- Figure out faster clear/using pats libraries
	
- Sound at the end

-> to be further refined as project advances

## Resources needed, issues
Are there books/code/tools/materials that you need access to? 
What are the possible risks to overcome? What are you concerned about? 
How can we help you succeed?