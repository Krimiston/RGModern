// zlib License

// Copyright (C) [2023] [Xiaomi Guo]

// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.

// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:

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
// Parameters:
//
//   Texture2D samplerState+shaderTexture;
//   float4 tone;
//
//
// Registers:
//
//   Name                       Reg   Size
//   -------------------------- ----- ----
//   tone                       c0       1
//   samplerState+shaderTexture s0       1
//

    ps_2_x
    def c1, 0.298999995, 0.587000012, 0.114, 0
    dcl t0.xy
    dcl_2d s0
    texld r0, t0, s0
    dp3 r1.w, r0, c1
    lrp r2.xyz, c0.w, r1.w, r0
    add r0.xyz, r2, c0
    mov oC0, r0

// approximately 5 instruction slots used (1 texture, 4 arithmetic)
#endif

extern constexpr unsigned char rgm_shader_tone_dx9_data[] = {
    1,   2,   255, 255, 254, 255, 47,  0,   67,  84,  65,  66,  28,  0,   0,
    0,   143, 0,   0,   0,   1,   2,   255, 255, 2,   0,   0,   0,   28,  0,
    0,   0,   0,   129, 0,   0,   136, 0,   0,   0,   68,  0,   0,   0,   3,
    0,   0,   0,   1,   0,   0,   0,   96,  0,   0,   0,   0,   0,   0,   0,
    112, 0,   0,   0,   2,   0,   0,   0,   1,   0,   0,   0,   120, 0,   0,
    0,   0,   0,   0,   0,   115, 97,  109, 112, 108, 101, 114, 83,  116, 97,
    116, 101, 43,  115, 104, 97,  100, 101, 114, 84,  101, 120, 116, 117, 114,
    101, 0,   171, 4,   0,   7,   0,   1,   0,   4,   0,   1,   0,   0,   0,
    0,   0,   0,   0,   116, 111, 110, 101, 0,   171, 171, 171, 1,   0,   3,
    0,   1,   0,   4,   0,   1,   0,   0,   0,   0,   0,   0,   0,   112, 115,
    95,  50,  95,  97,  0,   77,  105, 99,  114, 111, 115, 111, 102, 116, 32,
    40,  82,  41,  32,  72,  76,  83,  76,  32,  83,  104, 97,  100, 101, 114,
    32,  67,  111, 109, 112, 105, 108, 101, 114, 32,  49,  48,  46,  49,  0,
    171, 81,  0,   0,   5,   1,   0,   15,  160, 135, 22,  153, 62,  162, 69,
    22,  63,  213, 120, 233, 61,  0,   0,   0,   0,   31,  0,   0,   2,   0,
    0,   0,   128, 0,   0,   3,   176, 31,  0,   0,   2,   0,   0,   0,   144,
    0,   8,   15,  160, 66,  0,   0,   3,   0,   0,   15,  128, 0,   0,   228,
    176, 0,   8,   228, 160, 8,   0,   0,   3,   1,   0,   8,   128, 0,   0,
    228, 128, 1,   0,   228, 160, 18,  0,   0,   4,   2,   0,   7,   128, 0,
    0,   255, 160, 1,   0,   255, 128, 0,   0,   228, 128, 2,   0,   0,   3,
    0,   0,   7,   128, 2,   0,   228, 128, 0,   0,   228, 160, 1,   0,   0,
    2,   0,   8,   15,  128, 0,   0,   228, 128, 255, 255, 0,   0};
