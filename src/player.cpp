#include "../include/player.hpp"

Player *Player::s_player;
unsigned int Player::s_current_time = 0;
unsigned int Player::s_current_drums_time = 0;
unsigned int Player::s_note_time = 10000;
Phrase Player::s_phrase;
bool Player::s_need_regeneration = false;
bool Player::s_need_modulation = false;

std::vector<std::vector<unsigned int>> Player::s_current_phrase =
    Player::s_phrase.generate_phrase();

Player::Player() {
  try {
    m_midiout = new RtMidiOut();
    m_midiin = new RtMidiIn();
    m_midiclock = new RtMidiIn();
    // m_midiclock = new RtMidiIn(RtMidi::Api::UNSPECIFIED, "RtMidi Input Client", 1024);
   
    display_available_in_devices();
    display_available_out_devices();

    int in_port;
    std::cout << "Choose LEAPDATA Input port: ";
    std::cin >> in_port;
    m_midiin->openPort(in_port);

    int clock_port;
    std::cout << "Choose CLOCK Input port: ";
    std::cin >> clock_port;
    m_midiclock->openPort(clock_port);

    int out_port;
    std::cout << "Choose NOTES Output port: ";
    std::cin >> out_port;
    m_midiout->openPort(out_port);

    // Set our callback function.  This should be done immediately after
    // opening the port to avoid having incoming messages written to the
    // queue.
    m_midiin->setCallback(&on_midi_in);
    m_midiclock->setCallback(&on_midi_clock);

    // Don't ignore sysex, timing, or active sensing messages.
    m_midiin->ignoreTypes(false, false, false);
  } catch (RtMidiError &error) {
    error.printMessage();
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 15; i++) {
    m_pressed.push_back(std::vector<unsigned int>{});
  }
}

Player *Player::get_instance() {
  if (!s_player)
    s_player = new Player();
  return s_player;
}

void Player::display_available_out_devices() {
  // Check outputs.
  unsigned int nPorts = m_midiout->getPortCount();
  std::cout << "Here are the " << nPorts << " MIDI OUTPUTS ports available:\n";
  std::string portName;
  for (unsigned int i = 0; i < nPorts; i++) {
    try {
      portName = m_midiout->getPortName(i);
    } catch (RtMidiError &error) {
      error.printMessage();
      delete m_midiout;
      exit(EXIT_FAILURE);
    }
    std::cout << "Output port #" << i << ": " << portName << '\n';
  }
  std::cout << '\n';
}

void Player::display_available_in_devices() {
  // Check outputs.
  unsigned int nPorts = m_midiin->getPortCount();
  std::cout << "Here are the " << nPorts << " MIDI INPUTS ports available:\n";
  std::string portName;
  for (unsigned int i = 0; i < nPorts; i++) {
    try {
      portName = m_midiin->getPortName(i);
    } catch (RtMidiError &error) {
      error.printMessage();
      delete m_midiin;
      exit(EXIT_FAILURE);
    }
    std::cout << "Input port #" << i << ": " << portName << '\n';
  }
  std::cout << '\n';
}

void Player::phrase_tick() {
  Player *player = get_instance();

  if (s_note_time > s_current_phrase[s_current_time][2] + 1) {
    player->play_chord(s_current_phrase[s_current_time][0], 3,
                       s_current_phrase[s_current_time][1], 0);
    player->play_chord(s_current_phrase[s_current_time][0], 2, 2, 1);
    s_note_time = 0;

    if (s_current_time == 1 && s_need_modulation) {
      player->modulate();
    }

    if (s_current_time == 0 && s_need_regeneration) {
      std::cout << "restart" << std::endl;
      s_current_phrase = s_phrase.generate_phrase();
      s_need_regeneration = false;
    }

    s_current_time = (s_current_time + 1) % s_current_phrase.size();
  }

  s_note_time++;
}

void Player::modulate() {
  std::cout << "modulation, current fundamental is : "
            << m_range.get_fundamental() << std::endl;
  switch (m_range.get_fundamental()) {
  case C:
    m_range.set_fundamental(Note::F);
    break;
  case C_SHARP:
    m_range.set_fundamental(Note::F_SHARP);
    break;
  case D:
    m_range.set_fundamental(Note::G);
    break;
  case D_SHARP:
    m_range.set_fundamental(Note::G_SHARP);
    break;
  case E:
    m_range.set_fundamental(Note::A);
    break;
  case F:
    m_range.set_fundamental(Note::A_SHARP);
    break;
  case F_SHARP:
    m_range.set_fundamental(Note::B);
    break;
  case G:
    m_range.set_fundamental(Note::C);
    break;
  case G_SHARP:
    m_range.set_fundamental(Note::C_SHARP);
    break;
  case A:
    m_range.set_fundamental(Note::D);
    break;
  case A_SHARP:
    m_range.set_fundamental(Note::D_SHARP);
    break;
  case B:
    m_range.set_fundamental(Note::E);
    break;
  default:
    assert(!"Invalid Note value");
    break;
  }
}

void Player::on_midi_clock(double deltatime,
                           std::vector<unsigned char> *message,
                           void *userData) {

  unsigned int nBytes = message->size();
  
  // note clock
  if ((*message)[1] == (unsigned char)60 &&
      (*message)[0] == (unsigned char)144) {
    phrase_tick();
  }
}

void Player::on_midi_in(double deltatime, std::vector<unsigned char> *message,
                        void *userData) {

  // std::cout << "Ici";

  if ((*message)[0] == (unsigned char)176 &&
      (*message)[1] == (unsigned char)2) {

    std::cout << s_current_time << std::endl;
    
    s_phrase.set_speed(4);

    if ((int)message->at(2) > 32) {
      s_phrase.set_speed(4);
    }

    if ((int)message->at(2) > 64) {
      s_phrase.set_speed(4);
    }

    if (s_current_time == 3) {
      std::cout << "Generation asked" << std::endl;
      s_need_regeneration = true;
    }
  }
}

void Player::play_chord(int note, int octave, int number,
                        unsigned int channel) {
  m_message[2] = 90;

  if (channel > 15) {
    std::cout << "invalid channel" << std::endl;
    return;
  }

  unsigned int first_byte = 128 + channel;

  // Note Off
  m_message[0] = first_byte;
  while (m_pressed[channel].size() > 0) {
    m_message[0] = 128 + channel;
    m_message[1] = m_pressed[channel][m_pressed[channel].size() - 1];
    m_pressed[channel].pop_back();
    m_midiout->sendMessage(&m_message);
  }

  first_byte = 144 + channel;

  // Note On
  m_message[0] = first_byte;
  for (int i = 0; i < number - 1; i++) {
    unsigned int pressed_note = m_range.get_note(note + i * 2, octave);
    m_pressed[channel].push_back(pressed_note);
    m_message[1] = pressed_note;
    m_midiout->sendMessage(&m_message);
  }
}


// void Player::drums_tick() {
//   s_current_drums_time = (s_current_drums_time + 1) % 64;
// }


// drums clock
// if ((*message)[1] == (unsigned char)60 &&
//     (*message)[0] == (unsigned char)145) {
//   drums_tick();
// }