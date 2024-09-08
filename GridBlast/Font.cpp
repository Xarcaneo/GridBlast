#include "Font.h"
#include <GL/glew.h>
#include <iostream>

Font::Font(const std::string& id, const std::string& fontPath, unsigned int fontSize)
    : Resource(id), fontPath(fontPath), currentFontSize(fontSize) {
    Load();  // Load the initial font size
}

Font::~Font() {
    // Clean up textures for all cached glyphs
    for (auto& sizePair : sizeGlyphs) {
        for (auto& pair : sizePair.second) {
            glDeleteTextures(1, &pair.second.TextureID);
        }
    }
}

bool Font::Load() {
    // Check if glyphs for this font size are already cached
    if (sizeGlyphs.find(currentFontSize) != sizeGlyphs.end()) {
        return true;  // Font size is already loaded
    }

    // Initialize FreeType
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    // Load the font face
    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }

    // Set font size
    FT_Set_Pixel_Sizes(face, 0, currentFontSize);

    // Load glyphs and store them in the cache
    loadFontGlyphs(face, currentFontSize);

    // Cleanup FreeType
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

void Font::SetFontSize(unsigned int fontSize) {
    // If the requested size is different, update the size and reload the glyphs
    if (fontSize != currentFontSize) {
        currentFontSize = fontSize;
        Load();  // Load glyphs for the new font size
    }
}

void Font::loadFontGlyphs(FT_Face face, unsigned int fontSize) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Disable byte-alignment restriction

    std::map<char, Glyph> glyphMap;  // Temporary map to store glyphs for this size

    for (unsigned char c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture options to use nearest-neighbor filtering for sharp fonts
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Sharp scaling when minified
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // Sharp scaling when magnified

        // Store glyph information
        Glyph glyph = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        glyphMap.insert(std::pair<char, Glyph>(c, glyph));
    }

    // Store the glyph map for this size
    sizeGlyphs[fontSize] = glyphMap;
}

const std::map<char, Glyph>& Font::GetGlyphs() const {
    // Ensure the glyphs for the current font size exist before returning them
    auto it = sizeGlyphs.find(currentFontSize);
    if (it != sizeGlyphs.end()) {
        return it->second;
    }
    else {
        // Handle the case where the glyphs for currentFontSize are not loaded
        throw std::runtime_error("Glyphs for the requested font size are not loaded.");
    }
}
