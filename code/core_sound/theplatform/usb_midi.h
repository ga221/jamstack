#ifndef USBmidi_h_
#define USBmidi_h_

#include "usb_desc.h"

#if defined(MIDI_INTERFACE)

#include <inttypes.h>

#define USB_MIDI_SYSEX_MAX 290

#ifdef __cplusplus
extern "C"
{
#endif
  void                    usb_midi_configure(void);
  void                    usb_midi_write_packed(uint32_t n);
  void                    usb_midi_send_sysex_buffer_has_term(const uint8_t *data, uint32_t length, uint8_t cable);
  void                    usb_midi_send_sysex_add_term_bytes(const uint8_t *data, uint32_t length, uint8_t cable);
  void                    usb_midi_flush_output(void);
  int                     usb_midi_read(uint32_t channel);
  uint32_t                usb_midi_available(void);
  uint32_t                usb_midi_read_message(void);
  extern uint8_t          usb_midi_msg_cable;
  extern uint8_t          usb_midi_msg_channel;
  extern uint8_t          usb_midi_msg_type;
  extern uint8_t          usb_midi_msg_data1;
  extern uint8_t          usb_midi_msg_data2;
  extern uint8_t          usb_midi_msg_sysex[USB_MIDI_SYSEX_MAX];
  extern uint16_t         usb_midi_msg_sysex_len;
  extern volatile uint8_t usb_configuration;
  extern void (*usb_midi_handleNoteOff)(uint8_t ch, uint8_t note, uint8_t vel);
  extern void (*usb_midi_handleNoteOn)(uint8_t ch, uint8_t note, uint8_t vel);
  extern void (*usb_midi_handleVelocityChange)(uint8_t ch, uint8_t note, uint8_t vel);
  extern void (*usb_midi_handleControlChange)(uint8_t ch, uint8_t control, uint8_t value);
  extern void (*usb_midi_handleProgramChange)(uint8_t ch, uint8_t program);
  extern void (*usb_midi_handleAfterTouch)(uint8_t ch, uint8_t pressure);
  extern void (*usb_midi_handlePitchChange)(uint8_t ch, int pitch);
  extern void (*usb_midi_handleSysExPartial)(const uint8_t *data, uint16_t length, uint8_t complete);
  extern void (*usb_midi_handleSysExComplete)(uint8_t *data, unsigned int size);
  extern void (*usb_midi_handleTimeCodeQuarterFrame)(uint8_t data);
  extern void (*usb_midi_handleSongPosition)(uint16_t beats);
  extern void (*usb_midi_handleSongSelect)(uint8_t songnumber);
  extern void (*usb_midi_handleTuneRequest)(void);
  extern void (*usb_midi_handleClock)(void);
  extern void (*usb_midi_handleStart)(void);
  extern void (*usb_midi_handleContinue)(void);
  extern void (*usb_midi_handleStop)(void);
  extern void (*usb_midi_handleActiveSensing)(void);
  extern void (*usb_midi_handleSystemReset)(void);
  extern void (*usb_midi_handleRealTimeSystem)(uint8_t rtb);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class usb_midi_class
{
public:
  enum MidiType
  {
    InvalidType          = 0x00,
    NoteOff              = 0x80,
    NoteOn               = 0x90,
    AfterTouchPoly       = 0xA0,
    ControlChange        = 0xB0,
    ProgramChange        = 0xC0,
    AfterTouchChannel    = 0xD0,
    PitchBend            = 0xE0,
    SystemExclusive      = 0xF0,
    TimeCodeQuarterFrame = 0xF1,
    SongPosition         = 0xF2,
    SongSelect           = 0xF3,
    TuneRequest          = 0xF6,
    Clock                = 0xF8,
    Start                = 0xFA,
    Continue             = 0xFB,
    Stop                 = 0xFC,
    ActiveSensing        = 0xFE,
    SystemReset          = 0xFF,
  };
  void begin(void) {}
  void end(void) {}
  void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    send(0x80, note, velocity, channel, cable);
  }
  void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    send(0x90, note, velocity, channel, cable);
  }
  void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel, uint8_t cable = 0)
      __attribute__((always_inline))
  {
    send(0xA0, note, pressure, channel, cable);
  }
  void sendAfterTouchPoly(uint8_t note, uint8_t pressure, uint8_t channel, uint8_t cable = 0)
      __attribute__((always_inline))
  {
    send(0xA0, note, pressure, channel, cable);
  }
  void sendControlChange(uint8_t control, uint8_t value, uint8_t channel, uint8_t cable = 0)
      __attribute__((always_inline))
  {
    send(0xB0, control, value, channel, cable);
  }
  void sendProgramChange(uint8_t program, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    send(0xC0, program, 0, channel, cable);
  }
  void sendAfterTouch(uint8_t pressure, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    send(0xD0, pressure, 0, channel, cable);
  }
  void sendPitchBend(int value, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    if(value < -8192)
    {
      value = -8192;
    }
    else if(value > 8191)
    {
      value = 8191;
    }
    value += 8192;
    send(0xE0, value, value >> 7, channel, cable);
  }
  void sendSysEx(uint32_t length, const uint8_t *data, bool hasTerm = false, uint8_t cable = 0)
      __attribute__((always_inline))
  {
    if(cable >= MIDI_NUM_CABLES)
      return;
    if(hasTerm)
    {
      usb_midi_send_sysex_buffer_has_term(data, length, cable);
    }
    else
    {
      usb_midi_send_sysex_add_term_bytes(data, length, cable);
    }
  }
  void sendRealTime(uint8_t type, uint8_t cable = 0) __attribute__((always_inline)) __attribute__((always_inline))
  {
    switch(type)
    {
      case 0xF8:
      case 0xFA:
      case 0xFB:
      case 0xFC:
      case 0xFE:
      case 0xFF: send(type, 0, 0, 0, cable); break;
      default: break;
    }
  }
  void sendTimeCodeQuarterFrame(uint8_t type, uint8_t value, uint8_t cable = 0) __attribute__((always_inline))
  __attribute__((always_inline))
  {
    send(0xF1, ((type & 0x07) << 4) | (value & 0x0F), 0, 0, cable);
  }
  void sendSongPosition(uint16_t beats, uint8_t cable = 0) __attribute__((always_inline))
  {
    send(0xF2, beats, beats >> 7, 0, cable);
  }
  void sendSongSelect(uint8_t song, uint8_t cable = 0) __attribute__((always_inline)) { send(0xF3, song, 0, 0, cable); }
  void sendTuneRequest(uint8_t cable = 0) __attribute__((always_inline)) { send(0xF6, 0, 0, 0, cable); }
  void beginRpn(uint16_t number, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(101, number >> 7, channel, cable);
    sendControlChange(100, number, channel, cable);
  }
  void sendRpnValue(uint16_t value, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(6, value >> 7, channel, cable);
    sendControlChange(38, value, channel, cable);
  }
  void sendRpnIncrement(uint8_t amount, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(96, amount, channel, cable);
  }
  void sendRpnDecrement(uint8_t amount, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(97, amount, channel, cable);
  }
  void endRpn(uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(101, 0x7F, channel, cable);
    sendControlChange(100, 0x7F, channel, cable);
  }
  void beginNrpn(uint16_t number, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(99, number >> 7, channel, cable);
    sendControlChange(98, number, channel, cable);
  }
  void sendNrpnValue(uint16_t value, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(6, value >> 7, channel, cable);
    sendControlChange(38, value, channel, cable);
  }
  void sendNrpnIncrement(uint8_t amount, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(96, amount, channel, cable);
  }
  void sendNrpnDecrement(uint8_t amount, uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(97, amount, channel, cable);
  }
  void endNrpn(uint8_t channel, uint8_t cable = 0) __attribute__((always_inline))
  {
    sendControlChange(99, 0x7F, channel, cable);
    sendControlChange(98, 0x7F, channel, cable);
  }
  void send(uint8_t type, uint8_t data1, uint8_t data2, uint8_t channel, uint8_t cable) __attribute__((always_inline))
  {
    if(cable >= MIDI_NUM_CABLES)
      return;
    if(type < 0xF0)
    {
      if(type < 0x80)
        return;
      type &= 0xF0;
      usb_midi_write_packed((type << 8) | (type >> 4) | ((cable & 0x0F) << 4) | (((channel - 1) & 0x0F) << 8)
                            | ((data1 & 0x7F) << 16) | ((data2 & 0x7F) << 24));
    }
    else if(type >= 0xF8 || type == 0xF6)
    {
      usb_midi_write_packed((type << 8) | 0x0F | ((cable & 0x0F) << 4));
    }
    else if(type == 0xF1 || type == 0xF3)
    {
      usb_midi_write_packed((type << 8) | 0x02 | ((cable & 0x0F) << 4) | ((data1 & 0x7F) << 16));
    }
    else if(type == 0xF2)
    {
      usb_midi_write_packed((type << 8) | 0x03 | ((cable & 0x0F) << 4) | ((data1 & 0x7F) << 16)
                            | ((data2 & 0x7F) << 24));
    }
  }
  void     send_now(void) __attribute__((always_inline)) { usb_midi_flush_output(); }
  uint8_t  analog2velocity(uint16_t val, uint8_t range);
  bool     read(uint8_t channel = 0) __attribute__((always_inline)) { return usb_midi_read(channel); }
  uint8_t  getType(void) __attribute__((always_inline)) { return usb_midi_msg_type; }
  uint8_t  getCable(void) __attribute__((always_inline)) { return usb_midi_msg_cable; }
  uint8_t  getChannel(void) __attribute__((always_inline)) { return usb_midi_msg_channel; }
  uint8_t  getData1(void) __attribute__((always_inline)) { return usb_midi_msg_data1; }
  uint8_t  getData2(void) __attribute__((always_inline)) { return usb_midi_msg_data2; }
  uint8_t *getSysExArray(void) __attribute__((always_inline)) { return usb_midi_msg_sysex; }
  uint16_t getSysExArrayLength(void) __attribute__((always_inline))
  {
    return usb_midi_msg_data2 << 8 | usb_midi_msg_data1;
  }

  void setHandleNoteOff(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity))
  {
    usb_midi_handleNoteOff = fptr;
  }
  void setHandleNoteOn(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) { usb_midi_handleNoteOn = fptr; }
  void setHandleVelocityChange(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity))
  {
    usb_midi_handleVelocityChange = fptr;
  }
  void setHandleAfterTouchPoly(void (*fptr)(uint8_t channel, uint8_t note, uint8_t pressure))
  {
    usb_midi_handleVelocityChange = fptr;
  }
  void setHandleControlChange(void (*fptr)(uint8_t channel, uint8_t control, uint8_t value))
  {
    usb_midi_handleControlChange = fptr;
  }
  void setHandleProgramChange(void (*fptr)(uint8_t channel, uint8_t program)) { usb_midi_handleProgramChange = fptr; }
  void setHandleAfterTouch(void (*fptr)(uint8_t channel, uint8_t pressure)) { usb_midi_handleAfterTouch = fptr; }
  void setHandleAfterTouchChannel(void (*fptr)(uint8_t channel, uint8_t pressure)) { usb_midi_handleAfterTouch = fptr; }
  void setHandlePitchChange(void (*fptr)(uint8_t channel, int pitch)) { usb_midi_handlePitchChange = fptr; }
  void setHandleSysEx(void (*fptr)(const uint8_t *data, uint16_t length, bool complete))
  {
    usb_midi_handleSysExPartial = (void (*)(const uint8_t *, uint16_t, uint8_t))fptr;
  }
  void setHandleSystemExclusive(void (*fptr)(const uint8_t *data, uint16_t length, bool complete))
  {
    usb_midi_handleSysExPartial = (void (*)(const uint8_t *, uint16_t, uint8_t))fptr;
  }
  void setHandleSystemExclusive(void (*fptr)(uint8_t *data, unsigned int size)) { usb_midi_handleSysExComplete = fptr; }
  void setHandleTimeCodeQuarterFrame(void (*fptr)(uint8_t data)) { usb_midi_handleTimeCodeQuarterFrame = fptr; }
  void setHandleSongPosition(void (*fptr)(uint16_t beats)) { usb_midi_handleSongPosition = fptr; }
  void setHandleSongSelect(void (*fptr)(uint8_t songnumber)) { usb_midi_handleSongSelect = fptr; }
  void setHandleTuneRequest(void (*fptr)(void)) { usb_midi_handleTuneRequest = fptr; }
  void setHandleClock(void (*fptr)(void)) { usb_midi_handleClock = fptr; }
  void setHandleStart(void (*fptr)(void)) { usb_midi_handleStart = fptr; }
  void setHandleContinue(void (*fptr)(void)) { usb_midi_handleContinue = fptr; }
  void setHandleStop(void (*fptr)(void)) { usb_midi_handleStop = fptr; }
  void setHandleActiveSensing(void (*fptr)(void)) { usb_midi_handleActiveSensing = fptr; }
  void setHandleSystemReset(void (*fptr)(void)) { usb_midi_handleSystemReset = fptr; }
  void setHandleRealTimeSystem(void (*fptr)(uint8_t realtimebyte)) { usb_midi_handleRealTimeSystem = fptr; };
};

extern usb_midi_class usbMIDI;

#endif

#endif

#endif
