#ifndef ICONS_H
#define ICONS_H

#include <SDL2/SDL.h>

Uint8 icons[][8] = {
    {0x00, 0x00, 0x10, 0x38, 0x7c, 0x38, 0x10, 0x00}, /* play */
    {0x00, 0x00, 0x48, 0x24, 0x12, 0x24, 0x48, 0x00}, /* next */
    {0x00, 0x00, 0x66, 0x42, 0x00, 0x42, 0x66, 0x00}, /* skip */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00}, /* midi:1 */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x3e, 0x00}, /* midi:2 */
    {0x00, 0x00, 0x00, 0x00, 0x3e, 0x3e, 0x3e, 0x00}, /* midi:3 */
    {0x00, 0x00, 0x00, 0x3e, 0x3e, 0x3e, 0x3e, 0x00}, /* midi:4 */
    {0x00, 0x00, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x00}, /* midi:5 */
    {0x00, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x00}, /* midi:6 */
    {0x00, 0x00, 0x00, 0x82, 0x44, 0x38, 0x00, 0x00}, /* eye open */
    {0x00, 0x38, 0x44, 0x92, 0x28, 0x10, 0x00, 0x00}, /* eye closed */
    {0x10, 0x54, 0x28, 0xc6, 0x28, 0x54, 0x10, 0x00}  /* unsaved */
};

#endif // !ICONS_H
