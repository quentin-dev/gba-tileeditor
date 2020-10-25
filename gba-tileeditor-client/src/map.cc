/* map.cc
 * the actual map model which stores the tile information */

#include "map.hh"

#include <QFileInfo>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

#include "json.hpp"

/* construct a new map of a given size, and set to all zeroes */
Map::Map(int width, int height, bool regular)
{
    /* convert pixel sizes into tile sizes */
    this->width = width;
    this->height = height;
    this->regular = regular;
    this->tiles = new int[width * height];

    for (int i = 0; i < width * height; i++)
    {
        tiles[i] = 0;
    }
}

/* access the width of the map (in tiles) */
int Map::get_width()
{
    return width;
}

/* access the width of the map (in tiles) */
int Map::get_height()
{
    return height;
}

/* make a blank map */
Map::Map()
{
    width = 0;
    height = 0;
    regular = true;
    tiles = NULL;
}

/* clear the memory for this map */
Map::~Map()
{
    if (tiles)
    {
        delete[] tiles;
    }

    while (!undo_stack.empty())
    {
        int* tmp = undo_stack.top();
        undo_stack.pop();
        delete[] tmp;
    }

    while (!redo_stack.empty())
    {
        int* tmp = redo_stack.top();
        redo_stack.pop();
        delete[] tmp;
    }
}

/* gets a tile from the map using the complex indexing required
 * must be called until it returns NULL */
int* Map::lookup_tile(int& sb, int& row, int& col, int& above, int& left)
{
    /* if it's an affine background, then we must do them strictly in order */
    if (!regular)
    {
        /* we just go tile by tile */
        if (row == height)
        {
            return NULL;
        }

        /* grab the value */
        int* value = &tiles[row * width + col];

        /* update counters */
        col++;
        if (col == width)
        {
            col = 0;
            row++;
        }

        return value;
    }

    /* count the screen block we have to write */
    int num_sbs = (width * height) / 1024;

    /* check if we are done */
    if (sb == num_sbs)
    {
        return NULL;
    }

    /* get the next one based off of the current indices */
    int realrow = row + 32 * above;
    int realcol = col + 32 * left;

    /* update the column */
    col++;

    /* if the column is out, move to the next row */
    if (col == 32)
    {
        row++;
        col = 0;
    }

    /* if the row is out, move to next screen block */
    if (row == 32)
    {
        /* if we just did the last screen block in a row of screen blocks */
        int last = 0;
        switch (num_sbs)
        {
        case 1:
            last = 1;
            break;
        case 2:
            if (width == 32)
                last = 1;
            else
                last = 0;
            break;
        case 4:
            if (sb == 1 || sb == 3)
                last = 1;
            else
                last = 0;
            break;
        case 16:
            if ((sb + 1) % 4 == 0)
                last = 1;
            else
                last = 0;
            break;
        }

        // TODO: Add default case

        /* if it WAS the last in a row, none are left and one more is above
         * otherwise, one more is to the left */
        if (last)
        {
            left = 0;
            above++;
        }
        else
        {
            left++;
        }

        /* now update to the next block */
        sb++;
        row = 0;
    }

    /* finally return the shit */
    return &tiles[realrow * width + realcol];
}

void Map::write_header(const std::string& filename)
{
    QFileInfo info(filename.c_str());
    std::string name = info.baseName().toStdString();

    std::ofstream header_file(info.path().toStdString() + '/' + name + ".h");

    if (!header_file.is_open())
    {
        std::cerr << "Could not create header file!\n";
        return;
    }

    header_file << "/* Created by GBA Tile Editor\n"
                << (regular ? "Regular" : "Affine") << " map header\n*/\n\n"
                << "#ifndef GBA_TILE_"
                << info.baseName().toUpper().toStdString() << "_H\n"
                << "#define GBA_TILE_"
                << info.baseName().toUpper().toStdString() << "_H\n\n"
                << "#define " << name << "_width " << width << '\n'
                << "#define " << name << "_height " << height << "\n\n"
                << "#define " << name << "_len " << width * height << '\n'
                << "extern const " << (regular ? "short" : "char") << ' '
                << name << '[' << width * height << "];\n";

    header_file << "\n#endif\n";
}

void Map::write_data(const std::string& filename, bool header_only)
{
    QFileInfo info(filename.c_str());
    std::string name(info.baseName().toStdString());

    char file_ending = (header_only) ? 'h' : 'c';

    std::string complete_path(info.path().toStdString() + '/' + name + '.'
                              + file_ending);

    std::ofstream data_file(complete_path);

    if (!data_file.is_open())
    {
        std::cerr << "Could not create data file!\n";
        return;
    }

    data_file << "/* Created by GBA Tile Editor\n"
              << (regular ? "Regular" : "Affine") << " map data\n*/\n\n"
              << "const unsigned " << (regular ? "short" : "char") << ' '
              << name << '[' << width * height << "] = {\n    ";

    /* start line break counter */
    int counter = 0;

    /* start the complex indexing loop operation */
    int sb = 0;
    int above = 0;
    int left = 0;
    int row = 0;
    int col = 0;
    int* tile = nullptr;

    /* grab the next tile we need to write into */
    while ((tile = lookup_tile(sb, row, col, above, left)))
    {
        /* dump it into the file
         * regular backgrounds use 16-bit indices, affine ones use 8-bit ones */
        if (!regular)
        {
            data_file << "0x" << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<unsigned char>(*tile) << ", ";
        }
        else
        {
            data_file << "0x" << std::hex << std::setw(4) << std::setfill('0')
                      << static_cast<unsigned short>(*tile) << ", ";
        }

        counter++;
        if (counter >= 9)
        {
            data_file << "\n    ";
            counter = 0;
        }
    }

    /* write postamble stuff */
    if (counter)
    {
        data_file << '\n';
    }

    data_file << "};\n\n";
}

