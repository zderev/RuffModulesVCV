#include "plugin.hpp"
#include<array>

struct ComplexOscillator : Module {
    enum ParamId {
        FREQ1_PARAM,
        FREQ2_PARAM,
        CV1_ATTV_PARAM,
        CV2_ATTV_PARAM,
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
        configParam(FREQ1_PARAM, 0.f, 10.f, 5.f, "OSC1 Freq", "%", 0, 10);
        configParam(FREQ2_PARAM, 0.f, 10.f, 5.f, "OSC2 Freq", "%", 0, 10);
        configParam(CV1_ATTV_PARAM, -1.f, 1.f, 0.f, "OSC1 CV", "%", 0, 100);
        configParam(CV2_ATTV_PARAM, -1.f, 1.f, 0.f, "OSC2 CV", "%", 0, 100);

        // -- Params FM
        configParam(FM1_PARAM, 0.f, 1.f, 0.f, "FM1 CV", "%", 0, 10);
        configParam(FM2_PARAM, 0.f, 1.f, 0.f, "FM2 CV", "%", 0, 10);

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

        // ------ HARDWARE SEND ------ //

        //OSC1
        float cvToOsc1_HW = getComplexCV(FREQ1_PARAM, CV1_ATTV_PARAM, CV1_INPUT);
        float fmOsc1_HW = getSimpleCV(FM1_PARAM, FM1_INPUT);
        float vOctOSC1_HM = inputs[V_OCT1_INPUT].getVoltage();

        outputs[CV1_OUTPUT_HW].setVoltage(cvToOsc1_HW);
        outputs[FM1_OUTPUT_HW].setVoltage(fmOsc1_HW);
        outputs[V_OCT1_OUTPUT_HW].setVoltage(vOctOSC1_HM);



        //OSC1 SEND CV TO HW
        float cvToOsc2_HW = {
                getComplexCV(FREQ2_PARAM, CV2_ATTV_PARAM, CV2_INPUT)
        };
        outputs[CV2_OUTPUT_HW].setVoltage(cvToOsc2_HW);

    }
};

struct RuffBigRedKnob : RoundKnob { RuffBigRedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/custom/ruff-big-red-knob.svg")));
    } };

struct RuffHugeRedKnob : RoundKnob { RuffHugeRedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/custom/ruff-huge-red-knob.svg")));
    } };

struct RuffCvRedKnob : RoundKnob { RuffCvRedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/custom/ruff-cv-red-knob.svg")));
    } };


struct ComplexOscillatorWidget : ModuleWidget {

    std::array<float, 10> createHwOuts(float start_point, float distance) {
        std::array<float, 10> outCols;
        for (int i = 0; i<10; i++) {
            outCols[i] = start_point + distance*i;
        }
        return outCols;
    }

    ComplexOscillatorWidget(ComplexOscillator* module) {



        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/ComplexOscillator.svg")));

        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        addParam(createParamCentered<RuffHugeRedKnob>(mm2px(Vec(100, 30)), module, ComplexOscillator::FREQ2_PARAM));
        addParam(createParamCentered<RuffCvRedKnob>(mm2px(Vec(6.605, 80.561)), module, ComplexOscillator::CV1_ATTV_PARAM));

        // ------ MODULE KNOBS ------
        // OSC1
        addParam(createParamCentered<RuffHugeRedKnob>(mm2px(Vec(30, 30)), module, ComplexOscillator::FREQ1_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(Vec(10, 100))), module, ComplexOscillator::FM1_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(Vec(25, 100))), module, ComplexOscillator::CV1_ATTV_PARAM));

        // ------ MODULE INPUTS ------
        // OSC1
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(10, 115)), module, ComplexOscillator::FM1_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(25, 115)), module, ComplexOscillator::CV1_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(40, 115)), module, ComplexOscillator::V_OCT1_INPUT));

        // ------ HARDWARE OUTPUTS ------
        std::array<float, 10> hw_outs = createHwOuts(12, 11);
        // OSC1
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[0])), module, ComplexOscillator::CV1_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[1])), module, ComplexOscillator::FM1_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[2])), module, ComplexOscillator::V_OCT1_OUTPUT_HW));

        // OSC2
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[3])), module, ComplexOscillator::CV2_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[4])), module, ComplexOscillator::FM2_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[5])), module, ComplexOscillator::V_OCT2_OUTPUT_HW));

        // Modulation
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[6])), module, ComplexOscillator::MOD_OUTPUT_HW));

        // Harmonics
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[7])), module, ComplexOscillator::HARMONICS_TIMBRE_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[8])), module, ComplexOscillator::HARMONICS_LOW_HIGH_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(150, hw_outs[9])), module, ComplexOscillator::HARMONICS_EVEN_ODD_OUTPUT_HW));

    }
};


Model* modelComplexOscillator = createModel<ComplexOscillator, ComplexOscillatorWidget>("ComplexOscillator");

