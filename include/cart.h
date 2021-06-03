#ifndef CNES_CART_H
#define CNES_CART_H

#include "nes.h"

#define PRGROM_BLOCK_SZ 0x4000
#define CHRROM_BLOCK_SZ 0x2000
#define TRAINER_SZ      0x200

// iNES file format information from NESdev wiki
// https://wiki.nesdev.com/w/index.php/INES
struct cart {
  struct {
    u8 magic[4];   // iNES header, should be exactly "NES\x1a"
    u8 prgrom_n;   // Number of 16K PRG ROMs
    u8 chrrom_n;   // Number of 8K CHR ROMs
    u8 flags6;     // Mapper, mirroring, battery, trainer
    u8 flags7;     // Mapper, VS/Playchoice, NES 2.0
    u8 flags8;     // PRG-RAM size (rarely used extension)
    u8 flags9;     // TV system (rarely used extension)
    u8 flags10;    // TV system, PRG-RAM presence (rarely used extension)
    u8 padding[5]; // Extra padding so the header is 16 bytes
  } header;

  // TODO: Maybe clean this stuff up in the future
  u8 mapper;       // Mapper number this cart uses
  u8 *prg_rom;     // PRG ROM, the meat of the ROM
  FILE *cart_f;    // FILE pointer for cart file
};

void cart_init(struct cart *cart, char *cart_fn);
void cart_destroy(struct cart *cart);
u8 get_mapper(struct cart *cart);
#endif  // CNES_CART_H
