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
// Parameters:
//
//   float4 k;
//   Texture2D samplerState+shaderTexture;
//
//
// Registers:
//
//   Name                       Reg   Size
//   -------------------------- ----- ----
//   k                          c0       1
//   samplerState+shaderTexture s0       1
//

    ps_2_x
    dcl t0.xy
    dcl_2d s0
    texld r0, t0, s0
    dp3 r1.x, r0, c0
    dp3 r1.y, r0.yzxw, c0
    dp3 r1.z, r0.zxyw, c0
    mov r1.w, r0.w
    mov oC0, r1

// approximately 6 instruction slots used (1 texture, 5 arithmetic)
#endif

extern constexpr unsigned char rgm_shader_hue_dx9_data[] = {
    1,   2,   255, 255, 254, 255, 46,  0,   67,  84,  65,  66,  28,  0,   0,
    0,   139, 0,   0,   0,   1,   2,   255, 255, 2,   0,   0,   0,   28,  0,
    0,   0,   0,   129, 0,   0,   132, 0,   0,   0,   68,  0,   0,   0,   2,
    0,   0,   0,   1,   0,   0,   0,   72,  0,   0,   0,   0,   0,   0,   0,
    88,  0,   0,   0,   3,   0,   0,   0,   1,   0,   0,   0,   116, 0,   0,
    0,   0,   0,   0,   0,   107, 0,   171, 171, 1,   0,   3,   0,   1,   0,
    4,   0,   1,   0,   0,   0,   0,   0,   0,   0,   115, 97,  109, 112, 108,
    101, 114, 83,  116, 97,  116, 101, 43,  115, 104, 97,  100, 101, 114, 84,
    101, 120, 116, 117, 114, 101, 0,   171, 4,   0,   7,   0,   1,   0,   4,
    0,   1,   0,   0,   0,   0,   0,   0,   0,   112, 115, 95,  50,  95,  97,
    0,   77,  105, 99,  114, 111, 115, 111, 102, 116, 32,  40,  82,  41,  32,
    72,  76,  83,  76,  32,  83,  104, 97,  100, 101, 114, 32,  67,  111, 109,
    112, 105, 108, 101, 114, 32,  49,  48,  46,  49,  0,   171, 31,  0,   0,
    2,   0,   0,   0,   128, 0,   0,   3,   176, 31,  0,   0,   2,   0,   0,
    0,   144, 0,   8,   15,  160, 66,  0,   0,   3,   0,   0,   15,  128, 0,
    0,   228, 176, 0,   8,   228, 160, 8,   0,   0,   3,   1,   0,   1,   128,
    0,   0,   228, 128, 0,   0,   228, 160, 8,   0,   0,   3,   1,   0,   2,
    128, 0,   0,   201, 128, 0,   0,   228, 160, 8,   0,   0,   3,   1,   0,
    4,   128, 0,   0,   210, 128, 0,   0,   228, 160, 1,   0,   0,   2,   1,
    0,   8,   128, 0,   0,   255, 128, 1,   0,   0,   2,   0,   8,   15,  128,
    1,   0,   228, 128, 255, 255, 0,   0};
