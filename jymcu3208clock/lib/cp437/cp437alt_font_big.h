// cp437alt_font.h

// 6x7 bit patterns for the CP437 font
// Code page 437 is the character set of the original IBM PC
// (personal computer), or MS-DOS.
//
// modded for 6x8 numbers by replacing 10 characters
// starting at 0xC0 in the character table

// 2016-02-10

// format:
// Bytes correspond to columns, left to right
//
// with the high bit at the bottom
// and the first byte on the left
//
// B0.0 B1.0 B2.0...
// B0.1 B1.1 B2.1...
// B0.2 B1.2 B2.2...
// ...
// B0.7 B1.7 B2.7...


const byte working_font [127] [8] PROGMEM = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // 0x00
  { 0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x06, 0x00 }, // 0x01
  { 0x7E, 0xFF, 0xEB, 0xCF, 0xCF, 0xEB, 0xFF, 0x7E }, // 0x02
  { 0x0E, 0x1F, 0x3F, 0x7E, 0x3F, 0x1F, 0x0E, 0x00 }, // 0x03
  { 0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08, 0x00 }, // 0x04
  { 0x18, 0xBA, 0xFF, 0xFF, 0xFF, 0xBA, 0x18, 0x00 }, // 0x05
  { 0x10, 0xB8, 0xFC, 0xFF, 0xFC, 0xB8, 0x10, 0x00 }, // 0x06
  { 0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00 }, // 0x07
  { 0xFF, 0xFF, 0xE7, 0xC3, 0xC3, 0xE7, 0xFF, 0xFF }, // 0x08
  { 0x00, 0x3C, 0x66, 0x42, 0x42, 0x66, 0x3C, 0x00 }, // 0x09
  { 0xFF, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0xFF }, // 0x0A
  { 0x70, 0xF8, 0x88, 0x88, 0xFD, 0x7F, 0x07, 0x0F }, // 0x0B
  { 0x00, 0x4E, 0x5F, 0xF1, 0xF1, 0x5F, 0x4E, 0x00 }, // 0x0C
  { 0xC0, 0xE0, 0xFF, 0x7F, 0x05, 0x05, 0x07, 0x07 }, // 0x0D
  { 0xC0, 0xFF, 0x7F, 0x05, 0x05, 0x65, 0x7F, 0x3F }, // 0x0E
  { 0x99, 0x5A, 0x3C, 0xE7, 0xE7, 0x3C, 0x5A, 0x99 }, // 0x0F
  { 0x7F, 0x3E, 0x3E, 0x1C, 0x1C, 0x08, 0x08, 0x00 }, // 0x10
  { 0x08, 0x08, 0x1C, 0x1C, 0x3E, 0x3E, 0x7F, 0x00 }, // 0x11
  { 0x00, 0x24, 0x66, 0xFF, 0xFF, 0x66, 0x24, 0x00 }, // 0x12
  { 0x00, 0x5F, 0x5F, 0x00, 0x00, 0x5F, 0x5F, 0x00 }, // 0x13
  { 0x06, 0x0F, 0x09, 0x7F, 0x7F, 0x01, 0x7F, 0x7F }, // 0x14
  { 0x40, 0xDA, 0xBF, 0xA5, 0xFD, 0x59, 0x03, 0x02 }, // 0x15
  { 0x00, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x00 }, // 0x16
  { 0x80, 0x94, 0xB6, 0xFF, 0xFF, 0xB6, 0x94, 0x80 }, // 0x17
  { 0x00, 0x04, 0x06, 0x7F, 0x7F, 0x06, 0x04, 0x00 }, // 0x18
  { 0x00, 0x10, 0x30, 0x7F, 0x7F, 0x30, 0x10, 0x00 }, // 0x19
  { 0x08, 0x08, 0x08, 0x2A, 0x3E, 0x1C, 0x08, 0x00 }, // 0x1A
  { 0x08, 0x1C, 0x3E, 0x2A, 0x08, 0x08, 0x08, 0x00 }, // 0x1B
  { 0x3C, 0x3C, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00 }, // 0x1C
  { 0x08, 0x1C, 0x3E, 0x08, 0x08, 0x3E, 0x1C, 0x08 }, // 0x1D
  { 0x30, 0x38, 0x3C, 0x3E, 0x3E, 0x3C, 0x38, 0x30 }, // 0x1E
  { 0x06, 0x0E, 0x1E, 0x3E, 0x3E, 0x1E, 0x0E, 0x06 }, // 0x1F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // ' '
  { 0x00, 0x06, 0x5F, 0x5F, 0x06, 0x00, 0x00, 0x00 }, // '!'
  { 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x00 }, // '"'
  { 0x14, 0x7F, 0x7F, 0x14, 0x7F, 0x7F, 0x14, 0x00 }, // '#'
  { 0x24, 0x2E, 0x6B, 0x6B, 0x3A, 0x12, 0x00, 0x00 }, // '$'
  { 0x46, 0x66, 0x30, 0x18, 0x0C, 0x66, 0x62, 0x00 }, // '%'
  { 0x30, 0x7A, 0x4F, 0x5D, 0x37, 0x7A, 0x48, 0x00 }, // '&'
  { 0x04, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 }, // '''
  { 0x00, 0x1C, 0x3E, 0x63, 0x41, 0x00, 0x00, 0x00 }, // '('
  { 0x00, 0x41, 0x63, 0x3E, 0x1C, 0x00, 0x00, 0x00 }, // ')'
  { 0x08, 0x2A, 0x3E, 0x1C, 0x1C, 0x3E, 0x2A, 0x08 }, // '*'
  { 0x08, 0x08, 0x3E, 0x3E, 0x08, 0x08, 0x00, 0x00 }, // '+'
  { 0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00 }, // ','
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00 }, // '-'
  { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00 }, // '.'
  { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00 }, // '/'
  { 0x3C, 0x7E, 0x81, 0x81, 0x7E, 0x3C, 0x00, 0x00 }, // '0' 6x8
  { 0x00, 0x00, 0x82, 0xFF, 0xFF, 0x80, 0x00, 0x00 }, // '1' 6x8
  { 0xC2, 0xE3, 0xB1, 0x99, 0xCF, 0xC6, 0x00, 0x00 }, // '2' 6x8
  { 0x42, 0xC3, 0x99, 0x99, 0xFF, 0x66, 0x00, 0x00 }, // '3' 6x8
  { 0x1C, 0x16, 0x93, 0xFF, 0xFF, 0x90, 0x00, 0x00 }, // '4' 6x8
  { 0x4F, 0xCF, 0x89, 0x89, 0xF9, 0x71, 0x00, 0x00 }, // '5' 6x8
  { 0x7C, 0xFE, 0x8B, 0x89, 0xF9, 0x70, 0x00, 0x00 }, // '6' 6x8
  { 0x03, 0x03, 0xE1, 0xF1, 0x1F, 0x0F, 0x00, 0x00 }, // '7' 6x8
  { 0x76, 0xFF, 0x89, 0x89, 0xFF, 0x76, 0x00, 0x00 }, // '8' 6x8
  { 0x06, 0x8F, 0x89, 0xC9, 0x7F, 0x3E, 0x00, 0x00 }, // '9' 6x8
  { 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00 }, // ':'
  { 0x00, 0x80, 0xE6, 0x66, 0x00, 0x00, 0x00, 0x00 }, // ';'
  { 0x08, 0x1C, 0x36, 0x63, 0x41, 0x00, 0x00, 0x00 }, // '<'
  { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00 }, // '='
  { 0x00, 0x41, 0x63, 0x36, 0x1C, 0x08, 0x00, 0x00 }, // '>'
  { 0x02, 0x03, 0x51, 0x59, 0x0F, 0x06, 0x00, 0x00 }, // '?'
  { 0x3E, 0x7F, 0x41, 0x5D, 0x5D, 0x1F, 0x1E, 0x00 }, // '@' 
  { 0x7C, 0x7E, 0x13, 0x13, 0x7E, 0x7C, 0x00, 0x00 }, // 'A'
  { 0x41, 0x7F, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00 }, // 'B'
  { 0x1C, 0x3E, 0x63, 0x41, 0x41, 0x63, 0x22, 0x00 }, // 'C'
  { 0x41, 0x7F, 0x7F, 0x41, 0x63, 0x3E, 0x1C, 0x00 }, // 'D'
  { 0x41, 0x7F, 0x7F, 0x49, 0x5D, 0x41, 0x63, 0x00 }, // 'E'
  { 0x41, 0x7F, 0x7F, 0x49, 0x1D, 0x01, 0x03, 0x00 }, // 'F'
  { 0x1C, 0x3E, 0x63, 0x41, 0x51, 0x73, 0x72, 0x00 }, // 'G'
  { 0x7F, 0x7F, 0x08, 0x08, 0x7F, 0x7F, 0x00, 0x00 }, // 'H'
  { 0x00, 0x41, 0x7F, 0x7F, 0x41, 0x00, 0x00, 0x00 }, // 'I'
  { 0x30, 0x70, 0x40, 0x41, 0x7F, 0x3F, 0x01, 0x00 }, // 'J'
  { 0x41, 0x7F, 0x7F, 0x08, 0x1C, 0x77, 0x63, 0x00 }, // 'K'
  { 0x41, 0x7F, 0x7F, 0x41, 0x40, 0x60, 0x70, 0x00 }, // 'L'
  { 0x7F, 0x7F, 0x0E, 0x1C, 0x0E, 0x7F, 0x7F, 0x00 }, // 'M'
  { 0x7F, 0x7F, 0x06, 0x0C, 0x18, 0x7F, 0x7F, 0x00 }, // 'N'
  { 0x1C, 0x3E, 0x63, 0x41, 0x63, 0x3E, 0x1C, 0x00 }, // 'O'
  { 0x41, 0x7F, 0x7F, 0x49, 0x09, 0x0F, 0x06, 0x00 }, // 'P'
  { 0x1E, 0x3F, 0x21, 0x71, 0x7F, 0x5E, 0x00, 0x00 }, // 'Q'
  { 0x41, 0x7F, 0x7F, 0x09, 0x19, 0x7F, 0x66, 0x00 }, // 'R'
  { 0x26, 0x6F, 0x4D, 0x59, 0x73, 0x32, 0x00, 0x00 }, // 'S'
  { 0x03, 0x41, 0x7F, 0x7F, 0x41, 0x03, 0x00, 0x00 }, // 'T'
  { 0x7F, 0x7F, 0x40, 0x40, 0x7F, 0x7F, 0x00, 0x00 }, // 'U'
  { 0x1F, 0x3F, 0x60, 0x60, 0x3F, 0x1F, 0x00, 0x00 }, // 'V'
  { 0x7F, 0x7F, 0x30, 0x18, 0x30, 0x7F, 0x7F, 0x00 }, // 'W'
  { 0x43, 0x67, 0x3C, 0x18, 0x3C, 0x67, 0x43, 0x00 }, // 'X'
  { 0x07, 0x4F, 0x78, 0x78, 0x4F, 0x07, 0x00, 0x00 }, // 'Y'
  { 0x47, 0x63, 0x71, 0x59, 0x4D, 0x67, 0x73, 0x00 }, // 'Z'
  { 0x00, 0x7F, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00 }, // '['
  { 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00 }, // backslash
  { 0x00, 0x41, 0x41, 0x7F, 0x7F, 0x00, 0x00, 0x00 }, // ']'
  { 0x08, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x08, 0x00 }, // '^'
  { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 }, // '_'
  { 0x00, 0x00, 0x03, 0x07, 0x04, 0x00, 0x00, 0x00 }, // '`'
  { 0x20, 0x74, 0x54, 0x54, 0x3C, 0x78, 0x40, 0x00 }, // 'a'
  { 0x41, 0x7F, 0x3F, 0x48, 0x48, 0x78, 0x30, 0x00 }, // 'b'
  { 0x38, 0x7C, 0x44, 0x44, 0x6C, 0x28, 0x00, 0x00 }, // 'c'
  { 0x30, 0x78, 0x48, 0x49, 0x3F, 0x7F, 0x40, 0x00 }, // 'd'
  { 0x38, 0x7C, 0x54, 0x54, 0x5C, 0x18, 0x00, 0x00 }, // 'e'
  { 0x48, 0x7E, 0x7F, 0x49, 0x03, 0x02, 0x00, 0x00 }, // 'f'
  { 0x98, 0xBC, 0xA4, 0xA4, 0xF8, 0x7C, 0x04, 0x00 }, // 'g'
  { 0x41, 0x7F, 0x7F, 0x08, 0x04, 0x7C, 0x78, 0x00 }, // 'h'
  { 0x00, 0x44, 0x7D, 0x7D, 0x40, 0x00, 0x00, 0x00 }, // 'i'
  { 0x60, 0xE0, 0x80, 0x80, 0xFD, 0x7D, 0x00, 0x00 }, // 'j'
  { 0x41, 0x7F, 0x7F, 0x10, 0x38, 0x6C, 0x44, 0x00 }, // 'k'
  { 0x00, 0x41, 0x7F, 0x7F, 0x40, 0x00, 0x00, 0x00 }, // 'l'
  { 0x7C, 0x7C, 0x18, 0x38, 0x1C, 0x7C, 0x78, 0x00 }, // 'm'
  { 0x7C, 0x7C, 0x04, 0x04, 0x7C, 0x78, 0x00, 0x00 }, // 'n'
  { 0x38, 0x7C, 0x44, 0x44, 0x7C, 0x38, 0x00, 0x00 }, // 'o'
  { 0x84, 0xFC, 0xF8, 0xA4, 0x24, 0x3C, 0x18, 0x00 }, // 'p'
  { 0x18, 0x3C, 0x24, 0xA4, 0xF8, 0xFC, 0x84, 0x00 }, // 'q'
  { 0x44, 0x7C, 0x78, 0x4C, 0x04, 0x1C, 0x18, 0x00 }, // 'r'
  { 0x48, 0x5C, 0x54, 0x54, 0x74, 0x24, 0x00, 0x00 }, // 's'
  { 0x00, 0x04, 0x3E, 0x7F, 0x44, 0x24, 0x00, 0x00 }, // 't'
  { 0x3C, 0x7C, 0x40, 0x40, 0x3C, 0x7C, 0x40, 0x00 }, // 'u'
  { 0x1C, 0x3C, 0x60, 0x60, 0x3C, 0x1C, 0x00, 0x00 }, // 'v'
  { 0x3C, 0x7C, 0x70, 0x38, 0x70, 0x7C, 0x3C, 0x00 }, // 'w'
  { 0x44, 0x6C, 0x38, 0x10, 0x38, 0x6C, 0x44, 0x00 }, // 'x'
  { 0x9C, 0xBC, 0xA0, 0xA0, 0xFC, 0x7C, 0x00, 0x00 }, // 'y'
  { 0x4C, 0x64, 0x74, 0x5C, 0x4C, 0x64, 0x00, 0x00 }, // 'z'
  { 0x08, 0x08, 0x3E, 0x77, 0x41, 0x41, 0x00, 0x00 }, // '{'
  { 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00 }, // '|'
  { 0x41, 0x41, 0x77, 0x3E, 0x08, 0x08, 0x00, 0x00 }, // '}'
  { 0x02, 0x03, 0x01, 0x03, 0x02, 0x03, 0x01, 0x00 }, // '~'


};  //  end of cp437_font
