#include "plugin.hpp"


struct ComplexOscillator : Module {
    enum ParamId {
        FREQ_PARAM,
        CV_PARAM,
        PARAMS_LEN
    };
    enum InputId {
        CV_INPUT,
        INPUTS_LEN
    };
    enum OutputId {
        CV_OUTPUT,
        OUTPUTS_LEN
    };
    enum LightId {
        BLINK_LIGHT,
        LIGHTS_LEN
    };

    ComplexOscillator() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configParam(FREQ_PARAM, 0.f, 10.f, 0.f, string::f("Freq Master OSC"), "%", 0, 10);
        configParam(CV_PARAM, -1.f, 1.f, 0.f, string::f("CV Master OSC"), "%", 0, 100);
        configInput(CV_INPUT, "");
        configOutput(CV_OUTPUT, "");
    }

    void process(const ProcessArgs& args) override {

        float out = 0.f;

        float freq = params[FREQ_PARAM].getValue();
        float gain = params[CV_PARAM].getValue();
        float cvInput = inputs[CV_INPUT].getVoltage();

        out+=freq + gain*cvInput;

        outputs[CV_OUTPUT].setVoltage(out);
    }
};


struct ComplexOscillatorWidget : ModuleWidget {
    ComplexOscillatorWidget(ComplexOscillator* module) {
//        this->module = module;
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/ComplexOscillator.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.548, 25.39)), module, ComplexOscillator::FREQ_PARAM));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.977, 44.105)), module, ComplexOscillator::CV_PARAM));

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.806, 64.005)), module, ComplexOscillator::CV_OUTPUT));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.063, 111.509)), module, ComplexOscillator::CV_INPUT));
    }
};


Model* modelComplexOscillator = createModel<ComplexOscillator, ComplexOscillatorWidget>("ComplexOscillator");

