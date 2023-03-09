/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2023 tildearrow and contributors
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

#ifndef _AMIGA_H
#define _AMIGA_H

#include "../dispatch.h"
#include <queue>
#include "../waveSynth.h"

class DivPlatformAmiga: public DivDispatch {
  struct Channel: public SharedChannel<signed char> {
    unsigned int audLoc;
    unsigned short audLen;
    unsigned int audPos;
    unsigned int dmaLoc;
    unsigned short dmaLen;
    int audSub;
    signed char audDat;
    signed char audDat2;
    unsigned char volPos;
    int sample, wave;
    int busClock;
    bool useWave, setPos, useV, useP, dmaOn, audDatClock;
    DivWaveSynth ws;
    Channel():
      SharedChannel<signed char>(64),
      audLoc(0),
      audLen(0),
      audPos(0),
      dmaLoc(0),
      dmaLen(0),
      audSub(0),
      audDat(0),
      audDat2(0),
      volPos(0),
      sample(-1),
      wave(-1),
      busClock(0),
      useWave(false),
      setPos(false),
      useV(false),
      useP(false),
      dmaOn(false),
      audDatClock(false) {}
  };
  Channel chan[4];
  DivDispatchOscBuffer* oscBuf[4];
  bool isMuted[4];
  bool bypassLimits;
  bool amigaModel;
  bool filterOn;

  int filter[2][4];
  int filtConst;
  int filtConstOff, filtConstOn;
  int chipMem;

  unsigned char volTable[64][64];

  unsigned int sampleOff[256];
  bool sampleLoaded[256];

  unsigned char* sampleMem;
  size_t sampleMemLen;

  int sep1, sep2;

  friend void putDispatchChip(void*,int);
  friend void putDispatchChan(void*,int,int);

  public:
    void acquire(short** buf, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    DivDispatchOscBuffer* getOscBuffer(int chan);
    void reset();
    void forceIns();
    void tick(bool sysTick=true);
    void muteChannel(int ch, bool mute);
    int getOutputCount();
    bool keyOffAffectsArp(int ch);
    DivMacroInt* getChanMacroInt(int ch);
    void setFlags(const DivConfig& flags);
    void notifyInsChange(int ins);
    void notifyWaveChange(int wave);
    void notifyInsDeletion(void* ins);
    void renderSamples(int chipID);
    const char** getRegisterSheet();
    const void* getSampleMem(int index=0);
    size_t getSampleMemCapacity(int index=0);
    size_t getSampleMemUsage(int index=0);
    bool isSampleLoaded(int index, int sample);
    int init(DivEngine* parent, int channels, int sugRate, const DivConfig& flags);
    void quit();
};

#endif
