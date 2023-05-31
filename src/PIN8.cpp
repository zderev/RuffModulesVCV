#include "plugin.hpp"

struct PIN8 : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        INPUTS_LEN=8
    };
    enum OutputId {
        POLY_CV_OUTPUT,OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    PIN8() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        for (int k = 0; k < 8; k++) {
            std::string label = std::to_string(k + 1);
            configInput(k, "Channel " + label);
        }
        configOutput(POLY_CV_OUTPUT,"Poly");
    }

    void process(const ProcessArgs& args) override {
        int channels=0;
        for (int k = 0; k < 8; k++) {
            if (inputs[k].isConnected()) {
                channels = k + 1;
                outputs[POLY_CV_OUTPUT].setVoltage(inputs[k].getVoltage(), k);
            } else {
                outputs[POLY_CV_OUTPUT].setVoltage(0.f, k);
            }
        }
        outputs[POLY_CV_OUTPUT].setChannels(channels);
    }
};


struct PIN8Widget : ModuleWidget {
    PIN8Widget(PIN8* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/PIN8.svg")));
        float x=7.62;
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 21.968)),  module, 0));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 34.982)),  module, 1));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 48.004)),  module, 2));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 61.026)),  module, 3));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 74.048)),  module, 4));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 87.070)),  module, 5));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 100.093)), module, 6));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x, 113.115)), module, 7));
        float y=7.5;
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x,y)),module,PIN8::POLY_CV_OUTPUT));
    }
};


Model* modelPIN8 = createModel<PIN8, PIN8Widget>("PIN8");