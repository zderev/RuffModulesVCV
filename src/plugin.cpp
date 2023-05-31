#include "plugin.hpp"


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;
    p->addModel(modelComplexOscillator);
    p->addModel(modelVCA);
    p->addModel(modelNotes);
    p->addModel(modelPIN8);
    p->addModel(modelOUT8);
}
