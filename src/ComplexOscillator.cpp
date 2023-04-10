#include "plugin.hpp"
#include<array>

struct ComplexOscillator : Module {
    enum ParamId {
        FREQ1_PARAM,
        FREQ2_PARAM,
        CV1_ATTNV_PARAM,
        CV2_ATTNV_PARAM,
        FM1_PARAM,
        FM2_PARAM,
        MOD_INDEX_PARAM,
        MOD_CV_ATTNV_PARAM,
        HARMONICS_TIMBRE_PARAM,
        HARMONICS_TIMBRE_CV_ATTNV_PARAM,
        HARMONICS_LOW_HIGH_PARAM,
        HARMONICS_LOW_HIGH_CV_ATTNV_PARAM,
        HARMONICS_EVEN_ODD_PARAM,
        HARMONICS_EVEN_ODD_CV_ATTNV_PARAM,
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
        configParam(CV1_ATTNV_PARAM, -1.f, 1.f, 0.f, "OSC1 CV", "%", 0, 100);
        configParam(CV2_ATTNV_PARAM, -1.f, 1.f, 0.f, "OSC2 CV", "%", 0, 100);

        // -- Params FM
        configParam(FM1_PARAM, 0.f, 1.f, 0.f, "FM1 CV", "%", 0, 10);
        configParam(FM2_PARAM, 0.f, 1.f, 0.f, "FM2 CV", "%", 0, 10);

        // -- Params Modulation
        configParam(MOD_INDEX_PARAM, 0.f, 10.f, 0.f, "Modulation Index", "%", 0, 10);
        configParam(MOD_CV_ATTNV_PARAM, -1.f, 1.f, 0.f, "Modulation CV", "%", 0, 100);

        // -- Params Harmonics
        configParam(HARMONICS_TIMBRE_PARAM, 0.f, 10.f, 0.f, "Harmonics Timbre", "%", 0, 10);
        configParam(HARMONICS_TIMBRE_CV_ATTNV_PARAM, -1.f, 1.f, 0.f, "Harmonics Timbre CV", "%", 0, 100);
        configParam(HARMONICS_LOW_HIGH_PARAM, 0.f, 10.f, 0.f, "Harmonics Low/High", "%", 0, 10);
        configParam(HARMONICS_LOW_HIGH_CV_ATTNV_PARAM, -1.f, 1.f, 0.f, "Harmonics Low/High CV", "%", 0, 100);
        configParam(HARMONICS_EVEN_ODD_PARAM, 0.f, 10.f, 0.f, "Harmonics Even/Odd", "%", 0, 10);
        configParam(HARMONICS_EVEN_ODD_CV_ATTNV_PARAM, -1.f, 1.f, 0.f, "Harmonics Even/Odd CV", "%", 0, 100);


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

        // ------ HARDWARE OUTPUTS ------ --> TO AUDIO DEVICE//

        //OSC1
        float cvToOsc1_HW = getComplexCV(FREQ1_PARAM, CV1_ATTNV_PARAM, CV1_INPUT);
        float fmOsc1_HW = getSimpleCV(FM1_PARAM, FM1_INPUT);
        float vOctOSC1_HM = inputs[V_OCT1_INPUT].getVoltage();
        
        outputs[CV1_OUTPUT_HW].setVoltage(cvToOsc1_HW);
        outputs[FM1_OUTPUT_HW].setVoltage(fmOsc1_HW);
        outputs[V_OCT1_OUTPUT_HW].setVoltage(vOctOSC1_HM);

        // MODULATION
        float cvToMod_HW = getComplexCV(MOD_INDEX_PARAM, MOD_CV_ATTNV_PARAM, MOD_INPUT);
        outputs[MOD_OUTPUT_HW].setVoltage(cvToMod_HW);

        //OSC2
        float cvToOsc2_HW = getComplexCV(FREQ2_PARAM, CV2_ATTNV_PARAM, CV2_INPUT);
        float fmOsc2_HW = getSimpleCV(FM2_PARAM, FM2_INPUT);
        float vOctOSC2_HM = inputs[V_OCT2_INPUT].getVoltage();

        outputs[CV2_OUTPUT_HW].setVoltage(cvToOsc2_HW);
        outputs[FM2_OUTPUT_HW].setVoltage(fmOsc2_HW);
        outputs[V_OCT2_OUTPUT_HW].setVoltage(vOctOSC2_HM);
        
