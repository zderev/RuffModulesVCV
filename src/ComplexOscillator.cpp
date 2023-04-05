#include "plugin.hpp"


struct ComplexOscillator : Module {
    enum ParamId {
        FREQ1_PARAM,
        FREQ2_PARAM,
        CV1_PARAM,
        CV2_PARAM,
        FM1_PARAM,
        FM2_PARAM,
        MOD_INDEX_PARAM,
        MOD_CV_PARAM,
        HARMONICS_TIMBRE_PARAM,
        HARMONICS_TIMBRE_CV_PARAM,
        HARMONICS_LOW_HIGH_PARAM,
        HARMONICS_LOW_HIGH_CV_PARAM,
        HARMONICS_EVEN_ODD_PARAM,
        HARMONICS_EVEN_ODD_CV_PARAM,
        PARAMS_LEN
    };
    enum InputId {
        V_OCT1_INPUT,
        V_OCT2_INPUT,
        CV1_INPUT,
        CV2_INPUT,
        FM1_INPUT,
        FM2_INPUT,
        MOD_INPUT,
        HARMONICS_TIMBRE_INPUT,
        HARMONICS_LOW_HIGH_INPUT,
        HARMONICS_EVEN_ODD_INPUT,

        OSC1_INPUT_HW,
        OSC2_INPUT_HW,

        INPUTS_LEN

    };
    enum OutputId {
        OSC1_OUTPUT,
        OSC2_OUTPUT,

        V_OCT1_OUTPUT_HW,
        V_OCT2_OUTPUT_HW,
        CV1_OUTPUT_HW,
        CV2_OUTPUT_HW,
        FM1_OUTPUT_HW,
        FM2_OUTPUT_HW,
        MOD_OUTPUT_HW,
        HARMONICS_TIMBRE_OUTPUT_HW,
        HARMONICS_LOW_HIGH_OUTPUT_HW,
        HARMONICS_EVEN_ODD_OUTPUT_HW,

        OUTPUTS_LEN
    };
    enum LightId {
        BLINK_LIGHT,
        LIGHTS_LEN
    };

    ComplexOscillator() {
        config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);


        // PARAMS
        // -- Params OSC
        configParam(FREQ1_PARAM, 0.f, 10.f, 0.f, "OSC1 Freq", "%", 0, 10);
        configParam(FREQ2_PARAM, 0.f, 10.f, 0.f, "OSC2 Freq", "%", 0, 10);
        configParam(CV1_PARAM, -1.f, 1.f, 0.f, "OSC1 CV", "%", 0, 100);
        configParam(CV2_PARAM, -1.f, 1.f, 0.f, "OSC2 CV", "%", 0, 100);

        // -- Params FM
        configParam(FM1_PARAM, 0.f, 10.f, 0.f, "FM1 CV", "%", 0, 10);
        configParam(FM2_PARAM, 0.f, 10.f, 0.f, "FM2 CV", "%", 0, 10);

        // -- Params Modulation
        configParam(MOD_INDEX_PARAM, 0.f, 10.f, 0.f, "Modulation Index", "%", 0, 10);
        configParam(MOD_CV_PARAM, -1.f, 1.f, 0.f, "Modulation CV", "%", 0, 100);

        // -- Params Harmonics
        configParam(HARMONICS_TIMBRE_PARAM, 0.f, 10.f, 0.f, "Harmonics Timbre", "%", 0, 10);
        configParam(HARMONICS_TIMBRE_CV_PARAM, -1.f, 1.f, 0.f, "Harmonics Timbre CV", "%", 0, 100);
        configParam(HARMONICS_LOW_HIGH_PARAM, 0.f, 10.f, 0.f, "Harmonics Low/High", "%", 0, 10);
        configParam(HARMONICS_LOW_HIGH_CV_PARAM, -1.f, 1.f, 0.f, "Harmonics Low/High CV", "%", 0, 100);
        configParam(HARMONICS_EVEN_ODD_PARAM, 0.f, 10.f, 0.f, "Harmonics Even/Odd", "%", 0, 10);
        configParam(HARMONICS_EVEN_ODD_CV_PARAM, -1.f, 1.f, 0.f, "Harmonics Even/Odd CV", "%", 0, 100);


