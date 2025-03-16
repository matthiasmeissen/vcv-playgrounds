declare filename "sound.dsp";
declare name "sound";
import("stdfaust.lib");

freq = hslider("freq",200,50,2000,0.01);

process = os.osc(freq);