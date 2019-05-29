"//\n"
"//   Copyright 2013 Pixar\n"
"//\n"
"//   Licensed under the Apache License, Version 2.0 (the \"Apache License\")\n"
"//   with the following modification; you may not use this file except in\n"
"//   compliance with the Apache License and the following modification to it:\n"
"//   Section 6. Trademarks. is deleted and replaced with:\n"
"//\n"
"//   6. Trademarks. This License does not grant permission to use the trade\n"
"//      names, trademarks, service marks, or product names of the Licensor\n"
"//      and its affiliates, except as required to comply with Section 4(c) of\n"
"//      the License and to reproduce the content of the NOTICE file.\n"
"//\n"
"//   You may obtain a copy of the Apache License at\n"
"//\n"
"//       http://www.apache.org/licenses/LICENSE-2.0\n"
"//\n"
"//   Unless required by applicable law or agreed to in writing, software\n"
"//   distributed under the Apache License with the above modification is\n"
"//   distributed on an \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY\n"
"//   KIND, either express or implied. See the Apache License for the specific\n"
"//   language governing permissions and limitations under the Apache License.\n"
"//\n"
"\n"
"//----------------------------------------------------------\n"
"// Patches.VertexGregory\n"
"//----------------------------------------------------------\n"
"#ifdef OSD_PATCH_VERTEX_GREGORY_SHADER\n"
"\n"
"layout (location=0) in vec4 position;\n"
"OSD_USER_VARYING_ATTRIBUTE_DECLARE\n"
"\n"
"out block {\n"
"    OsdPerVertexGregory v;\n"
"    OSD_USER_VARYING_DECLARE\n"
"} outpt;\n"
"\n"
"void main()\n"
"{\n"
"    OsdComputePerVertexGregory(gl_VertexID, position.xyz, outpt.v);\n"
"    OSD_PATCH_CULL_COMPUTE_CLIPFLAGS(position);\n"
"    OSD_USER_VARYING_PER_VERTEX();\n"
"}\n"
"\n"
"#endif\n"
"\n"
"//----------------------------------------------------------\n"
"// Patches.TessControlGregory\n"
"//----------------------------------------------------------\n"
"#ifdef OSD_PATCH_TESS_CONTROL_GREGORY_SHADER\n"
"\n"
"in block {\n"
"    OsdPerVertexGregory v;\n"
"    OSD_USER_VARYING_DECLARE\n"
"} inpt[];\n"
"\n"
"out block {\n"
"    OsdPerPatchVertexGregory v;\n"
"    OSD_USER_VARYING_DECLARE\n"
"} outpt[4];\n"
"\n"
"layout(vertices = 4) out;\n"
"\n"
"void main()\n"
"{\n"
"    OsdPerVertexGregory cv[4];\n"
"    for (int i=0; i<4; ++i) {\n"
"        cv[i] = inpt[i].v;\n"
"    }\n"
"\n"
"    ivec3 patchParam = OsdGetPatchParam(OsdGetPatchIndex(gl_PrimitiveID));\n"
"    OsdComputePerPatchVertexGregory(patchParam, gl_InvocationID, gl_PrimitiveID, cv, outpt[gl_InvocationID].v);\n"
"\n"
"    OSD_USER_VARYING_PER_CONTROL_POINT(gl_InvocationID, gl_InvocationID);\n"
"\n"
"    if (gl_InvocationID == 0) {\n"
"        vec4 tessLevelOuter = vec4(0);\n"
"        vec2 tessLevelInner = vec2(0);\n"
"\n"
"        OSD_PATCH_CULL(4);\n"
"\n"
"        OsdGetTessLevels(cv[0].P, cv[3].P, cv[2].P, cv[1].P,\n"
"                         patchParam, tessLevelOuter, tessLevelInner);\n"
"\n"
"        gl_TessLevelOuter[0] = tessLevelOuter[0];\n"
"        gl_TessLevelOuter[1] = tessLevelOuter[1];\n"
"        gl_TessLevelOuter[2] = tessLevelOuter[2];\n"
"        gl_TessLevelOuter[3] = tessLevelOuter[3];\n"
"\n"
"        gl_TessLevelInner[0] = tessLevelInner[0];\n"
"        gl_TessLevelInner[1] = tessLevelInner[1];\n"
"    }\n"
"}\n"
"\n"
"#endif\n"
"\n"
"//----------------------------------------------------------\n"
"// Patches.TessEvalGregory\n"
"//----------------------------------------------------------\n"
"#ifdef OSD_PATCH_TESS_EVAL_GREGORY_SHADER\n"
"\n"
"layout(quads) in;\n"
"layout(OSD_SPACING) in;\n"
"\n"
"in block {\n"
"    OsdPerPatchVertexGregory v;\n"
"    OSD_USER_VARYING_DECLARE\n"
"} inpt[];\n"
"\n"
"out block {\n"
"    OutputVertex v;\n"
"    OSD_USER_VARYING_DECLARE\n"
"} outpt;\n"
"\n"
"void main()\n"
"{\n"
"    vec3 P = vec3(0), dPu = vec3(0), dPv = vec3(0);\n"
"    vec3 N = vec3(0), dNu = vec3(0), dNv = vec3(0);\n"
"\n"
"    vec3 cv[20];\n"
"    cv[0] = inpt[0].v.P;\n"
"    cv[1] = inpt[0].v.Ep;\n"
"    cv[2] = inpt[0].v.Em;\n"
"    cv[3] = inpt[0].v.Fp;\n"
"    cv[4] = inpt[0].v.Fm;\n"
"\n"
"    cv[5] = inpt[1].v.P;\n"
"    cv[6] = inpt[1].v.Ep;\n"
"    cv[7] = inpt[1].v.Em;\n"
"    cv[8] = inpt[1].v.Fp;\n"
"    cv[9] = inpt[1].v.Fm;\n"
"\n"
"    cv[10] = inpt[2].v.P;\n"
"    cv[11] = inpt[2].v.Ep;\n"
"    cv[12] = inpt[2].v.Em;\n"
"    cv[13] = inpt[2].v.Fp;\n"
"    cv[14] = inpt[2].v.Fm;\n"
"\n"
"    cv[15] = inpt[3].v.P;\n"
"    cv[16] = inpt[3].v.Ep;\n"
"    cv[17] = inpt[3].v.Em;\n"
"    cv[18] = inpt[3].v.Fp;\n"
"    cv[19] = inpt[3].v.Fm;\n"
"\n"
"    vec2 UV = gl_TessCoord.xy;\n"
"    ivec3 patchParam = inpt[0].v.patchParam;\n"
"    OsdEvalPatchGregory(patchParam, UV, cv, P, dPu, dPv, N, dNu, dNv);\n"
"\n"
"    // all code below here is client code\n"
"    outpt.v.position = OsdModelViewMatrix() * vec4(P, 1.0f);\n"
"    outpt.v.normal = (OsdModelViewMatrix() * vec4(N, 0.0f)).xyz;\n"
"    outpt.v.tangent = (OsdModelViewMatrix() * vec4(dPu, 0.0f)).xyz;\n"
"    outpt.v.bitangent = (OsdModelViewMatrix() * vec4(dPv, 0.0f)).xyz;\n"
"#ifdef OSD_COMPUTE_NORMAL_DERIVATIVES\n"
"    outpt.v.Nu = dNu;\n"
"    outpt.v.Nv = dNv;\n"
"#endif\n"
"\n"
"    outpt.v.tessCoord = UV;\n"
"    outpt.v.patchCoord = OsdInterpolatePatchCoord(UV, patchParam);\n"
"\n"
"    OSD_USER_VARYING_PER_EVAL_POINT(UV, 0, 1, 3, 2);\n"
"\n"
"    OSD_DISPLACEMENT_CALLBACK;\n"
"\n"
"    gl_Position = OsdProjectionMatrix() * outpt.v.position;\n"
"}\n"
"\n"
"#endif\n"
"\n"