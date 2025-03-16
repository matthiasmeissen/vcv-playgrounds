
# Basic Oscillator

A simple oscillator with a sine wave and adjustable frequency.

Params:
- Freq


## Steps

### Create Files

- Specify the absolute path to the SDK in the terminal: `export RACK_DIR=/Users/matthiasmeissen/Documents/VCV_Rack/Rack-SDK`
- Create a new plugin folder with `$RACK_DIR/helper.py createplugin 02-basic-oscillator`


### Design Panel

witdh: 5.08mm x HP
height: 128.5mm

param: red 
output: blue

Place tempalting elements (circle or rect) in group called components.
Use color codes to specify and add param names as labels.

Save svg in the res folder of the project.

Go into the plugin folder and run this command to create a module linked to the panel `$RACK_DIR/helper.py createmodule 02-basic-oscillator res/02-basic-oscillator.svg src/02-basic-oscillator.cpp`

Adjust the plugin.hpp to include `extern Model* model_02_basic_oscillator;`

And adjust the plugin.cpp to include `p->addModel(model_02_basic_oscillator);`


### Rack Path

The plugin.hpp will complain in line `#include <rack.hpp>` since the file is in a different location.
To fix the missing files you need to adjust the c_cpp_properties.json to include files outside of the working directory. 
To get there you need to press `cmd + shift + p` and type c/c++ edit configurations. 
Then in the includes path add `"/Users/matthiasmeissen/Documents/VCV_Rack/Rack-SDK/**"` to let it use all files in that folder.

In addition you can add the path to the Makefile by adding this `RACK_DIR ?= /Users/matthiasmeissen/Documents/VCV_Rack/Rack-SDK`

## Generating Plugin Code

I am using FAUST to generated the code. I export it as category source and then as c++ code.

The generated .cpp file does not work directly so I need to adjust it by instructing 
to convert it to a .h file with public setter methods and removed inhertiance for all classes in it.

Adjust your parameter ranges in the .cpp file to fit the range of the plugin code.


### Building the plugin

Use `make clean` to clear all files already generated with the make command.

Write `make dist` and copy the files from the dist folder to the vcv rack modules folder.
