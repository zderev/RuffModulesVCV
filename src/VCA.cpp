#include "plugin.hpp"


struct VCA : Module {
	enum ParamId {
		CUTOFF_PARAM,
		LIN_CV_PARAM,
		INPUT_GAIN_PARAM,
		EXP_CV_PARAM,
		FREQ_CV_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN_LIN_CV_INPUT,
		IN_EXP_CV_INPUT,
		INPUT_INPUT,
		IN_FREQ_CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		HW_INPUT_OUTPUT,
		HW_OOUTPUT_OUTPUT,
		HW_FREQ_CV_OUTPUT,
		HW_EXP_CV_OUTPUT,
		HW_LIN_CV_OUTPUT,
		OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	VCA() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(CUTOFF_PARAM, 0.f, 1.f, 0.f, "");
		configParam(LIN_CV_PARAM, 0.f, 1.f, 0.f, "");
		configParam(INPUT_GAIN_PARAM, 0.f, 1.f, 0.f, "");
		configParam(EXP_CV_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FREQ_CV_PARAM, 0.f, 1.f, 0.f, "");
		configInput(IN_LIN_CV_INPUT, "");
		configInput(IN_EXP_CV_INPUT, "");
		configInput(INPUT_INPUT, "");
		configInput(IN_FREQ_CV_INPUT, "");
		configOutput(HW_INPUT_OUTPUT, "");
		configOutput(HW_OOUTPUT_OUTPUT, "");
		configOutput(HW_FREQ_CV_OUTPUT, "");
		configOutput(HW_EXP_CV_OUTPUT, "");
		configOutput(HW_LIN_CV_OUTPUT, "");
		configOutput(OUT_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct VCAWidget : ModuleWidget {
	VCAWidget(VCA* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/VCA.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.433, 28.409)), module, VCA::CUTOFF_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(44.3, 48.654)), module, VCA::LIN_CV_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.433, 68.879)), module, VCA::INPUT_GAIN_PARAM));
		addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(44.3, 78.933)), module, VCA::EXP_CV_PARAM));
		addParam(createParamCentered<RuffBigRedKnob16>(mm2px(Vec(44.3, 109.349)), module, VCA::FREQ_CV_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(62.361, 48.518)), module, VCA::IN_LIN_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(62.361, 79.106)), module, VCA::IN_EXP_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.433, 109.349)), module, VCA::INPUT_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(62.361, 109.348)), module, VCA::IN_FREQ_CV_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.416, 8.3)), module, VCA::HW_INPUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.876, 8.3)), module, VCA::HW_OOUTPUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(36.335, 8.3)), module, VCA::HW_FREQ_CV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(50.794, 8.3)), module, VCA::HW_EXP_CV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(65.254, 8.3)), module, VCA::HW_LIN_CV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(62.361, 28.409)), module, VCA::OUT_OUTPUT));
	}
};


Model* modelVCA = createModel<VCA, VCAWidget>("VCA");