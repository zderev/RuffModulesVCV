#include "plugin.hpp"


struct VCA : Module {
	enum ParamId {
		AMPLITUDE_PARAM,
		LIN_CV_PARAM,
		CUTOFF_PARAM,
		EXP_CV_PARAM,
		INPUT_GAIN_PARAM,
		FREQ_CV_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		HW_OUTPUT_INPUT,
		IN_LIN_CV_INPUT,
		IN_EXP_CV_INPUT,
		INPUT_INPUT,
		IN_FREQ_CV_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		HW_INPUT_OUTPUT,
		HW_LIN_CV_OUTPUT,
		HW_FREQ_CV_OUTPUT,
		HW_EXP_CV_OUTPUT,
		MODULE_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	VCA() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);

        // Module Params
        configParam(AMPLITUDE_PARAM, 0.f, 10.f, 5, "Amplitude", "%", 0, 10);
        configParam(CUTOFF_PARAM, 0.f, 10.f, 5.f, "Cutoff", "%", 0, 10);
        configParam(FREQ_CV_PARAM, -1.f, 1.f, 0.f, "Freq CV", "%", 0, 100);
        configParam(INPUT_GAIN_PARAM, 0.f, 1.f, 0.5, "Input Gain", "%", 0, 100);
        configParam(LIN_CV_PARAM, -1.f, 1.f, 0.f, "Lin CV", "%", 0, 100);
        configParam(EXP_CV_PARAM, -1.f, 1.f, 0.f, "Exp CV", "%", 0, 100);

        // Module Inputs
        configInput(IN_LIN_CV_INPUT, "Linear");
        configInput(IN_EXP_CV_INPUT, "Exponential");
        configInput(INPUT_INPUT, "Signal");
        configInput(IN_FREQ_CV_INPUT, "Freq");

        // Module Output
        configOutput(MODULE_OUT_OUTPUT, "Signal");

        // HW input
		configInput(HW_OUTPUT_INPUT, "HW output -> VCV");

        // HW Outputs
		configOutput(HW_INPUT_OUTPUT, "VCV -> HW input");
		configOutput(HW_LIN_CV_OUTPUT, "VCV -> HW Lin CV");
		configOutput(HW_FREQ_CV_OUTPUT, "VCV -> HW Freq CV");
		configOutput(HW_EXP_CV_OUTPUT, "VCV -> Exp CV");
	}

    float getSimpleCV(ParamId param_input, InputId cv_input) {
        float paramValue = params[param_input].getValue();
        float cvVoltage = inputs[cv_input].getVoltage();
        return paramValue*cvVoltage;
    }

    float getComplexCV(ParamId param_input, ParamId attenuator_input, InputId cv_input) {
        float paramValue = params[param_input].getValue();
        float attenuatorValue = params[attenuator_input].getValue();
        float cvVoltage = inputs[cv_input].getVoltage();
        return paramValue + attenuatorValue * cvVoltage;
    }
	void process(const ProcessArgs& args) override {
        // ------ VCV -> HW ------//
        float cvToFreq_HW = getComplexCV(CUTOFF_PARAM, FREQ_CV_PARAM, IN_FREQ_CV_INPUT);
        float inputGain_HW = getSimpleCV(INPUT_GAIN_PARAM, INPUT_INPUT);
        float lin_HW = getComplexCV(AMPLITUDE_PARAM, LIN_CV_PARAM, IN_LIN_CV_INPUT);
        float exp_HW = getComplexCV(AMPLITUDE_PARAM, EXP_CV_PARAM, IN_EXP_CV_INPUT);

        outputs[HW_FREQ_CV_OUTPUT].setVoltage(cvToFreq_HW);
        outputs[HW_INPUT_OUTPUT].setVoltage(inputGain_HW);
        outputs[HW_LIN_CV_OUTPUT].setVoltage(lin_HW);
        outputs[HW_EXP_CV_OUTPUT].setVoltage(exp_HW);

        // Module output
        float outputModule = inputs[HW_OUTPUT_INPUT].getVoltage();
        outputs[MODULE_OUT_OUTPUT].setVoltage(outputModule);
	}
};


struct VCAWidget : ModuleWidget {
	VCAWidget(VCA* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/VCA.svg")));

        // Module Params
		addParam(createParamCentered<RuffBigRedKnob16>(mm2px(Vec(15.121, 36.836)), module, VCA::AMPLITUDE_PARAM));
		addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(40.596, 48.654)), module, VCA::LIN_CV_PARAM));
		addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(15.121, 62.584)), module, VCA::CUTOFF_PARAM));
		addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(40.596, 78.933)), module, VCA::EXP_CV_PARAM));
		addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(15.121, 85.584)), module, VCA::INPUT_GAIN_PARAM));
		addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(40.596, 109.349)), module, VCA::FREQ_CV_PARAM));

        // Module Inputs
		addInput(createInputCentered<PJ3410Port>(mm2px(Vec(56.54, 48.518)), module, VCA::IN_LIN_CV_INPUT));
		addInput(createInputCentered<PJ3410Port>(mm2px(Vec(56.54, 79.106)), module, VCA::IN_EXP_CV_INPUT));
		addInput(createInputCentered<PJ3410Port>(mm2px(Vec(15.433, 109.348)), module, VCA::INPUT_INPUT));
		addInput(createInputCentered<PJ3410Port>(mm2px(Vec(56.54, 109.348)), module, VCA::IN_FREQ_CV_INPUT));

        // Module Output
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(56.54, 28.409)), module, VCA::MODULE_OUT_OUTPUT));

        // HW Input (HW -> VCV)
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(56.259, 6.184)), module, VCA::HW_OUTPUT_INPUT));

        // HW Outputs (VCV -> HW)
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(9.004, 6.184)), module, VCA::HW_INPUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.817, 6.184)), module, VCA::HW_LIN_CV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32.631, 6.184)), module, VCA::HW_FREQ_CV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(44.444, 6.184)), module, VCA::HW_EXP_CV_OUTPUT));

	}
};


Model* modelVCA = createModel<VCA, VCAWidget>("VCA");