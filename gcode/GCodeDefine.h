#ifndef GCODE_DEFINE_H
#define GCODE_DEFINE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum GMID {
  M02,        //0
  G00,        //1
  G01,        //2
  G02,        //3
  G03,        //4
  G04,        //5
  G92,        //6
  G40,        //7
  G41,        //8
  G42,        //9
  G20,        //10
  G21,        //11
  G90,        //12
  G91,        //13
  G99,        //14
  G26,        //15
  G27,        //16
  G28,        //17
  G22,        //18
  G80,        //19
  M00,        //20
  M30,        //21
  M07,        //22
  M08,        //23
  M09,        //24
  M10,        //25
  M11,        //26
  M12,        //27
  M50,        //28
  M52,        //29
  M80,        //30
  G62,
  G63,
  G64,
  GGG,        // unrecognized
  G43,        // kerf value
  G59,        // kerf table
  M51,
  M61,
  M90,        // laser: layer start
  M91,        // laser: layer end
  M92,        // laser: loop start
  M93,        // laser: loop end
  M94,        // laser: file start
  M95,        // laser: file end
  M200,       // laser: user custom cmd
  NCODE,
};

enum M10_M21 {
  M42 = 110,
  M43,
  M44,
  M45,
  M14,
  M15,
  M16,
  M17,
  M18,
  M19,
  M20,
  M21,
  M22,
  M23,
  M24,
  M25,
  M26,
  M27,
  M28,
  M29,
  M46,
  M47,
  M32,
  M33,
  M34,
  M35,
  M36,
  M37,
  M38,
  M39,
  M40,
  M41,
  M48,
  M60,
  M62,
  M63,
  M64,
  M65,
  M81,
  M82,
  I28,
  I29
};

typedef enum __GCodeResultType
{
  GCodeOK = 0,
  GCodeErr,
  GCodeLarge,
  GCodePostionErr,
  GCodeArcErr,
  GCodeArcRadiusSmall,
  GCodeArcCenterErr,
  GCodeFullCircleErr,
  GCodeKerfCutOffErr,
  GCodeArcCalibrateErr,
  GCodeKerfErr,
  GCodeInvalidFile,
  GCodeSyntaxErr

} GCodeResult;

#ifdef __cplusplus
}
#endif

#endif
