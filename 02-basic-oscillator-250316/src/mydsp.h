#ifndef MYDSP_H
#define MYDSP_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

class mydspSIG0 {
  
  private:
    int iVec0[2];
    int iRec0[2];
  
  public:
    int getNumInputsmydspSIG0() {
        return 0;
    }
    int getNumOutputsmydspSIG0() {
        return 1;
    }
    
    void instanceInitmydspSIG0(int sample_rate) {
        for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
            iVec0[l0] = 0;
        }
        for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
            iRec0[l1] = 0;
        }
    }
    
    void fillmydspSIG0(int count, float* table) {
        for (int i1 = 0; i1 < count; i1 = i1 + 1) {
            iVec0[0] = 1;
            iRec0[0] = (iVec0[1] + iRec0[1]) % 65536;
            table[i1] = std::sin(9.58738e-05f * float(iRec0[0]));
            iVec0[1] = iVec0[0];
            iRec0[1] = iRec0[0];
        }
    }
};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];

class mydsp {
  
 private:
    int iVec1[2];
    FAUSTFLOAT fHslider0;
    int fSampleRate;
    float fConst0;
    float fRec1[2];
  
 public:
    mydsp() { }
    
    // Metadata function (unchanged from original)
    void metadata(void* m) { 
        // Metadata declarations...
        // (Original calls to m->declare(...) have been omitted for brevity.)
    }
    
    virtual int getNumInputs() {
        return 0;
    }
    virtual int getNumOutputs() {
        return 1;
    }
    
    static void classInit(int sample_rate) {
        mydspSIG0* sig0 = newmydspSIG0();
        sig0->instanceInitmydspSIG0(sample_rate);
        sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
        deletemydspSIG0(sig0);
    }
    
    virtual void instanceConstants(int sample_rate) {
        fSampleRate = sample_rate;
        fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
    }
    
    virtual void instanceResetUserInterface() {
        fHslider0 = FAUSTFLOAT(2e+02f);
    }
    
    virtual void instanceClear() {
        for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
            iVec1[l2] = 0;
        }
        for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
            fRec1[l3] = 0.0f;
        }
    }
    
    virtual void init(int sample_rate) {
        classInit(sample_rate);
        instanceInit(sample_rate);
    }
    
    virtual void instanceInit(int sample_rate) {
        instanceConstants(sample_rate);
        instanceResetUserInterface();
        instanceClear();
    }
    
    virtual mydsp* clone() {
        return new mydsp();
    }
    
    virtual int getSampleRate() {
        return fSampleRate;
    }
    
    virtual void buildUserInterface(void* ui_interface) {
        // This function would normally build the UI.
        // It is left unimplemented in this header-only version.
    }
    
    virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
        FAUSTFLOAT* output0 = outputs[0];
        float fSlow0 = fConst0 * float(fHslider0);
        for (int i0 = 0; i0 < count; i0 = i0 + 1) {
            iVec1[0] = 1;
            float fTemp0 = ((1 - iVec1[1]) ? 0.0f : fSlow0 + fRec1[1]);
            fRec1[0] = fTemp0 - std::floor(fTemp0);
            output0[i0] = FAUSTFLOAT(ftbl0mydspSIG0[std::max<int>(0, std::min<int>(int(65536.0f * fRec1[0]), 65535))]);
            iVec1[1] = iVec1[0];
            fRec1[1] = fRec1[0];
        }
    }
    
    // Public setter to update the frequency parameter
    void setFreq(FAUSTFLOAT value) { fHslider0 = value; }
};

#endif  // MYDSP_H