        // HARMONICS
        float harmTimbre_HW = {
                getComplexCV(HARMONICS_TIMBRE_PARAM, HARMONICS_TIMBRE_CV_ATTNV_PARAM, HARMONICS_TIMBRE_INPUT)
        };
        float harmLowHigh_HW = {
                getComplexCV(HARMONICS_LOW_HIGH_PARAM, HARMONICS_LOW_HIGH_CV_ATTNV_PARAM, HARMONICS_LOW_HIGH_INPUT)
        };
        float harmEvenOdd_HW = {
                getComplexCV(HARMONICS_EVEN_ODD_PARAM, HARMONICS_EVEN_ODD_CV_ATTNV_PARAM, HARMONICS_EVEN_ODD_INPUT)
        };

        outputs[HARMONICS_TIMBRE_OUTPUT_HW].setVoltage(harmTimbre_HW);
        outputs[HARMONICS_LOW_HIGH_OUTPUT_HW].setVoltage(harmLowHigh_HW);
        outputs[HARMONICS_EVEN_ODD_OUTPUT_HW].setVoltage(harmEvenOdd_HW);

        // ------ HARDWARE INPUTS ------ FROM AUDIO DEVICE --> IN MODULE//
        float osc1input_HW = inputs[OSC1_INPUT_HW].getVoltage();
        float osc2input_HW = inputs[OSC1_INPUT_HW].getVoltage();
        outputs[OSC1_OUTPUT].setVoltage(osc1input_HW);
        outputs[OSC2_OUTPUT].setVoltage(osc2input_HW);


    }
};

struct RuffBigRedKnob : RoundKnob { RuffBigRedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/custom/ruff-big-red-knob.svg")));
    } };

struct RuffHugeRedKnob : RoundKnob { RuffHugeRedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/custom/ruff-huge-red-knob30.svg")));
    } };

struct RuffCvRedKnob : RoundKnob { RuffCvRedKnob() {
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/custom/ruff-cv-red-knob.svg")));
    } };


struct ComplexOscillatorWidget : ModuleWidget {

    std::array<float, 12> createObjects(float start_point, float distance, int n) {
        std::array<float, 12> outCols;
        for (int i = 0; i<n; i++) {
            outCols[i] = start_point + distance*i;
        }
        return outCols;
    }

    ComplexOscillatorWidget(ComplexOscillator* module) {
        
        
        setModule(module);
        setPanel(createPanel(asset::plugin(pluginInstance, "res/ComplexOscillator.svg")));

//        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
//        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
//        addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
//        addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));



        float x_distance = 14;
        float y_distance = 16;
        float dist_osc_mod = 20;
        float KnobPosition_y = 100;
        float PortPosition_y = KnobPosition_y + y_distance;
        float osc1_start_point = 10;
        std::array<float, 12> osc1_Objects = createObjects(osc1_start_point, x_distance, 3);
        float freqPosition_x = osc1_Objects[1];
        float freqPosition_y = 40;

        // ------ MODULE KNOBS ------

        // OSC1 KNOBS
        addParam(createParamCentered<RuffHugeRedKnob>(mm2px(Vec(freqPosition_x, freqPosition_y)), module, ComplexOscillator::FREQ1_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(osc1_Objects[0], KnobPosition_y)), module, ComplexOscillator::FM1_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(osc1_Objects[1], KnobPosition_y)), module, ComplexOscillator::CV1_ATTNV_PARAM));

        // MODULATION KNOBS
        float modulation_x = osc1_Objects[2] + dist_osc_mod;
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(modulation_x, KnobPosition_y - y_distance)), module, ComplexOscillator::MOD_INDEX_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(modulation_x, KnobPosition_y )), module, ComplexOscillator::MOD_CV_ATTNV_PARAM));

        // OSC2 KNOBS
        float osc2_start_point = modulation_x + dist_osc_mod;
        std::array<float, 12> osc2_Objects = createObjects(osc2_start_point, x_distance, 3);

        float freqPositionOSC2_x = 2*modulation_x - freqPosition_x;
        addParam(createParamCentered<RuffHugeRedKnob>(mm2px(Vec(freqPositionOSC2_x, freqPosition_y)), module, ComplexOscillator::FREQ2_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(osc2_Objects[0], KnobPosition_y)), module, ComplexOscillator::FM2_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(osc2_Objects[1], KnobPosition_y)), module, ComplexOscillator::CV2_ATTNV_PARAM));

        // HARMONICS KNOBS
        float harmParamStart_x = osc2_Objects[1] + 2*x_distance;
        float harmCvStart_x = harmParamStart_x + x_distance;
        std::array<float, 12> harmParamObjects_y = createObjects(PortPosition_y-y_distance, -y_distance*2, 3);

        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(harmParamStart_x, harmParamObjects_y[0])), module, ComplexOscillator::HARMONICS_TIMBRE_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(harmParamStart_x, harmParamObjects_y[1])), module, ComplexOscillator::HARMONICS_LOW_HIGH_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(harmParamStart_x, harmParamObjects_y[2])), module, ComplexOscillator::HARMONICS_EVEN_ODD_PARAM));
        
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(harmCvStart_x, harmParamObjects_y[0])), module, ComplexOscillator::HARMONICS_TIMBRE_CV_ATTNV_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(harmCvStart_x, harmParamObjects_y[1])), module, ComplexOscillator::HARMONICS_LOW_HIGH_CV_ATTNV_PARAM));
        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(harmCvStart_x, harmParamObjects_y[2])), module, ComplexOscillator::HARMONICS_EVEN_ODD_CV_ATTNV_PARAM));

