# Simple Module

Building the first vcv rack plugin.

First downloaded the rack sdk, which is a folder and placed in in som space.

Then open a terminal and assing the path of that folder to a global variable with `export RACK_DIR=<Path>` 

This makes that you can use it anywhere.

Then go to a directory where you want the plugin to be place and run the command `$RACK_DIR/helper.py createplugin MyPlugin`

When done you need to add `$RACK_DIR/helper.py createmodule MyModule res/MyModule.svg src/MyModule.cpp` to create the Panel for it.

Then you can run `make install` to place it in your vcv rack plugins directly.