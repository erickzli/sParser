//
//  parser.hh
//
//  Created by Erick Li on 04/11/19.
//  Copyright © 2019 Erick Li. All rights reserved.
//

#ifndef __PARSER__
#define __PARSER__

#include "parser_helper.hh"
#include "fill_parser.hh"
#include "line_parser.hh"
#include "marker_parser.hh"
#include "json_writer.hh"

#include <stdlib.h>
#include <unistd.h>

const bool PRINT_TO_FILE = true;
const bool DO_REWIND = true;

const int USE_RGB = 0;
const int USE_HSV = 1;

/**
 * Entry of the module
 * \param a pointer pointing to the first bytes of the memory block.
 * \param a pointer pointing to the last byte of the memory block
 * WARNING: The input source MUST have an extra byte at the end of the block, and the num_of_bytes MUST include that byte.
 *          Otherwise, undefined behavior may occur.
 * \param opton to if logging should be enabled.
 * \return the jstring
 *
 *  *cursor        *tail
 *     \             \
 *     |0|1|2|3|4|5|6|7|
 */
std::string grandParser(char *head, char *tail, bool enableLogging);


/**
 * Parses the binary block where it defines a color pattern
 * \param the input file stream.
 * \param the output file stream.
 * \param color type, such as, "outline color", etc.
 * \param the level(indention).
 * References: 1. ArcGIS uses CIELAB to represent RGB and HSV color.
               https://support.esri.com/en/technical-article/000002092
 *             2. The conversion to RGB/HSV is based on the knowledge from the websites:
               https://www.cs.rit.edu/~ncs/color/t_convert.html#XYZ%20to%20CIE%20L*a*b*%20(CIELAB)%20&%20CIELAB%20to%20XYZ
 */
int parseColorPattern(char **cursor, std::string &jstring, std::string color_type, int level);

/**
 * Parses out layer number.
 * \param the input file stream.
 * \param the output file stream.
 * \param the level(indention).
 * \return:
 *    val > 0: the number of layers
 *    val == -1: something wrong...
 */
int parseLayerNumber(char **cursor, std::string &jstring, int level);

/**
 * Parser the binary block where it defines a double value
 * \param the input file stream.
 * \param the output file stream.
 * \param the name of the double value.
 * \param the level(indention)
 */
double parseDouble(char **cursor, std::string &jstring, std::string tag, int level);

/**
 * Parser the binary block where it defines an integer value
 * \param the input file stream.
 * \param the output file stream.
 * \param the name of the double value.
 * \param the level(indention)
 */
int parseInt(char **cursor, std::string &jstring, std::string tag, int level);

/**
 * Parser the binary block where it defines a string (font name)
 * \param the input file stream.
 * \param the output file stream.
 * \param the name of the double value.
 * \param the level(indention)
 */
int parseString(char **cursor, std::string &jstring, std::string tag, int level);

/**
 * Parser the TEMPLATE pattern.
 *     TEMPLATE is for line feature which defines dot repeats.
 *     interval length -> line length -> gap length.
 * \param the input file stream.
 * \param the output file stream.
 * \param type type of template feed (0: hash/carto line; 1: marker line)
 * \param the level(indention)
 */
int parseTemplate(char **cursor, std::string &jstring, int type, int level);

#endif