        // INPUTS
        // -- Inputs From VCV
        configInput(CV1_INPUT, "OSC1 CV Input");
        configInput(CV2_INPUT, "OSC2 CV Input");
        configInput(FM1_INPUT, "FM1 Input");
        configInput(FM2_INPUT, "FM2 Input");
        configInput(MOD_INPUT, "Modulation Input");
        configInput(V_OCT1_INPUT, "V/Oct OSC1 Input");
        configInput(V_OCT2_INPUT, "V/Oct OSC1 Input");
        configInput(HARMONICS_TIMBRE_INPUT, "Harmonics Timbre Input");
        configInput(HARMONICS_LOW_HIGH_INPUT, "Harmonics Low/High Input");
        configInput(HARMONICS_EVEN_ODD_INPUT, "Harmonics even/Odd Input");

        // -- Inputs from HW
        configInput(OSC1_INPUT_HW, "HW OSC1 -> VCV OSC1");
        configInput(OSC2_INPUT_HW, "HW OSC2 -> VCV OSC2");


        // OUTPUTS
        // -- Outputs to VCV
        configOutput(OSC1_OUTPUT, "OSC1 Output");
        configOutput(OSC2_OUTPUT, "OSC2 Output");

        // -- Outputs to HW
        configOutput(V_OCT1_OUTPUT_HW, "VCV V/oct -> HW OSC1 V/oct");
        configOutput(V_OCT2_OUTPUT_HW, "VCV V/oct -> HW OSC2 V/oct");
        configOutput(CV1_OUTPUT_HW, "VCV CV1 -> HW OSC1 CV");
        configOutput(CV2_OUTPUT_HW, "VCV CV2 -> HW OSC2 CV");
        configOutput(FM1_OUTPUT_HW, "VCV FM1 -> HW FM1");
        configOutput(FM2_OUTPUT_HW, "VCV FM2 -> HW OSC2 FM2");
        configOutput(MOD_OUTPUT_HW, "VCV MOD -> HW MOD");
        configOutput(HARMONICS_TIMBRE_OUTPUT_HW, "VCV HARMONICS_TIMBRE -> HW HARMONICS_TIMBRE");
        configOutput(HARMONICS_LOW_HIGH_OUTPUT_HW, "VCV HARMONICS_LOW_HIGH -> HW HARMONICS_LOW_HIGH");
        configOutput(HARMONICS_EVEN_ODD_OUTPUT_HW, "VCV HARMONICS_EVEN_ODD -> HW HARMONICS_EVEN_ODD");
    }

    void process(const ProcessArgs& args) override {

        // OSC1 SEND TO HW
//        float audioFromOsc1_HW;
        float cvToOsc1_HW;

        float freqOsc1 = params[FREQ1_PARAM].getValue();
        float attCvOsc1 = params[CV1_PARAM].getValue();
        float cvOsc1 = inputs[CV1_INPUT].getVoltage();

        cvToOsc1_HW = freqOsc1 + attCvOsc1 * cvOsc1;
        outputs[CV1_OUTPUT_HW].setVoltage(cvToOsc1_HW);
    }
};


struct ComplexOscillatorWidget : ModuleWidget {
    ComplexOscillatorWidget(ComplexOscillator* module) {

        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/ComplexOscillator.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.548, 25.39)), module, ComplexOscillator::FREQ1_PARAM));
        addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.977, 44.105)), module, ComplexOscillator::CV1_PARAM));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(8.063, 111.509)), module, ComplexOscillator::CV1_INPUT));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.806, 64.005)), module, ComplexOscillator::CV1_OUTPUT_HW));
    }
};


Model* modelComplexOscillator = createModel<ComplexOscillator, ComplexOscillatorWidget>("ComplexOscillator");

