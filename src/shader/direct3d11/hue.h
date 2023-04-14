// zlib License
//
// copyright (C) 2023 Guoxiaomi and Krimiston
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions:
//
// cbuffer $Globals
// {
//
//   float4 k;                          // Offset:    0 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// samplerState                      sampler      NA          NA             s0      1
// shaderTexture                     texture  float4          2d             t0      1
// $Globals                          cbuffer      NA          NA            cb0      1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float
// TEXCOORD                 0   xy          1     NONE   float   xy
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[1], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d(float, float, float, float) t0
dcl_input_ps linear v1.xy
dcl_output o0.xyzw
dcl_temps 1
sample_indexable(texture2d)(float, float, float, float) r0.xyzw, v1.xyxx, t0.xyzw, s0
dp3 o0.x, r0.xyzx, cb0[0].xyzx
dp3 o0.y, r0.yzxy, cb0[0].xyzx
dp3 o0.z, r0.zxyz, cb0[0].xyzx
mov o0.w, r0.w
ret
// Approximately 6 instruction slots used
#endif

extern constexpr unsigned char rgm_shader_hue_data[] = {
    68,  88,  66,  67,  141, 110, 219, 211, 236, 38,  90,  222, 179, 206, 57,
    146, 63,  199, 40,  135, 1,   0,   0,   0,   192, 3,   0,   0,   5,   0,
    0,   0,   52,  0,   0,   0,   148, 1,   0,   0,   236, 1,   0,   0,   32,
    2,   0,   0,   36,  3,   0,   0,   82,  68,  69,  70,  88,  1,   0,   0,
    1,   0,   0,   0,   192, 0,   0,   0,   3,   0,   0,   0,   60,  0,   0,
    0,   0,   5,   255, 255, 0,   129, 0,   0,   48,  1,   0,   0,   82,  68,
    49,  49,  60,  0,   0,   0,   24,  0,   0,   0,   32,  0,   0,   0,   40,
    0,   0,   0,   36,  0,   0,   0,   12,  0,   0,   0,   0,   0,   0,   0,
    156, 0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,
    0,   0,   169, 0,   0,   0,   2,   0,   0,   0,   5,   0,   0,   0,   4,
    0,   0,   0,   255, 255, 255, 255, 0,   0,   0,   0,   1,   0,   0,   0,
    12,  0,   0,   0,   183, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   115, 97,  109, 112, 108, 101, 114, 83,  116,
    97,  116, 101, 0,   115, 104, 97,  100, 101, 114, 84,  101, 120, 116, 117,
    114, 101, 0,   36,  71,  108, 111, 98,  97,  108, 115, 0,   183, 0,   0,
    0,   1,   0,   0,   0,   216, 0,   0,   0,   16,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   16,
    0,   0,   0,   2,   0,   0,   0,   12,  1,   0,   0,   0,   0,   0,   0,
    255, 255, 255, 255, 0,   0,   0,   0,   255, 255, 255, 255, 0,   0,   0,
    0,   107, 0,   102, 108, 111, 97,  116, 52,  0,   171, 171, 171, 1,   0,
    3,   0,   1,   0,   4,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    2,   1,   0,   0,   77,  105, 99,  114, 111, 115, 111, 102, 116, 32,  40,
    82,  41,  32,  72,  76,  83,  76,  32,  83,  104, 97,  100, 101, 114, 32,
    67,  111, 109, 112, 105, 108, 101, 114, 32,  49,  48,  46,  49,  0,   73,
    83,  71,  78,  80,  0,   0,   0,   2,   0,   0,   0,   8,   0,   0,   0,
    56,  0,   0,   0,   0,   0,   0,   0,   1,   0,   0,   0,   3,   0,   0,
    0,   0,   0,   0,   0,   15,  0,   0,   0,   68,  0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   1,   0,   0,   0,   3,
    3,   0,   0,   83,  86,  95,  80,  79,  83,  73,  84,  73,  79,  78,  0,
    84,  69,  88,  67,  79,  79,  82,  68,  0,   171, 171, 171, 79,  83,  71,
    78,  44,  0,   0,   0,   1,   0,   0,   0,   8,   0,   0,   0,   32,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   0,   0,   0,   0,
    0,   0,   0,   15,  0,   0,   0,   83,  86,  95,  84,  65,  82,  71,  69,
    84,  0,   171, 171, 83,  72,  69,  88,  252, 0,   0,   0,   80,  0,   0,
    0,   63,  0,   0,   0,   106, 8,   0,   1,   89,  0,   0,   4,   70,  142,
    32,  0,   0,   0,   0,   0,   1,   0,   0,   0,   90,  0,   0,   3,   0,
    96,  16,  0,   0,   0,   0,   0,   88,  24,  0,   4,   0,   112, 16,  0,
    0,   0,   0,   0,   85,  85,  0,   0,   98,  16,  0,   3,   50,  16,  16,
    0,   1,   0,   0,   0,   101, 0,   0,   3,   242, 32,  16,  0,   0,   0,
    0,   0,   104, 0,   0,   2,   1,   0,   0,   0,   69,  0,   0,   139, 194,
    0,   0,   128, 67,  85,  21,  0,   242, 0,   16,  0,   0,   0,   0,   0,
    70,  16,  16,  0,   1,   0,   0,   0,   70,  126, 16,  0,   0,   0,   0,
    0,   0,   96,  16,  0,   0,   0,   0,   0,   16,  0,   0,   8,   18,  32,
    16,  0,   0,   0,   0,   0,   70,  2,   16,  0,   0,   0,   0,   0,   70,
    130, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   16,  0,   0,   8,
    34,  32,  16,  0,   0,   0,   0,   0,   150, 4,   16,  0,   0,   0,   0,
    0,   70,  130, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,   16,  0,
    0,   8,   66,  32,  16,  0,   0,   0,   0,   0,   38,  9,   16,  0,   0,
    0,   0,   0,   70,  130, 32,  0,   0,   0,   0,   0,   0,   0,   0,   0,
    54,  0,   0,   5,   130, 32,  16,  0,   0,   0,   0,   0,   58,  0,   16,
    0,   0,   0,   0,   0,   62,  0,   0,   1,   83,  84,  65,  84,  148, 0,
    0,   0,   6,   0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   2,
    0,   0,   0,   3,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
