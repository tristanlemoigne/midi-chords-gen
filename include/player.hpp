#pragma once

#include <iostream>
#include <vector>

#include "rtmidi.h"
#include "notes.hpp"
#include "phrase.hpp"
#include "range.hpp"

class Player {
protected:
  RtMidiOut *m_midiout = 0;
  RtMidiIn *m_midiin = 0;
  RtMidiIn *m_midiclock = 0;
  std::vector<unsigned char> m_message{0, 0, 0};
  Range m_range{Note::A, 0};
  std::vector<std::vector<unsigned int>> m_pressed;

  Player();

  static unsigned int s_current_drums_time;

  static unsigned int s_current_time;
  static unsigned int s_note_time;
  static Player *s_player;
  static std::vector<std::vector<unsigned int>> s_current_phrase;
  static Phrase s_phrase;
  static bool s_need_regeneration;
  static bool s_need_modulation;

public:
  void display_available_out_devices();
  void display_available_in_devices();

  void play_chord(int, int, int, unsigned int);
  void modulate();

  static void phrase_tick();
  static void drums_tick();

  static Player *get_instance();
  static void on_midi_clock(double deltatime,
                            std::vector<unsigned char> *message,
                            void *userData);
  static void on_midi_in(double deltatime, std::vector<unsigned char> *message,
                         void *userData);
};