void Map::to_json(nlohmann::json& json)
{
    std::vector<int> vector_tiles;

    for (int i = 0; i < width * height; ++i)
    {
        vector_tiles.push_back(tiles[i]);
    }

    json = nlohmann::json{
        {"width", width},
        {"height", height},
        {"regular", regular},
        {"tiles", vector_tiles},
    };
}

void Map::to_json_file(const std::string& filename)
{
    QFileInfo info(filename.c_str());
    std::string name(info.baseName().toStdString());

    std::string complete_path(info.path().toStdString() + '/' + name + ".json");

    std::ofstream file(complete_path);
    nlohmann::json json;
    this->to_json(json);

    file << std::setw(4) << json << '\n';
}

bool Map::from_json(nlohmann::json& json)
{
    json.at("width").get_to(this->width);
    json.at("height").get_to(this->height);
    json.at("regular").get_to(this->regular);

    std::vector<int> vector_tiles = json.at("tiles").get<std::vector<int>>();

    this->tiles = new int[width * height];

    for (std::size_t i = 0; i < vector_tiles.size(); ++i)
    {
        tiles[i] = vector_tiles.at(i);
    }

    return true;
}

bool Map::from_json_file(const std::string& filename)
{
    std::ifstream file(filename);

    nlohmann::json json;
    file >> json;

    return this->from_json(json);
}

/* write this map into a file */
void Map::write(const std::string& filename)
{
    this->to_json_file(filename);
    write_header(filename);
    write_data(filename);
}

/* modify the tile */
void Map::set_tile(int index, int tile_no)
{
    /* save state */
    int* temp = new int[width * height];
    for (int i = 0; i < width * height; i++)
    {
        temp[i] = tiles[i];
    }
    undo_stack.push(temp);

    /* and make the change */
    tiles[index] = tile_no;
}

/* get a pixmap from this Map which can be shown in a QT view */
QPixmap Map::get_pixmap(QImage* tile_image, bool grid_mode, QColor grid_color)
{
    /* create an image which we can draw into */
    QImage image(width * 8, height * 8, QImage::Format_RGB555);

    /* for each tile in the map */
    for (int col = 0; col < width; col++)
    {
        for (int row = 0; row < height; row++)
        {
            /* get the tile number we want */
            int tileno = tiles[row * width + col];

            /* get the x, y position of this tile in the tile image
             * these represent the upper left hand corner of the tile */
            int tilex = (tileno * 8) % (tile_image->width());
            int tiley = ((tileno * 8) / (tile_image->width())) * 8;

            /* get the x, y position of this tile in the map image
             * ditto for upper left corner */
            int mapx = col * 8;
            int mapy = row * 8;

            /* now we will blit the whole tile manually */
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    QRgb color = tile_image->pixel(tilex + i, tiley + j);
                    image.setPixel(mapx + i, mapy + j, color);
                }
            }
        }
    }

    /* draw the grid, if needed */
    if (grid_mode)
    {
        /* for each row 7 of a tile */
        for (int i = 7; i < image.height(); i += 8)
        {
            /* for each column */
            for (int j = 0; j < image.width(); j++)
            {
                image.setPixel(j, i, grid_color.rgba());
            }
        }

        /* for each column 7 of a tile */
        for (int i = 7; i < image.width(); i += 8)
        {
            /* for each column */
            for (int j = 0; j < image.height(); j++)
            {
                image.setPixel(i, j, grid_color.rgba());
            }
        }
    }

    /* return a pixmap out of this image */
    return QPixmap::fromImage(image);
}

/* undo the last move made */
void Map::undo()
{
    if (undo_stack.empty())
    {
        return;
    }
    nlohmann::json j;

    this->to_json(j);
    std::cout << j << '\n';
    /* pop off the last one */
    int* restore = undo_stack.top();
    undo_stack.pop();

    /* replace tiles with it */
    int* current = tiles;
    tiles = restore;

    /* push this onto redo stack */
    redo_stack.push(current);
}

/* redo the last move made */
void Map::redo()
{
    if (redo_stack.empty())
    {
        return;
    }

    /* pop off the last one */
    int* restore = redo_stack.top();
    redo_stack.pop();

    /* replace tiles with it */
    int* current = tiles;
    tiles = restore;

    /* push this onto redo stack */
    undo_stack.push(current);
}
