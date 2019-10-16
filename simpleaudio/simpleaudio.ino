/*
This sketch uses the buzzer to play songs.
The Arduino's tone() command will play notes of a given frequency.
We'll provide a function that takes in note characters (a-g),
and returns the corresponding frequency from this table:

  note   frequency
  c     262 Hz
  d     294 Hz
  e     330 Hz
  f     349 Hz
  g     392 Hz
  a     440 Hz
  b     494 Hz
  C     523 Hz

For more information, see http://arduino.cc/en/Tutorial/Tone
*/
  
const int buzzerPin = 13;
const int ledPin = 1;

// We'll set up an array with the notes we want to play
// change these values to make different songs!

// Length must equal the total number of notes and spaces 

const int songLength = 14;

// Notes is an array of text characters corresponding to the notes
// in your song. A space represents a rest (no tone)

String notes[] = {"e","eb", "e","eb", "b","d","c","a","a", "b"}; // a space represents a rest

// Beats is an array values for each note and rest.
// A "1" represents a quarter-note, 2 a half-note, etc.
// Don't forget that the rests (spaces) need a length as well.

int beats[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

// The tempo is how fast to play the song.
// To make the song play faster, decrease this value.

int tempo = 150;


void setup() 
{
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}


void loop() 
{
  int i, duration;
  
  digitalWrite(ledPin,HIGH);
  
  for (i = 0; i < songLength; i++) // step through the song arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms
    
    if (notes[i] == " ")          // is this a rest? 
    {
      delay(duration);            // then pause for a moment
    }
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration); // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }
  
  digitalWrite(ledPin,LOW);
  // We only want to play the song once, so we'll pause forever:
  while(true){}
  // If you'd like your song to play over and over,
  // remove the above statement
}


int frequency(String note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.
  
  int i;
  const int numNotes = 18;  // number of notes we're storing
  
  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  String names[] = {"c", "ch", "db", "d", "dh", "eb", "e", "f", "fh", "gb", "g", "gh", "ab", "a", "ah", "bb", "b", "C"};
  int frequencies[] = {256, 272, 272, 288, 305, 305, 323, 342, 363, 363, 384, 407, 407, 432, 457, 457, 484, 513};
  
  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.
  
  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}
