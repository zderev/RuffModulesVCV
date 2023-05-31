#include "plugin.hpp"

using namespace rack::engine;

struct Blank2L : Module {
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

    Blank2L() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
    }

    void process(const ProcessArgs& args) override {
    }
};

struct Blank2LWidget : ModuleWidget {
    Blank2LWidget(Blank2L* module) {
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/Blank2L.svg")));
    }
};


Model* modelBlank2L = createModel<Blank2L, Blank2LWidget>("Blank2L");