#include "plugin.hpp"

using namespace rack::engine;

struct Blank2R : Module {
    enum ParamId {
        PARAMS_LEN
    };
    enum InputId {
        INPUTS_LEN
    };
    enum OutputId {
        OUTPUTS_LEN
    };
    enum LightId {
        LIGHTS_LEN
    };

    Blank2R() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
    }

    void process(const ProcessArgs& args) override {
    }
};

struct Blank2RWidget : ModuleWidget {
    Blank2RWidget(Blank2R* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Blank2R.svg")));
    }
};


Model* modelBlank2R = createModel<Blank2R, Blank2RWidget>("Blank2R");