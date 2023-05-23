static int font_glyphs[] = {23535,31471,25166,31595,29391,4815,31310,23533,29847,13463,23277,29257,23423,23403,15214,5103,26474,23279,14798,9367,27501,12141,32621,23213,31213,29351};

// Return a bitmap for the glyph corresponding to `c`.
// `c` must be lowercase.
// if `c` is invalid, return 0;
int get_glyph(char c)
{
    if (c > 'z' || c < 'a') return 0;
    return font_glyphs[c - 'a'];
}
