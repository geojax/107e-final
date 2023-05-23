// picofont.h

// Return a bitmap for the glyph corresponding to `c`.
// Least significant bit in returned value corresponds to
// top-left, most significant to bottom left. For example,
// 'a' is 0b101101111101111. Arrange this so that every 3 bits
// has its own row with the last 3 bits on top:
// 111
// 101
// 111
// 101
// 101
// `c` must be lowercase.
// if `c` is invalid, return 0;
int get_glyph(char c);
