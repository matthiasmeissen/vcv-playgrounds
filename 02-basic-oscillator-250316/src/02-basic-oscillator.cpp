#include "plugin.hpp"
#include "mydsp.h"


struct _02_basic_oscillator : Module {
	enum ParamId {
		FREQ_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	mydsp dspInstance;

	_02_basic_oscillator() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(FREQ_PARAM, 50.f, 2000.f, 200.f, "Frequency");
		configOutput(OUT_OUTPUT, "");


		// Initialize the Faust DSP with a sample rate (e.g., 44100 Hz)
        int sampleRate = 44100;
        dspInstance.init(sampleRate);
        dspInstance.instanceResetUserInterface();
        dspInstance.instanceClear();
	}

	void process(const ProcessArgs& args) override {
		// Update DSP parameters from the module controls
        dspInstance.setFreq(params[FREQ_PARAM].getValue());

        const int count = 1;  // process one sample at a time
        FAUSTFLOAT* in[1] = { nullptr }; // No input signals in this example

        // Prepare an output buffer; our DSP has one output
        FAUSTFLOAT outBuffer[1] = {0};
        FAUSTFLOAT* out[1] = { outBuffer };

        dspInstance.compute(count, in, out);

        // Scale the output to typical Rack levels (e.g., ±5V)
        outputs[OUT_OUTPUT].setVoltage(5.f * outBuffer[0]);
	}
};


struct _02_basic_oscillatorWidget : ModuleWidget {
	_02_basic_oscillatorWidget(_02_basic_oscillator* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/02-basic-oscillator.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.625, 14.0)), module, _02_basic_oscillator::FREQ_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.625, 104.0)), module, _02_basic_oscillator::OUT_OUTPUT));
	}
};


Model* model_02_basic_oscillator = createModel<_02_basic_oscillator, _02_basic_oscillatorWidget>("02-basic-oscillator");