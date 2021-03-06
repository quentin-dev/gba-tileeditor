/* map.hh
 * the actual map model which stores the tile information */

#ifndef MAP_HH
#define MAP_HH

#include <QImage>
#include <QPixmap>
#include <stack>
#include <string>

#include "json.hpp"

class Map
{
private:
    /* width and height measured in tiles */
    int width, height;
    int* tiles;

    /* whether this is a regular map (if not it's affine) */
    bool regular;

    /* undo and redo stacks store the tile information */
    std::stack<int*> undo_stack;
    std::stack<int*> redo_stack;

    /* do the tile lookup in the order that the GBA requires */
    int* lookup_tile(int& sb, int& row, int& col, int& above, int& left);

    void write_header(const std::string& filename);

    void to_json(nlohmann::json& json);
    bool from_json(nlohmann::json& json);

public:
    Map(int width, int height, bool regular);
    Map();
    ~Map();

    /* get a pixmap of what this map will look like when rendered */
    QPixmap get_pixmap(QImage* tiles, bool grid_mode, QColor grid_color);

    /* load/save the map from/to a file */
    void write(const std::string& filename);
    void write_data(const std::string& filename, bool header_only = false);

    /* set a tile in the map to a new value */
    void set_tile(int index, int tile_no);

    bool from_json_file(const std::string& filename);
    void to_json_file(const std::string& filename);

    /* get the dimensions */
    int get_width();
    int get_height();

    /* undo or redo last operation */
    void undo();
    void redo();
};

#endif
