# ChangeLog

### v1.1.4

- Fix bug where lichen could grow to tiles adjacent to factories
- Fix bug where if one factory fails to build a unit, all other factories fail to build units
- Fix bugs for lichen growth on border overlapping a little
- Fix bug with local CLI using different time setup to kaggle.
- Transfers are irrelevant of unit ID now, and is completely simultaneous.
- Fix bug in factory placement where if placement failed due to using too much metal, we set metal to `init_water`
- Fix bug where printed collided agents is incorrect and shows previous collided units in the same turn
- Fix bug for windows on python 3.7 with asyncio
- Transfers and pickups happen at the end of a turn just before refining and powering
- Fix engine crash where erroring on turn 0 crashes engine
- Lichen growing positons are now computed after everything happens (dig, self destruct, movement)
### v1.1.3

- Fix bug with lichen frontiers being computed incorrectly
- Fix bug where units could transfer more than they held into factories
- Fix bug when traces were printed it errored instead.
- Added some aggregate meta data for preparation of factions
- Fixed critical bug in starter kit where units wasted their time expending energy sending a move center action
### v1.1.2
- Fix bug with C++ agents not running with CLI tool

### v1.1.1

- Allow "negative" bids to bid to go second instead of first in factory placement. The winning bidder is whoever has the higher absolute value bid. The winning bidder now loses water and metal equal to the absolute value of their bid.
- Fixed bug in python kit that adds 1 to the water cost calculation in the `lux/factory.py` file
- Removed an extra `1` in the state representation of move actions left from old code that allowed robots to move more than 1 tile.
- Fixed bug where move center actions weren't repeated.
- Fix visualizer bug where bid for player_1 showed up as player_0's bid
- Fixed repeats. Now repeat `n` times means the action is repeatedly executed `n` times before the next action in the queue. Repeat `-1` means to move the action to the end of the queue.

### v1.1.0

**Most Important Changes:**
- Switch to x,y indexing for all map and position related data. E.g. any code that did `board[y][x]` should be `board[x][y]` now. We will likely not change this ever again and will keep this for the rest of beta and the official competition. For python competitors a simple switch is to just do `board.T[y][x]` which is equivalent to `board[x][y]`.
- Maps are asymmetric now, teams now bid for being first to place a factory instead of a new factory
- Please download the new python starter kits! There are changes to the observations so old code will not work. Moreover, the action space is now different. Instead of specifying whether an action in an action queue should be repeated, you now specify -1 for infinite repeating, and n for n repeats.

Rest of changelog for v1.1.0:

Environment:
- Assymmetric Maps are used now
- Bids are now for who goes first, not who gets an extra factory. If bid is tied, player 0 goes first. This early phase is kept parallel for simplicity. Instead, when it is not your turn to place a factory you must skip your turn. Subsequent turns after the starting phase are still in parallel.
- renamed `board.spawns` -> `board.valid_spawns_mask`. Stores the same information (locations on map that you can spawn a factory on). This changes over time based on where new factories are placed.
- moved `env_cfg.UNIT_ACTION_QUEUE_POWER_COST` to their respective spots under `env_cfg.ROBOTS` e.g. `env_cfg.ROBOTS["LIGHT"].ACTION_QUEUE_POWER_COST`
- Factories can spawn anywhere, but must not overlap any resource or factory.
- Switch to x,y indexing for all map and position related data
- Bumped up initial water/metal resources per factory to 150 each (old: 100)
- Bumped up initial power per factory to 1000 (old: 100)
- Lichen requires 10 units before being able to expand now (old: 20)
- Lichen grows from any square cardinally adjacent to a factory tile now (so an factory without any surrounding rubble will immediately grow 4*3=12 lichen tiles)
- Lichen no longer grows over ice/ore tiles
- Units can transfer any amount and wont have an action cancelled. Environment will internally clip it so that unit only transfers as much as they can and target unit only receives as much as it can. Excess given to a unit is wasted. 
- Factories spawned can be spawned with any amount of resources and the placement won't be cancelled. Instead a warning is given and only the maximum of resources left will be used.
- Factories must spawn 6 or more tiles away from another
- Heavies/Lights dig 2x more rubble per action (Heavies: 10->20, Lights: 1->2)

Visualizer:
- x,y indexing fixes
- fix bug where slider over weather goes off the weather bar

Python Kits:
- Updated to accept some new observation entires (`teams[player].place_first`, `board.valid_spawns_mask`), and removed old ones (`board.spawns`)
- Added utility function to determine if it is your team's turn to place a factory or not

Bug Fixes:
- Lichen water cost costed 1 extra
- Fix bug where added rubble doesn't remove all lichen underneath
- Fix bug where move center costs power
- Fix extra line in stderr logging
- Potential fix of Windows issues with verbose error logging
- Fix bug in lichen growth where lichen would grow to new tiles if there is just 1 lichen, it should be 20
- Fix bug where agent could create infinite robots without spending metal via repeated pickups and builds
- Remove irrelevant rubble information stored in marsquake config.
- Fix bug where rubble goes onto factories when there is a unit on top during marsquakes
- Fix bugs in observation space of off by one error in map shapes
- Clarify in specs and fixed bug where added rubble didn't remove lichen under it.

CLI Tool:
- Fix bug where Java agents can't be run

### v1.0.6
- Fix bug where game ends at turns < 1000 (kaggle-environments bug)
- Fixed bug with self-destruct actions not being validated or added
- Log unit ids that collided. E.g. `14: 1 Units: (unit_11) collided at 33,44 with [1] unit_9 UnitType.HEAVY at (33, 44) surviving`
- Fixed bug where power costs were recomputed after state change in a single step, causing potentially negative energy in edge cases

### v1.0.5

Environment:
- Fixed bug where it outputs TypeError and can't serialize np.int32. This is caused by windows systems using np.int32 (but utils didn't convert it to a int)
- Fixed bug where factories could overlap
- More informative error message when user submits action instead of action queue
- Fixed bug with weather events potentially overlapping
- Fixed bug where units were not capped by their battery capacity
- Fixed bug where we do not invalidate off map transfers

Visualizer:
- Fixed small offset bug in weather schedule display
### v1.0.4

Initial beta release. Good luck!