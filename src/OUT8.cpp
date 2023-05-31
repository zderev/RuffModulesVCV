#include "plugin.hpp"

struct OUT8 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        POLY_CV_INPUT, INPUTS_LEN
    };
    enum OutputId {
        OUTPUTS_LEN = 8
    };
    enum LightId {
        LIGHTS_LEN
    };

    OUT8() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        for(int k = 0; k < 8; k++) {
            std::string label = std::to_string(k + 1);
            configOutput(k, "Channel " + label);
        }
        configInput(POLY_CV_INPUT, "Poly");
    }

    void process(const ProcessArgs& args) override {
        for(int k = 0; k < 8; k++) {
            outputs[k].setVoltage(inputs[POLY_CV_INPUT].getVoltage(k));
        }
    }
};


struct OUT8Widget : ModuleWidget {
    OUT8Widget(OUT8* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/OUT8.svg")));

        float x=7.62;
        float y=7.5;

        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 21.968)),  module, 0));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 34.982)),  module, 1));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 48.004)),  module, 2));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 61.026)),  module, 3));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 74.048)),  module, 4));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 87.070)),  module, 5));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 100.093)), module, 6));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, 113.115)), module, 7));

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x,y)),module,OUT8::POLY_CV_INPUT));
    }
};


Model* modelOUT8 = createModel<OUT8, OUT8Widget>("OUT8");