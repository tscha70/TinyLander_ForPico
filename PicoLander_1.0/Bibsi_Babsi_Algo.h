//   >>>>>  T-I-N-Y  L-A-N-D-E-R v1.0 for RPI Pico RP2040  GPLv3 <<<<
//              Programmer: (c) Roger Buehler 2021
//              Contact EMAIL: tscha70@gmail.com
//        Official repository:  https://github.com/tscha70/
//  Tiny Lander v1.0 is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  This game uses features or part of code created by
//  Daniel C (Electro L.I.B) https://www.tinyjoypad.com under GPLv3
//  to work with tinyjoypad game console's standard.
//
// function to convert a vertical bitmap into horizontal bitmap
// https://javl.github.io/image2cpp/ (Draw mode: Vertical - 1 bit per pixel --> Horizontal - 1 bit per pixel
// this library allows to use the vertical bitmaps with the u8g2 - library
void ConvertVerticalToHorizontalBitmap(uint8_t pixel_width, uint8_t inputBitmap[], uint8_t outputBitmap[])
{
  // 00111000 <- line 0
  // 01000100 <- line 1
  // 01000100 <- line 2
  // 01111100 <- line 3...
  int index = 0; // index of the byte to store the new information
  int counter = 0;

  // initialize the array
  for (int r = 0; r < pixel_width; r++)
  {
    outputBitmap[r] = 0;
  }

  // for a byte scan all 8 lines
  for (int line = 0; line < 8; line++)
  {
    // mask must be shifted for each line
    uint8_t mask =  0x01 << line;
    
    // scan all pixels from left to right and then shift one line down
    for (int pix = 0; pix < pixel_width; pix++)
    {
      // after every 8th bit increment the index to store the new byte
      if (counter == 8)
      {
        index++;
        counter = 0;
      }

      // add up the bits for the new byte (vertical to horizontal transformation)
      outputBitmap[index] += ( (inputBitmap[pix] & mask) != 0) << (7 - counter);

      counter++;
    }
  }
}
