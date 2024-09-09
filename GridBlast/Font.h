#ifndef FONT_H
#define FONT_H

#include "Resource.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <glm/glm.hpp>

// Structure to hold font glyph information
struct Glyph {
    unsigned int TextureID;  // ID of the texture holding the glyph
    glm::ivec2 Size;         // Size of glyph
    glm::ivec2 Bearing;      // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class Font : public Resource {
public:
    Font(const std::string& id, const std::string& fontPath, unsigned int fontSize = 256);
    ~Font() override;

    // Override the pure virtual Load function from Resource
    bool Load() override;

    // Set the font size and load new glyphs if necessary
    void SetFontSize(unsigned int fontSize);

    // Get glyph map for the current font size
    const std::map<char, Glyph>& GetGlyphs() const;

private:
    std::string fontPath;
    unsigned int currentFontSize;  // Track the current size of the font
    std::map<unsigned int, std::map<char, Glyph>> sizeGlyphs;  // Cache glyphs per font size

    // Helper to load glyphs for a specific font size
    void loadFontGlyphs(FT_Face face, unsigned int fontSize);
};

#endif // FONT_H