//        addParam(createParamCentered<RuffBigRedKnob>(mm2px(Vec(harmCvStart_x+10, harmParamObjects_y[2])), module, ComplexOscillator::HARMONICS_EVEN_ODD_CV_ATTNV_PARAM));

        // HARMONICS PORTS
        std::array<float, 12> harmPortsObjects_y = createObjects(PortPosition_y, -y_distance*2, 3);
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(harmCvStart_x, harmPortsObjects_y[0])), module, ComplexOscillator::HARMONICS_TIMBRE_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(harmCvStart_x, harmPortsObjects_y[1])), module, ComplexOscillator::HARMONICS_LOW_HIGH_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(harmCvStart_x, harmPortsObjects_y[2])), module, ComplexOscillator::HARMONICS_EVEN_ODD_INPUT));

        // ------ MODULE PORTS ------
        // OSC1
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(osc1_Objects[0], PortPosition_y)), module, ComplexOscillator::FM1_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(osc1_Objects[1], PortPosition_y)), module, ComplexOscillator::CV1_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(osc1_Objects[2], PortPosition_y)), module, ComplexOscillator::V_OCT1_INPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(osc1_Objects[2], freqPosition_y + 20)), module, ComplexOscillator::OSC1_OUTPUT));

        // MODULATION
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(modulation_x, PortPosition_y)), module, ComplexOscillator::MOD_INPUT));

        // OSC2
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(osc2_Objects[0], PortPosition_y)), module, ComplexOscillator::FM2_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(osc2_Objects[1], PortPosition_y)), module, ComplexOscillator::CV2_INPUT));
        addInput(createInputCentered<PJ3410Port>(mm2px(Vec(osc2_Objects[2], PortPosition_y)), module, ComplexOscillator::V_OCT2_INPUT));
        addOutput(createOutputCentered<CL1362Port>(mm2px(Vec(osc2_Objects[2], freqPosition_y + 20)), module, ComplexOscillator::OSC2_OUTPUT));

        // ------ HARDWARE INPUTS/OUTPUTS ------
        std::array<float, 12> hw_outs = createObjects(5, 12, 12);
        float hwPosition = 5;

        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(hw_outs[0], hwPosition)), module, ComplexOscillator::OSC1_INPUT_HW));
        addInput(createInputCentered<PJ301MPort>(mm2px(Vec(hw_outs[1], hwPosition)), module, ComplexOscillator::OSC2_INPUT_HW));

        // OSC1
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[2], hwPosition)), module, ComplexOscillator::CV1_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[3], hwPosition)), module, ComplexOscillator::FM1_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[4], hwPosition)), module, ComplexOscillator::V_OCT1_OUTPUT_HW));

        // OSC2
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[5], hwPosition)), module, ComplexOscillator::CV2_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[6], hwPosition)), module, ComplexOscillator::FM2_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[7], hwPosition)), module, ComplexOscillator::V_OCT2_OUTPUT_HW));

        // Modulation
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[8], hwPosition)), module, ComplexOscillator::MOD_OUTPUT_HW));

        // Harmonics
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[9], hwPosition)), module, ComplexOscillator::HARMONICS_TIMBRE_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[10], hwPosition)), module, ComplexOscillator::HARMONICS_LOW_HIGH_OUTPUT_HW));
        addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(hw_outs[11], hwPosition)), module, ComplexOscillator::HARMONICS_EVEN_ODD_OUTPUT_HW));

    }
};


Model* modelComplexOscillator = createModel<ComplexOscillator, ComplexOscillatorWidget>("ComplexOscillator");

