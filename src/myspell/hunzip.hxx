/* hunzip: file decompression for sorted dictionaries with optional encryption,
 * algorithm: prefix-suffix encoding and 16-bit Huffman encoding */

#ifndef _HUNZIP_HXX_
#define _HUNZIP_HXX_

#define BUFSIZE  65536
#define HZIP_EXTENSION ".hz"

#define MSG_OPEN   "error: %s: cannot open\n"
#define MSG_FORMAT "error: %s: not in hzip format\n"
#define MSG_MEMORY "error: %s: missing memory\n"
#define MSG_KEY    "error: %s: missing or bad password\n"

#include <stdio.h>

struct bit {
    unsigned char c[2];
    int v[2];
};

class Hunzip
{

protected:
    char * filename;
    FILE * fin;
    int bufsiz, lastbit, inc, inbits, outc;
    struct bit * dec;        // code table
    char in[BUFSIZE];        // input buffer
    char out[BUFSIZE + 1];   // Huffman-decoded buffer
    char line[BUFSIZE + 50]; // decoded line
    int getcode(const char * key);
    int getbuf();
    int fail(const char * err, const char * par);
    
public:   
    Hunzip(const char * filename, const char * key = NULL);
    ~Hunzip();
    const char * getline();
};

#endif
