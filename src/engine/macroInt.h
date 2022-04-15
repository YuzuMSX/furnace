/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2022 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _MACROINT_H
#define _MACROINT_H

#include "instrument.h"

class DivEngine;

struct DivMacroStruct {
  int pos;
  int val;
  bool has, had, finished, will;
  unsigned int mode;
  void doMacro(DivInstrumentMacro& source, bool released);
  void init() {
    pos=mode=0;
    has=had=will=false;
    // TODO: test whether this breaks anything?
    val=0;
  }
  void prepare(DivInstrumentMacro& source) {
    has=had=will=true;
    mode=source.mode;
  }
  DivMacroStruct():
    pos(0),
    val(0),
    has(false),
    had(false),
    finished(false),
    will(false),
    mode(0) {}
};

class DivMacroInt {
  DivEngine* e;
  DivInstrument* ins;
  DivMacroStruct* macroList[128];
  DivInstrumentMacro* macroSource[128];
  size_t macroListLen;
  int subTick;
  bool released;
  public:
    // common macro
    DivMacroStruct vol;
    DivMacroStruct arp;
    DivMacroStruct duty, wave, pitch, ex1, ex2, ex3;
    DivMacroStruct alg, fb, fms, ams;
    DivMacroStruct panL, panR, phaseReset, ex4, ex5, ex6, ex7, ex8;
  
    // FM operator macro
    struct IntOp {
      DivMacroStruct am, ar, dr, mult;
      DivMacroStruct rr, sl, tl, dt2;
      DivMacroStruct rs, dt, d2r, ssg;
      DivMacroStruct dam, dvb, egt, ksl;
      DivMacroStruct sus, vib, ws, ksr;
      IntOp():
        am(),
        ar(),
        dr(),
        mult(),
        rr(),
        sl(),
        tl(),
        dt2(),
        rs(),
        dt(),
        d2r(),
        ssg(),
        dam(),
        dvb(),
        egt(),
        ksl(),
        sus(),
        vib(),
        ws(),
        ksr() {}
    } op[4];

    /**
     * trigger macro release.
     */
    void release();

    /**
     * trigger next macro tick.
     */
    void next();

    /**
     * set the engine.
     * @param the engine
     */
    void setEngine(DivEngine* eng);

    /**
     * initialize the macro interpreter.
     * @param which an instrument, or NULL.
     */
    void init(DivInstrument* which);

    /**
     * notify this macro interpreter that an instrument has been deleted.
     * @param which the instrument in question.
     */
    void notifyInsDeletion(DivInstrument* which);

    DivMacroInt():
      e(NULL),
      ins(NULL),
      macroListLen(0),
      subTick(0),
      released(false),
      vol(),
      arp(),
      duty(),
      wave(),
      pitch(),
      ex1(),
      ex2(),
      ex3(),
      alg(),
      fb(),
      fms(),
      ams(),
      panL(),
      panR(),
      phaseReset(),
      ex4(),
      ex5(),
      ex6(),
      ex7(),
      ex8() {
      memset(macroList,0,128*sizeof(void*));
      memset(macroSource,0,128*sizeof(void*));
    }
};

#endif
