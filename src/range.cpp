#include "range.hpp"

unsigned char Range::get_note(int note, int octave) {
  if (note > 80 || note < -50) {
    std::cout << "Invalid note" << std::endl;
    return 129;
  }

  if (octave < 0 || octave > 8) {
    std::cout << "Invalid octave" << std::endl;
    return 129;
  }

  octave += floor(note / 7);

  return (int)m_notes[note % 7] + 12 * octave;
}

void Range::set_fundamental(Note newFundamental) {
  m_fundamental = newFundamental;
  int current_note = m_fundamental;

  m_notes.clear();
  m_notes.push_back(current_note);

  for (int i = 0; i < m_intervals.size(); i++) {
    current_note += m_intervals[i];
    m_notes.push_back(current_note);
  }
}
Note Range::get_fundamental() { return m_fundamental; }
