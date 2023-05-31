#pragma once
#include <rack.hpp>


using namespace rack;


extern Plugin* pluginInstance;
extern Model* modelComplexOscillator;
extern Model* modelVCA;
extern Model* modelNotes;
extern Model* modelPIN8;
extern Model* modelOUT8;
extern Model* modelBlank2R;
extern Model* modelBlank2L;

struct RuffBigRedKnob : RoundKnob { RuffBigRedKnob() {
        sw->setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/ruff-big-red-knob.svg")));
        tw->box.size = sw->box.size;
        fb->box.size = sw->box.size;
        box.size = sw->box.size;
        shadow->box.size = sw->box.size;
        shadow->box.pos = math::Vec(3, sw->box.size.y * 0.025);
        shadow->opacity = 0.3;
        shadow->blurRadius = 0.1;
    }
};

struct RuffBigRedKnob16 : RoundKnob { RuffBigRedKnob16() {
        sw->setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/ruff-big-red-knob16.svg")));
        tw->box.size = sw->box.size;
        fb->box.size = sw->box.size;
        box.size = sw->box.size;
        shadow->box.size = sw->box.size;
        shadow->box.pos = math::Vec(3, sw->box.size.y * 0.025);
        shadow->opacity = 0.3;
        shadow->blurRadius = 0.1;
    }
};

struct RuffHugeRedKnob : RoundKnob { RuffHugeRedKnob() {
        sw->setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/ruff-huge-red-knob30.svg")));
        tw->box.size = sw->box.size;
        fb->box.size = sw->box.size;
        box.size = sw->box.size;
        shadow->box.size = sw->box.size;
        shadow->box.pos = math::Vec(3, sw->box.size.y * 0.025);
        shadow->opacity = 0.3;
        shadow->blurRadius = 0.1;
    }
};

struct RuffCvRedKnob : RoundKnob { RuffCvRedKnob() {
        shadow->opacity = 0.1;
        shadow->blurRadius = 2;
        setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/ruff-cv-red-knob.svg")));
    }
};