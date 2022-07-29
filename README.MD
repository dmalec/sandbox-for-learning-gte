# Dan's Sandbox for Learning GTE

This is a personal sandbox for experimenting with the [Generic Tile Engine for the Apple IIgs](https://github.com/lscharen/iigs-game-engine) (GTE). It may not always be in a working state and is best viewed as a curiosity rather than a reference for using GTE. I'm publishing it both as a reference point for when I encounter challenges and in the hopes that others find it interesting.

# Current State

The code currently fills the background with a tile and draws a sprite which can be moved around the screen using the arrow keys. The program can be exited by pressing the `Q` key:

![image filled with rainbow II tiles and a single square sprite](screenshots/Screen_Shot_2022-07-24.png)


# Dev Environment

* [Xcode](https://developer.apple.com/xcode/) 12.4 on macOS Catalina 10.15.7
* [Apple2GSBuildPipeline](https://github.com/jeremysrand/Apple2GSBuildPipeline) v3.0 build system by Jeremy Rand
* [Golden Gate](https://goldengate.gitlab.io/about/) r2.0.6 compatibility layer by Kelvin Sherlock
* [ORCA/C](https://juiced.gs/vendor/byteworks/) compiler and libraries by The Byte Works
* [ORCA/C 2.2.0 B6 update](https://github.com/byteworksinc/ORCA-C/releases/tag/orcac-220b6) by Stephen Heumann

# Runtime Environment

* System 6.0.1 as included in [Apple2GSBuildPipeline](https://github.com/jeremysrand/Apple2GSBuildPipeline)
* [GTE / Tool 160 Beta 1 (KansasFest Edition) - Orca C Demo Branch Build](https://github.com/lscharen/iigs-game-engine/tree/create-orca-c-demo) by Lucas Scharenbroich