xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 274;
 0.00000;5.53315;-1.02110;,
 0.00000;5.50860;-1.64473;,
 -2.07461;4.84813;-1.02110;,
 -0.89360;5.04300;-5.61429;,
 -1.93396;4.69843;-5.61429;,
 -1.19147;5.01587;-3.94064;,
 -0.89360;5.18811;-2.21867;,
 -1.51201;4.24930;-8.24832;,
 0.00000;4.75639;-8.24832;,
 0.00000;5.20140;-6.23624;,
 -0.27427;2.57622;9.67639;,
 -0.48589;2.44544;9.04654;,
 0.00000;2.30425;9.22952;,
 0.00000;2.49691;9.74074;,
 -0.69479;2.79572;9.22952;,
 -0.37027;2.80282;9.74074;,
 -0.27427;3.02942;9.67639;,
 -0.48589;3.13094;9.04654;,
 0.00000;3.27434;9.22952;,
 0.00000;3.10873;9.74074;,
 -2.51636;3.03533;8.59299;,
 -2.75963;2.80282;8.85559;,
 -2.51636;2.56807;8.59299;,
 -0.89489;2.13846;7.63789;,
 -2.50089;2.47859;7.88219;,
 -2.56738;2.53327;7.08538;,
 -0.85843;2.15905;6.05828;,
 -1.27778;2.77036;5.78949;,
 -2.79789;2.79779;6.90879;,
 -2.56738;3.05672;7.08538;,
 -0.85843;3.38011;6.05828;,
 -0.89489;3.42768;7.63789;,
 -2.50089;3.12202;7.88219;,
 -0.28277;0.37262;8.69310;,
 0.00000;0.12899;8.91995;,
 -0.31678;0.32377;7.38571;,
 0.00000;1.82440;5.85385;,
 0.00000;0.09235;7.29494;,
 -0.38940;0.30539;8.10744;,
 -0.28277;5.23078;8.69310;,
 0.00000;5.47664;8.91995;,
 -0.38940;5.23959;8.10744;,
 -0.31678;5.26623;7.38571;,
 0.00000;3.71633;5.85385;,
 0.00000;5.50323;7.29494;,
 0.00000;0.00000;8.19492;,
 -2.77500;2.80282;7.93749;,
 0.00000;5.55000;8.19492;,
 -1.13694;2.67927;-9.42968;,
 -0.95331;3.66061;-9.12340;,
 0.00000;3.84466;-9.42968;,
 0.00000;2.66301;-9.82346;,
 0.00000;1.51388;-9.42968;,
 -0.95331;1.72323;-9.12340;,
 -1.51201;1.20681;-8.24832;,
 0.00000;0.69972;-8.24832;,
 0.00000;0.21472;-5.61429;,
 -1.93396;0.85525;-5.61429;,
 -2.57862;2.77684;-5.61429;,
 -2.01601;2.72805;-8.24832;,
 -2.07461;0.73806;-1.02110;,
 0.00000;0.05305;-1.02110;,
 0.00000;0.81023;3.36766;,
 -1.43660;1.29547;3.36766;,
 -1.91547;2.75119;3.36766;,
 -2.76615;2.79310;-1.02110;,
 -1.43660;4.20691;3.36766;,
 0.00000;4.69214;3.36766;,
 -0.98420;1.75666;5.22979;,
 0.00000;1.41624;5.22979;,
 -1.31226;2.77793;5.22979;,
 -0.98420;3.79919;5.22979;,
 0.00000;4.13961;5.22979;,
 0.00000;2.80282;9.82346;,
 -0.89360;5.37142;-2.21867;,
 -0.89360;5.18710;-2.21867;,
 0.00000;6.22496;-1.64473;,
 -0.89360;6.22496;-2.21867;,
 -1.19147;5.37142;-3.94064;,
 -1.19147;5.01535;-3.94064;,
 -0.89360;5.18707;-2.21867;,
 -1.19147;5.01573;-3.94064;,
 -0.89360;5.37142;-5.61429;,
 -1.08710;6.07349;-3.33732;,
 -1.05141;6.22496;-3.13099;,
 -1.19147;6.00872;-3.94064;,
 -1.19147;6.52683;-3.94064;,
 -1.08710;6.46206;-3.33732;,
 -1.19147;7.17315;-3.94064;,
 -0.89360;7.17315;-2.21867;,
 -1.08166;6.46206;-4.57531;,
 -0.89360;7.17315;-5.61429;,
 -0.89360;6.22496;-5.61429;,
 -1.04596;6.22496;-4.78164;,
 -1.08166;6.07349;-4.57531;,
 -1.63733;6.07349;-4.57531;,
 -2.09215;6.12386;-4.41483;,
 -2.25133;6.22496;-4.57531;,
 -1.63733;6.22496;-4.78164;,
 -2.09215;6.41169;-4.41483;,
 -1.63733;6.46206;-4.57531;,
 -2.25133;6.46206;-3.94064;,
 -1.63733;6.52683;-3.94064;,
 -2.09215;6.41169;-3.49780;,
 -1.63733;6.46206;-3.33732;,
 -2.25133;6.22496;-3.33732;,
 -1.63733;6.22496;-3.13099;,
 -2.09215;6.12386;-3.49780;,
 -1.63733;6.07349;-3.33732;,
 -2.25133;6.07349;-3.94064;,
 -1.63733;6.00872;-3.94064;,
 -2.45600;6.22496;-3.94064;,
 -1.19147;6.22496;-3.94064;,
 0.00000;6.22496;-6.23624;,
 0.00000;7.17315;-1.64473;,
 0.00000;7.84880;-2.21867;,
 -0.66193;7.67363;-2.66507;,
 -0.89360;7.84880;-3.94064;,
 -0.66193;7.67363;-5.21591;,
 0.00000;7.84880;-5.66230;,
 0.00000;7.17315;-6.23624;,
 0.00000;8.07401;-3.94064;,
 2.07461;4.84813;-1.02110;,
 1.19147;5.01587;-3.94064;,
 1.93396;4.69843;-5.61429;,
 0.89360;5.04300;-5.61429;,
 0.89360;5.18811;-2.21867;,
 1.51201;4.24930;-8.24832;,
 0.48589;2.44544;9.04654;,
 0.27427;2.57622;9.67639;,
 0.69479;2.79572;9.22952;,
 0.37027;2.80282;9.74074;,
 0.48589;3.13094;9.04654;,
 0.27427;3.02942;9.67639;,
 2.51636;3.03533;8.59299;,
 2.75963;2.80282;8.85559;,
 2.51636;2.56807;8.59299;,
 0.89489;2.13846;7.63789;,
 2.50089;2.47859;7.88219;,
 0.85843;2.15905;6.05828;,
 2.56738;2.53327;7.08538;,
 1.27778;2.77036;5.78949;,
 2.79789;2.79779;6.90879;,
 0.85843;3.38011;6.05828;,
 2.56738;3.05672;7.08538;,
 0.89489;3.42768;7.63789;,
 2.50089;3.12202;7.88219;,
 0.28277;0.37262;8.69310;,
 0.31678;0.32377;7.38571;,
 0.38940;0.30539;8.10744;,
 0.28277;5.23078;8.69310;,
 0.38940;5.23959;8.10744;,
 0.31678;5.26623;7.38571;,
 2.77500;2.80282;7.93749;,
 0.95331;3.66061;-9.12340;,
 1.13694;2.67927;-9.42968;,
 0.95331;1.72323;-9.12340;,
 1.51201;1.20681;-8.24832;,
 1.93396;0.85525;-5.61429;,
 2.57862;2.77684;-5.61429;,
 2.01601;2.72805;-8.24832;,
 2.07461;0.73806;-1.02110;,
 1.43660;1.29547;3.36766;,
 1.91547;2.75119;3.36766;,
 2.76615;2.79310;-1.02110;,
 1.43660;4.20691;3.36766;,
 0.98420;1.75666;5.22979;,
 1.31226;2.77793;5.22979;,
 0.98420;3.79919;5.22979;,
 0.89360;5.18710;-2.21867;,
 0.89360;5.37142;-2.21867;,
 0.89360;6.22496;-2.21867;,
 1.19147;5.01535;-3.94064;,
 1.19147;5.37142;-3.94064;,
 0.89360;5.18707;-2.21867;,
 0.89360;5.37142;-5.61429;,
 1.19147;5.01573;-3.94064;,
 1.08710;6.07349;-3.33732;,
 1.05141;6.22496;-3.13099;,
 1.19147;6.00872;-3.94064;,
 1.19147;7.17315;-3.94064;,
 1.08710;6.46206;-3.33732;,
 1.19147;6.52683;-3.94064;,
 0.89360;7.17315;-2.21867;,
 1.08166;6.46206;-4.57531;,
 0.89360;7.17315;-5.61429;,
 0.89360;6.22496;-5.61429;,
 1.04596;6.22496;-4.78164;,
 1.08166;6.07349;-4.57531;,
 2.25133;6.22496;-4.57531;,
 2.09215;6.12386;-4.41483;,
 1.63733;6.07349;-4.57531;,
 1.63733;6.22496;-4.78164;,
 1.63733;6.46206;-4.57531;,
 2.09215;6.41169;-4.41483;,
 2.25133;6.46206;-3.94064;,
 1.63733;6.52683;-3.94064;,
 1.63733;6.46206;-3.33732;,
 2.09215;6.41169;-3.49780;,
 2.25133;6.22496;-3.33732;,
 1.63733;6.22496;-3.13099;,
 1.63733;6.07349;-3.33732;,
 2.09215;6.12386;-3.49780;,
 2.25133;6.07349;-3.94064;,
 1.63733;6.00872;-3.94064;,
 2.45600;6.22496;-3.94064;,
 1.19147;6.22496;-3.94064;,
 0.66193;7.67363;-2.66507;,
 0.89360;7.84880;-3.94064;,
 0.66193;7.67363;-5.21591;,
 -2.15588;2.98021;9.55677;,
 -1.34224;3.15482;9.48782;,
 -1.34224;2.47310;9.48782;,
 -2.15588;2.64770;9.55677;,
 -1.34224;2.47310;9.80904;,
 -2.15588;2.64770;9.67832;,
 -1.34224;3.15482;9.80904;,
 -2.15588;2.98021;9.67832;,
 0.16625;4.96983;9.67832;,
 0.34086;4.15619;9.80904;,
 0.34086;4.15619;9.48782;,
 0.16625;4.96983;9.55677;,
 -0.34086;4.15619;9.48782;,
 -0.16625;4.96983;9.55677;,
 -0.34086;4.15619;9.80904;,
 -0.16625;4.96983;9.67832;,
 0.16625;0.65808;9.55677;,
 0.34086;1.47172;9.48782;,
 0.34086;1.47172;9.80904;,
 0.16625;0.65808;9.67832;,
 -0.34086;1.47172;9.80904;,
 -0.16625;0.65808;9.67832;,
 -0.34086;1.47172;9.48782;,
 -0.16625;0.65808;9.55677;,
 2.15588;2.64770;9.67832;,
 1.34224;2.47310;9.80904;,
 1.34224;2.47310;9.48782;,
 2.15588;2.64770;9.55677;,
 1.34224;3.15482;9.48782;,
 2.15588;2.98021;9.55677;,
 1.34224;3.15482;9.80904;,
 2.15588;2.98021;9.67832;,
 -0.59458;3.00616;9.53961;,
 -0.59458;2.62175;9.53961;,
 -0.53519;2.64095;9.75368;,
 -0.53519;2.98696;9.75368;,
 0.17300;3.34914;9.75368;,
 0.19220;3.40854;9.53961;,
 -0.19220;3.40854;9.53961;,
 -0.17300;3.34914;9.75368;,
 0.19220;2.21938;9.53961;,
 0.17300;2.27877;9.75368;,
 -0.17300;2.27877;9.75368;,
 -0.19220;2.21938;9.53961;,
 0.53519;2.64095;9.75368;,
 0.59458;2.62175;9.53961;,
 0.59458;3.00616;9.53961;,
 0.53519;2.98696;9.75368;,
 -0.34777;3.16173;9.45545;,
 -0.34777;2.46619;9.45545;,
 -0.28806;2.52590;9.83785;,
 -0.28806;3.10202;9.83785;,
 0.28806;3.10202;9.83785;,
 0.34777;3.16173;9.45545;,
 0.34777;2.46619;9.45545;,
 0.28806;2.52590;9.83785;,
 0.25730;3.07125;9.17246;,
 0.25730;2.55666;9.17246;,
 -0.25730;2.55666;9.17246;,
 -0.25730;3.07125;9.17246;,
 0.15438;2.65958;10.17651;,
 0.15438;2.96834;10.17651;,
 -0.15438;2.96834;10.17651;,
 -0.15438;2.65958;10.17651;;
 
 284;
 3;0,1,2;,
 3;3,4,5;,
 3;4,2,5;,
 3;5,2,6;,
 3;6,2,1;,
 3;4,3,7;,
 4;8,7,3,9;,
 4;10,11,12,13;,
 4;14,11,10,15;,
 4;16,17,14,15;,
 4;18,17,16,19;,
 4;14,17,20,21;,
 4;22,11,14,21;,
 4;23,11,22,24;,
 4;25,26,23,24;,
 4;27,26,25,28;,
 4;29,30,27,28;,
 4;31,30,29,32;,
 4;20,17,31,32;,
 4;12,11,33,34;,
 4;35,26,36,37;,
 4;23,26,35,38;,
 4;33,11,23,38;,
 4;39,17,18,40;,
 4;31,17,39,41;,
 4;42,30,31,41;,
 4;43,30,42,44;,
 4;34,33,38,45;,
 4;38,35,37,45;,
 4;21,20,32,46;,
 4;24,22,21,46;,
 4;28,25,24,46;,
 4;32,29,28,46;,
 4;41,39,40,47;,
 4;44,42,41,47;,
 4;48,49,50,51;,
 4;52,53,48,51;,
 4;54,53,52,55;,
 4;56,57,54,55;,
 4;54,57,58,59;,
 4;48,53,54,59;,
 4;7,49,48,59;,
 4;58,4,7,59;,
 4;50,49,7,8;,
 4;60,57,56,61;,
 4;62,63,60,61;,
 4;60,63,64,65;,
 4;58,57,60,65;,
 4;2,4,58,65;,
 4;64,66,2,65;,
 4;2,66,67,0;,
 4;68,63,62,69;,
 4;36,26,68,69;,
 4;64,63,68,70;,
 4;71,66,64,70;,
 4;27,30,71,70;,
 4;68,26,27,70;,
 4;67,66,71,72;,
 4;71,30,43,72;,
 4;15,10,13,73;,
 4;19,16,15,73;,
 3;1,74,75;,
 4;76,77,74,1;,
 4;74,78,79,80;,
 4;81,78,82,3;,
 3;3,82,9;,
 4;83,74,77,84;,
 3;85,78,83;,
 3;78,74,83;,
 3;86,87,88;,
 4;77,89,87,84;,
 3;87,89,88;,
 3;86,88,90;,
 3;88,91,90;,
 4;90,91,92,93;,
 3;85,94,78;,
 4;92,82,94,93;,
 3;94,82,78;,
 4;95,96,97,98;,
 4;97,99,100,98;,
 4;100,99,101,102;,
 4;101,103,104,102;,
 4;104,103,105,106;,
 4;105,107,108,106;,
 4;108,107,109,110;,
 4;109,96,95,110;,
 4;97,96,109,111;,
 4;101,99,97,111;,
 4;105,103,101,111;,
 4;109,107,105,111;,
 4;84,112,85,83;,
 4;85,112,93,94;,
 4;86,112,84,87;,
 4;93,112,86,90;,
 4;110,95,94,85;,
 4;83,108,110,85;,
 4;84,106,108,83;,
 4;104,106,84,87;,
 4;102,104,87,86;,
 4;90,100,102,86;,
 4;93,98,100,90;,
 4;95,98,93,94;,
 4;82,92,113,9;,
 4;89,77,76,114;,
 4;115,116,89,114;,
 4;89,116,117,88;,
 4;117,118,91,88;,
 4;91,118,119,120;,
 4;113,92,91,120;,
 4;117,116,115,121;,
 4;119,118,117,121;,
 3;122,1,0;,
 3;123,124,125;,
 3;123,122,124;,
 3;126,122,123;,
 3;1,122,126;,
 3;127,125,124;,
 4;125,127,8,9;,
 4;12,128,129,13;,
 4;129,128,130,131;,
 4;130,132,133,131;,
 4;133,132,18,19;,
 4;134,132,130,135;,
 4;130,128,136,135;,
 4;136,128,137,138;,
 4;137,139,140,138;,
 4;140,139,141,142;,
 4;141,143,144,142;,
 4;144,143,145,146;,
 4;145,132,134,146;,
 4;147,128,12,34;,
 4;36,139,148,37;,
 4;148,139,137,149;,
 4;137,128,147,149;,
 4;18,132,150,40;,
 4;150,132,145,151;,
 4;145,143,152,151;,
 4;152,143,43,44;,
 4;149,147,34,45;,
 4;37,148,149,45;,
 4;146,134,135,153;,
 4;135,136,138,153;,
 4;138,140,142,153;,
 4;142,144,146,153;,
 4;40,150,151,47;,
 4;151,152,44,47;,
 4;50,154,155,51;,
 4;155,156,52,51;,
 4;52,156,157,55;,
 4;157,158,56,55;,
 4;159,158,157,160;,
 4;157,156,155,160;,
 4;155,154,127,160;,
 4;127,124,159,160;,
 4;127,154,50,8;,
 4;56,158,161,61;,
 4;161,162,62,61;,
 4;163,162,161,164;,
 4;161,158,159,164;,
 4;159,124,122,164;,
 4;122,165,163,164;,
 4;67,165,122,0;,
 4;62,162,166,69;,
 4;166,139,36,69;,
 4;166,162,163,167;,
 4;163,165,168,167;,
 4;168,143,141,167;,
 4;141,139,166,167;,
 4;168,165,67,72;,
 4;43,143,168,72;,
 4;13,129,131,73;,
 4;131,133,19,73;,
 3;169,170,1;,
 4;170,171,76,1;,
 4;172,173,170,174;,
 4;175,173,176,125;,
 3;9,175,125;,
 4;171,170,177,178;,
 3;177,173,179;,
 3;177,170,173;,
 3;180,181,182;,
 4;181,183,171,178;,
 3;180,183,181;,
 3;184,180,182;,
 3;184,185,180;,
 4;186,185,184,187;,
 3;173,188,179;,
 4;188,175,186,187;,
 3;173,175,188;,
 4;189,190,191,192;,
 4;193,194,189,192;,
 4;195,194,193,196;,
 4;197,198,195,196;,
 4;199,198,197,200;,
 4;201,202,199,200;,
 4;203,202,201,204;,
 4;191,190,203,204;,
 4;203,190,189,205;,
 4;189,194,195,205;,
 4;195,198,199,205;,
 4;199,202,203,205;,
 4;179,206,178,177;,
 4;187,206,179,188;,
 4;178,206,182,181;,
 4;182,206,187,184;,
 4;188,191,204,179;,
 4;204,201,177,179;,
 4;201,200,178,177;,
 4;178,200,197,181;,
 4;181,197,196,182;,
 4;196,193,184,182;,
 4;193,192,187,184;,
 4;187,192,191,188;,
 4;113,186,175,9;,
 4;76,171,183,114;,
 4;183,207,115,114;,
 4;208,207,183,180;,
 4;185,209,208,180;,
 4;119,209,185,120;,
 4;185,186,113,120;,
 4;115,207,208,121;,
 4;208,209,119,121;,
 4;210,211,212,213;,
 4;213,212,214,215;,
 4;215,214,216,217;,
 4;217,216,211,210;,
 4;218,219,220,221;,
 4;221,220,222,223;,
 4;223,222,224,225;,
 4;225,224,219,218;,
 4;226,227,228,229;,
 4;229,228,230,231;,
 4;231,230,232,233;,
 4;233,232,227,226;,
 4;234,235,236,237;,
 4;237,236,238,239;,
 4;239,238,240,241;,
 4;241,240,235,234;,
 4;211,242,243,212;,
 4;212,243,244,214;,
 4;214,244,245,216;,
 4;216,245,242,211;,
 4;219,246,247,220;,
 4;220,247,248,222;,
 4;222,248,249,224;,
 4;224,249,246,219;,
 4;227,250,251,228;,
 4;228,251,252,230;,
 4;230,252,253,232;,
 4;232,253,250,227;,
 4;235,254,255,236;,
 4;236,255,256,238;,
 4;238,256,257,240;,
 4;240,257,254,235;,
 4;242,258,259,243;,
 4;243,259,260,244;,
 4;244,260,261,245;,
 4;245,261,258,242;,
 4;246,262,263,247;,
 4;247,263,258,248;,
 4;248,258,261,249;,
 4;249,261,262,246;,
 4;250,264,265,251;,
 4;251,265,260,252;,
 4;252,260,259,253;,
 4;253,259,264,250;,
 4;254,265,264,255;,
 4;255,264,263,256;,
 4;256,263,262,257;,
 4;257,262,265,254;,
 4;266,263,264,267;,
 4;267,264,259,268;,
 4;268,259,258,269;,
 4;269,258,263,266;,
 4;270,265,262,271;,
 4;271,262,261,272;,
 4;272,261,260,273;,
 4;273,260,265,270;,
 4;210,213,215,217;,
 4;266,267,268,269;,
 4;218,221,223,225;,
 4;270,271,272,273;,
 4;226,229,231,233;,
 4;234,237,239,241;;
 
 MeshMaterialList {
  1;
  284;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.239216;0.239216;0.239216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.059804;0.059804;0.059804;;
  }
 }
 MeshNormals {
  340;
  0.833393;-0.000000;0.552681;,
  0.841594;-0.000175;-0.540110;,
  0.589793;0.735379;0.333710;,
  0.597502;0.727765;-0.336674;,
  0.999998;-0.000747;-0.001620;,
  0.878609;0.000000;0.477542;,
  -0.545208;0.340560;0.766007;,
  -0.540412;0.000000;0.841401;,
  0.883708;-0.001555;-0.468036;,
  0.987249;0.159179;-0.001256;,
  1.000000;0.000000;-0.000015;,
  -0.568553;0.328960;-0.754011;,
  -0.571257;0.000000;-0.820771;,
  0.000000;1.000000;-0.000017;,
  0.864463;0.245529;0.438656;,
  0.000000;0.904882;0.425662;,
  0.868054;0.239812;-0.434710;,
  0.636295;0.771446;-0.000677;,
  0.000000;0.901806;-0.432142;,
  0.985367;-0.000000;0.170449;,
  0.985367;0.000000;0.170449;,
  1.000000;0.000000;-0.000015;,
  0.984754;-0.000161;-0.173956;,
  0.984858;-0.001802;-0.173352;,
  1.000000;-0.000000;-0.000015;,
  0.985367;-0.000000;0.170449;,
  0.984841;0.001627;-0.173453;,
  0.289408;-0.914244;-0.283549;,
  0.087746;-0.936713;-0.338925;,
  0.108469;-0.828739;-0.549023;,
  0.367223;-0.857366;-0.360653;,
  0.386951;0.840265;-0.379769;,
  0.105541;0.889658;-0.444263;,
  0.062843;0.998018;0.003184;,
  0.437178;0.899356;0.005890;,
  0.384665;0.838092;0.386826;,
  0.105632;0.888209;0.447132;,
  0.136012;0.675503;0.724704;,
  0.496683;0.710437;0.498583;,
  0.288143;-0.912656;0.289885;,
  0.087886;-0.935606;0.341931;,
  0.062844;-0.998018;0.003184;,
  0.324944;-0.945720;0.005013;,
  0.513505;-0.858065;0.006097;,
  0.000000;0.976192;-0.216909;,
  0.540412;0.000000;0.841401;,
  0.985367;0.000000;0.170449;,
  0.311538;0.938009;-0.151930;,
  0.984529;0.000000;-0.175221;,
  0.000000;0.999158;-0.041016;,
  0.314147;0.948509;-0.040535;,
  0.314147;0.948509;-0.040535;,
  0.553650;-0.649933;0.520633;,
  0.486168;-0.626531;0.609180;,
  0.000000;-0.688605;0.725137;,
  -0.219889;-0.773902;0.593907;,
  0.473636;-0.642021;0.602892;,
  0.465347;-0.203111;0.861509;,
  0.554764;0.657048;0.510416;,
  0.489271;0.639983;0.592482;,
  0.000000;0.705456;0.708753;,
  -0.222050;0.793743;0.566274;,
  0.487690;0.767683;0.415718;,
  0.370858;0.864843;0.338394;,
  0.381219;-0.858529;0.342929;,
  0.186152;-0.979709;0.074283;,
  0.490906;-0.869507;0.054476;,
  0.655632;-0.743749;-0.130326;,
  0.519133;-0.827396;-0.214284;,
  0.775817;-0.592324;-0.217395;,
  0.648189;-0.700834;-0.297795;,
  0.653056;0.745633;-0.132469;,
  0.505045;0.832786;-0.226709;,
  0.168244;0.983724;0.063093;,
  0.479518;0.876310;0.046309;,
  -0.675785;-0.488440;0.552033;,
  0.798705;-0.389491;0.458657;,
  0.742004;-0.602987;-0.292979;,
  -0.574040;-0.719440;-0.391003;,
  0.000000;-0.654459;-0.756098;,
  0.844963;-0.529998;0.071686;,
  0.809255;0.390750;0.438658;,
  -0.683719;0.505712;0.526103;,
  0.847760;0.526199;0.066466;,
  0.749830;0.599930;-0.278995;,
  0.000000;0.642961;-0.765899;,
  -0.584916;0.718860;-0.375651;,
  -0.641568;-0.765955;0.041281;,
  0.737177;0.675250;0.024647;,
  -0.639006;0.768553;0.031581;,
  0.000000;-0.004243;-0.999991;,
  0.000000;-0.598671;-0.800995;,
  0.000000;0.574153;-0.818748;,
  0.477543;0.470493;-0.742017;,
  0.587380;-0.003151;-0.809305;,
  0.489775;-0.486331;-0.723604;,
  -0.000000;-0.916073;-0.401012;,
  -0.000000;-0.994026;-0.109143;,
  0.639985;-0.640109;-0.425064;,
  0.700649;-0.703003;-0.121972;,
  0.904145;-0.001277;-0.427224;,
  0.992201;-0.000198;-0.124650;,
  0.574316;0.709666;-0.408087;,
  0.626947;0.770003;-0.118457;,
  -0.000000;0.897750;-0.440505;,
  0.000000;-0.997666;0.068289;,
  0.000000;-0.970294;0.241930;,
  0.704212;-0.705973;0.075419;,
  0.685409;-0.680416;0.259323;,
  0.997190;-0.000095;0.074914;,
  0.968677;0.000106;0.248323;,
  0.541048;0.840598;0.025741;,
  0.685665;0.681136;0.256742;,
  0.000000;0.997142;0.075554;,
  0.000000;0.971225;0.238165;,
  0.000000;-0.911093;0.412202;,
  0.657531;-0.665051;0.354063;,
  0.964929;-0.000229;0.262511;,
  0.658359;0.665506;0.351662;,
  -0.000000;0.913045;0.407859;,
  0.000000;-0.000000;1.000000;,
  -0.541048;0.840598;0.025741;,
  -0.626947;0.770003;-0.118457;,
  -0.311538;0.938009;-0.151930;,
  -0.314147;0.948509;-0.040535;,
  -0.314147;0.948509;-0.040535;,
  -0.574316;0.709666;-0.408087;,
  -0.553650;-0.649933;0.520633;,
  -0.486168;-0.626531;0.609180;,
  -0.473636;-0.642021;0.602892;,
  -0.465347;-0.203111;0.861509;,
  -0.554764;0.657048;0.510416;,
  -0.489271;0.639983;0.592482;,
  -0.487690;0.767683;0.415718;,
  -0.370858;0.864843;0.338394;,
  -0.381219;-0.858529;0.342929;,
  -0.186152;-0.979709;0.074283;,
  -0.490906;-0.869507;0.054476;,
  -0.655632;-0.743749;-0.130326;,
  -0.519133;-0.827396;-0.214284;,
  -0.775817;-0.592324;-0.217395;,
  -0.648189;-0.700834;-0.297795;,
  -0.653056;0.745633;-0.132469;,
  -0.505045;0.832786;-0.226709;,
  -0.168244;0.983724;0.063093;,
  -0.479518;0.876310;0.046309;,
  -0.798705;-0.389491;0.458657;,
  -0.742004;-0.602987;-0.292979;,
  -0.844963;-0.529998;0.071686;,
  -0.809255;0.390750;0.438658;,
  -0.847760;0.526199;0.066466;,
  -0.749830;0.599930;-0.278995;,
  -0.737177;0.675250;0.024647;,
  -0.477543;0.470493;-0.742017;,
  -0.587380;-0.003151;-0.809305;,
  -0.489775;-0.486331;-0.723604;,
  -0.639985;-0.640109;-0.425064;,
  -0.700649;-0.703003;-0.121972;,
  -0.904145;-0.001277;-0.427224;,
  -0.992201;-0.000198;-0.124650;,
  -0.704212;-0.705973;0.075419;,
  -0.685409;-0.680416;0.259323;,
  -0.997190;-0.000095;0.074914;,
  -0.968677;0.000106;0.248323;,
  -0.685665;0.681136;0.256742;,
  -0.657531;-0.665051;0.354063;,
  -0.964929;-0.000229;0.262511;,
  -0.658359;0.665506;0.351662;,
  -0.878609;0.000000;0.477542;,
  -0.540412;0.000000;0.841401;,
  -0.833393;-0.000000;0.552681;,
  -0.999998;-0.000747;-0.001620;,
  -0.985367;0.000000;0.170449;,
  -0.984529;0.000000;-0.175221;,
  -0.883708;-0.001555;-0.468036;,
  -0.985367;0.000000;0.170449;,
  -0.985367;-0.000000;0.170449;,
  -1.000000;0.000000;-0.000015;,
  -0.985367;-0.000000;0.170449;,
  -1.000000;-0.000000;-0.000015;,
  -0.987249;0.159179;-0.001256;,
  -0.864463;0.245529;0.438656;,
  -0.984841;0.001627;-0.173453;,
  -0.868054;0.239812;-0.434710;,
  -0.984754;-0.000161;-0.173956;,
  -0.841594;-0.000175;-0.540110;,
  -0.984858;-0.001802;-0.173352;,
  -0.289408;-0.914244;-0.283549;,
  -0.087746;-0.936713;-0.338925;,
  -0.108469;-0.828739;-0.549023;,
  -0.367223;-0.857366;-0.360653;,
  -0.386951;0.840265;-0.379769;,
  -0.105541;0.889658;-0.444263;,
  -0.062843;0.998018;0.003184;,
  -0.437178;0.899356;0.005890;,
  -0.384665;0.838092;0.386826;,
  -0.105632;0.888209;0.447132;,
  -0.136012;0.675503;0.724704;,
  -0.496683;0.710437;0.498583;,
  -0.288143;-0.912656;0.289885;,
  -0.087886;-0.935606;0.341931;,
  -0.062844;-0.998018;0.003184;,
  -0.324944;-0.945720;0.005013;,
  -0.513505;-0.858065;0.006097;,
  -1.000000;0.000000;-0.000015;,
  -0.589793;0.735379;0.333710;,
  -0.636295;0.771446;-0.000677;,
  -0.597502;0.727765;-0.336674;,
  -0.165749;-0.165750;-0.972139;,
  -0.123790;0.480960;0.867959;,
  -0.165749;0.165750;-0.972139;,
  -0.665348;-0.665348;0.338560;,
  0.863406;-0.502781;0.041727;,
  0.665348;0.665348;0.338560;,
  0.863406;0.502782;0.041727;,
  0.665348;-0.665348;0.338560;,
  0.952506;0.000000;-0.304518;,
  0.000000;-0.952506;-0.304519;,
  -0.952506;0.000000;-0.304518;,
  0.930158;0.000000;0.367159;,
  0.000000;0.930158;0.367159;,
  -0.930158;0.000000;0.367159;,
  -0.129374;0.000000;-0.991596;,
  -0.144202;-0.982359;0.119066;,
  -0.129517;0.000000;0.991577;,
  0.982359;0.144202;0.119065;,
  0.000000;0.129374;-0.991596;,
  -0.982359;0.144202;0.119065;,
  0.982359;-0.144202;0.119065;,
  0.000000;-0.129517;0.991577;,
  -0.982359;-0.144202;0.119065;,
  0.144202;-0.982359;0.119066;,
  0.129374;0.000000;-0.991596;,
  0.144202;0.982359;0.119066;,
  -0.007690;0.000000;-0.999970;,
  -0.004861;-0.999957;0.007843;,
  -0.045394;0.000000;0.998969;,
  0.999957;0.004861;0.007843;,
  0.000000;0.007690;-0.999970;,
  -0.999957;0.004861;0.007843;,
  0.999957;-0.004861;0.007843;,
  0.000000;-0.045394;0.998969;,
  -0.999957;-0.004861;0.007843;,
  0.004861;-0.999957;0.007843;,
  0.007690;0.000000;-0.999970;,
  0.004861;0.999957;0.007843;,
  -0.084437;0.000000;-0.996429;,
  -0.209821;-0.977740;0.000000;,
  -0.158626;0.000000;0.987339;,
  0.977740;0.209821;0.000000;,
  0.000000;0.084437;-0.996429;,
  -0.977740;0.209821;0.000000;,
  0.977740;-0.209821;-0.000000;,
  0.000000;-0.158626;0.987339;,
  -0.977740;-0.209821;0.000000;,
  0.209821;-0.977740;-0.000000;,
  0.084437;0.000000;-0.996429;,
  0.209820;0.977740;0.000000;,
  -0.473293;0.651672;0.592720;,
  -0.734651;0.542251;0.407740;,
  -0.494299;-0.761447;0.419365;,
  -0.771757;0.596486;-0.220444;,
  -0.637139;0.706595;-0.307858;,
  -0.966024;-0.240287;0.095181;,
  -0.969576;0.225713;0.094743;,
  -0.742574;-0.669132;0.029096;,
  0.000000;-0.862128;0.506690;,
  0.000000;0.853889;0.520455;,
  -0.842201;0.000000;-0.539164;,
  -0.571257;0.000000;-0.820771;,
  -0.500451;0.712271;-0.492157;,
  -0.136012;0.675502;-0.724705;,
  -0.364951;-0.855934;0.366315;,
  -0.108469;-0.828740;0.549022;,
  -0.709668;0.704497;0.007459;,
  0.000000;-0.933237;-0.359261;,
  0.000000;-0.999997;0.002622;,
  0.000000;-0.932292;0.361706;,
  0.000000;-0.806102;0.591777;,
  0.000000;0.656460;0.754361;,
  0.000000;0.886622;0.462495;,
  0.000000;0.999997;0.002622;,
  0.000000;0.887831;-0.460169;,
  0.000000;0.656459;-0.754362;,
  0.000000;-0.806101;-0.591778;,
  0.473293;0.651672;0.592720;,
  0.734651;0.542251;0.407740;,
  0.494299;-0.761447;0.419365;,
  0.771757;0.596486;-0.220444;,
  0.637139;0.706595;-0.307858;,
  0.542624;-0.150073;0.826460;,
  0.675785;-0.488440;0.552033;,
  0.574040;-0.719440;-0.391003;,
  0.966024;-0.240287;0.095181;,
  0.542723;0.148229;0.826728;,
  0.683719;0.505712;0.526103;,
  0.969576;0.225713;0.094743;,
  0.584916;0.718860;-0.375651;,
  0.641568;-0.765955;0.041281;,
  0.742574;-0.669132;0.029096;,
  0.639006;0.768553;0.031581;,
  0.540412;0.000000;0.841401;,
  0.842201;0.000000;-0.539164;,
  0.571257;0.000000;-0.820771;,
  0.500451;0.712271;-0.492157;,
  0.136012;0.675502;-0.724705;,
  0.364951;-0.855934;0.366315;,
  0.108469;-0.828740;0.549022;,
  0.709668;0.704497;0.007459;,
  0.571257;0.000000;-0.820771;,
  0.545208;0.340560;0.766007;,
  0.568553;0.328960;-0.754011;,
  -0.209820;0.977740;0.000000;,
  -0.004861;0.999957;0.007843;,
  0.000000;0.158626;0.987339;,
  0.000000;0.045394;0.998969;,
  0.000000;-0.084437;-0.996429;,
  0.000000;-0.007690;-0.999970;,
  0.158626;0.000000;0.987339;,
  0.045394;0.000000;0.998969;,
  -0.144202;0.982359;0.119066;,
  0.000000;0.129517;0.991577;,
  0.000000;-0.129374;-0.991596;,
  0.129517;0.000000;0.991577;,
  -0.502782;-0.863406;0.041727;,
  -0.165549;-0.165549;0.972207;,
  -0.825985;0.485750;0.286000;,
  -0.863406;0.502782;0.041727;,
  0.165749;0.165750;-0.972139;,
  0.165549;0.165549;0.972207;,
  0.165549;-0.165549;0.972207;,
  0.165749;-0.165750;-0.972139;,
  0.000000;0.952507;-0.304517;,
  0.000000;-0.930158;0.367158;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;;
  284;
  3;113,49,121;,
  3;123,122,124;,
  3;122,121,124;,
  3;124,121,125;,
  3;125,121,49;,
  3;122,123,126;,
  4;104,126,123,44;,
  4;128,127,55,54;,
  4;129,127,128,130;,
  4;132,131,258,259;,
  4;61,131,132,60;,
  4;258,131,134,133;,
  4;135,127,129,260;,
  4;136,127,135,137;,
  4;139,138,136,137;,
  4;140,138,139,141;,
  4;143,142,261,262;,
  4;144,142,143,145;,
  4;134,131,144,145;,
  4;55,127,146,75;,
  4;147,138,79,78;,
  4;263,138,147,148;,
  4;146,127,263,148;,
  4;149,131,61,82;,
  4;264,131,149,150;,
  4;151,142,264,150;,
  4;85,142,151,86;,
  4;75,146,148,87;,
  4;148,147,78,87;,
  4;133,134,145,152;,
  4;137,135,260,265;,
  4;141,139,137,265;,
  4;145,143,262,152;,
  4;150,149,82,89;,
  4;86,151,150,89;,
  4;154,153,92,90;,
  4;91,155,154,90;,
  4;156,155,91,96;,
  4;97,157,156,96;,
  4;156,157,159,158;,
  4;154,155,156,158;,
  4;126,153,154,158;,
  4;159,122,126,158;,
  4;92,153,126,104;,
  4;160,157,97,105;,
  4;106,161,160,105;,
  4;160,161,163,162;,
  4;159,157,160,162;,
  4;121,122,159,162;,
  4;163,164,121,162;,
  4;121,164,114,113;,
  4;165,161,106,115;,
  4;266,138,165,115;,
  4;163,161,165,166;,
  4;167,164,163,166;,
  4;261,142,167,166;,
  4;165,138,140,166;,
  4;114,164,167,119;,
  4;167,142,267,119;,
  4;130,128,54,120;,
  4;60,132,130,120;,
  3;7,168,169;,
  4;7,170,168,7;,
  4;168,171,172,172;,
  4;173,171,174,268;,
  3;268,174,269;,
  4;175,168,170,176;,
  3;177,171,175;,
  3;171,168,175;,
  3;179,178,180;,
  4;170,181,178,176;,
  3;178,181,180;,
  3;179,180,182;,
  3;180,183,182;,
  4;182,183,185,184;,
  3;177,186,171;,
  4;185,174,186,184;,
  3;186,174,171;,
  4;188,187,190,189;,
  4;270,191,192,271;,
  4;192,191,194,193;,
  4;194,195,196,193;,
  4;196,195,198,197;,
  4;272,199,200,273;,
  4;200,199,202,201;,
  4;202,187,188,201;,
  4;190,187,202,203;,
  4;194,191,270,274;,
  4;198,195,194,274;,
  4;202,199,272,203;,
  4;176,204,177,175;,
  4;177,204,184,186;,
  4;179,204,176,178;,
  4;184,204,179,182;,
  4;201,188,275,276;,
  4;277,200,201,276;,
  4;278,273,200,277;,
  4;196,197,279,280;,
  4;193,196,280,281;,
  4;282,192,193,281;,
  4;283,271,192,282;,
  4;188,189,284,275;,
  4;174,185,12,269;,
  4;181,170,7,6;,
  4;15,205,181,6;,
  4;181,205,206,180;,
  4;206,207,183,180;,
  4;183,207,18,11;,
  4;12,185,183,11;,
  4;206,205,15,13;,
  4;18,207,206,13;,
  3;111,49,113;,
  3;51,103,47;,
  3;51,111,103;,
  3;50,111,51;,
  3;49,111,50;,
  3;102,47,103;,
  4;47,102,104,44;,
  4;55,52,53,54;,
  4;53,52,56,57;,
  4;285,58,59,286;,
  4;59,58,61,60;,
  4;63,58,285,62;,
  4;56,52,64,287;,
  4;64,52,65,66;,
  4;65,67,68,66;,
  4;68,67,69,70;,
  4;288,71,72,289;,
  4;72,71,73,74;,
  4;73,58,63,74;,
  4;76,52,290,291;,
  4;79,67,77,292;,
  4;77,67,293,80;,
  4;293,52,76,80;,
  4;294,58,81,295;,
  4;81,58,296,83;,
  4;296,71,84,83;,
  4;84,71,85,297;,
  4;80,76,291,298;,
  4;292,77,80,298;,
  4;74,63,62,88;,
  4;287,64,66,299;,
  4;66,68,70,299;,
  4;289,72,74,88;,
  4;295,81,83,300;,
  4;83,84,297,300;,
  4;92,93,94,90;,
  4;94,95,91,90;,
  4;91,95,98,96;,
  4;98,99,97,96;,
  4;101,99,98,100;,
  4;98,95,94,100;,
  4;94,93,102,100;,
  4;102,103,101,100;,
  4;102,93,92,104;,
  4;97,99,107,105;,
  4;107,108,106,105;,
  4;110,108,107,109;,
  4;107,99,101,109;,
  4;101,103,111,109;,
  4;111,112,110,109;,
  4;114,112,111,113;,
  4;106,108,116,115;,
  4;116,67,266,115;,
  4;116,108,110,117;,
  4;110,112,118,117;,
  4;118,71,288,117;,
  4;69,67,116,117;,
  4;118,112,114,119;,
  4;267,71,118,119;,
  4;54,53,57,120;,
  4;57,59,60,120;,
  3;45,5,301;,
  4;5,0,301,301;,
  4;46,4,5,46;,
  4;8,4,48,302;,
  3;303,8,302;,
  4;0,5,20,19;,
  3;20,4,21;,
  3;20,5,4;,
  3;9,25,24;,
  4;25,14,0,19;,
  3;9,14,25;,
  3;26,9,24;,
  3;26,16,9;,
  4;1,16,26,22;,
  3;4,23,21;,
  4;23,8,1,22;,
  3;4,8,23;,
  4;30,27,28,29;,
  4;32,31,304,305;,
  4;34,31,32,33;,
  4;36,35,34,33;,
  4;38,35,36,37;,
  4;40,39,306,307;,
  4;42,39,40,41;,
  4;28,27,42,41;,
  4;42,27,30,43;,
  4;304,31,34,308;,
  4;34,35,38,308;,
  4;306,39,42,43;,
  4;21,10,19,20;,
  4;22,10,21,23;,
  4;19,10,24,25;,
  4;24,10,22,26;,
  4;275,28,41,276;,
  4;41,40,277,276;,
  4;40,307,278,277;,
  4;279,37,36,280;,
  4;280,36,33,281;,
  4;33,32,282,281;,
  4;32,305,283,282;,
  4;284,29,28,275;,
  4;309,1,8,303;,
  4;301,0,14,310;,
  4;14,2,15,310;,
  4;17,2,14,9;,
  4;16,3,17,9;,
  4;18,3,16,311;,
  4;16,1,309,311;,
  4;15,2,17,13;,
  4;17,3,18,13;,
  4;246,234,234,246;,
  4;247,235,235,247;,
  4;248,236,236,248;,
  4;312,313,313,312;,
  4;249,237,237,249;,
  4;250,238,238,250;,
  4;251,239,239,251;,
  4;314,315,315,314;,
  4;252,240,240,252;,
  4;253,241,241,253;,
  4;254,242,242,254;,
  4;316,317,317,316;,
  4;255,243,243,255;,
  4;256,244,244,256;,
  4;257,245,245,257;,
  4;318,319,319,318;,
  4;234,222,222,234;,
  4;235,223,223,235;,
  4;236,224,224,236;,
  4;313,320,320,313;,
  4;237,225,225,237;,
  4;238,226,226,238;,
  4;239,227,227,239;,
  4;315,321,321,315;,
  4;240,228,228,240;,
  4;241,229,229,241;,
  4;242,230,230,242;,
  4;317,322,322,317;,
  4;243,231,231,243;,
  4;244,232,232,244;,
  4;245,233,233,245;,
  4;319,323,323,319;,
  4;222,210,208,222;,
  4;223,324,211,223;,
  4;224,325,209,224;,
  4;320,326,327,320;,
  4;225,213,214,225;,
  4;226,328,210,226;,
  4;227,327,326,227;,
  4;321,209,329,321;,
  4;228,212,215,228;,
  4;229,330,325,229;,
  4;230,211,324,230;,
  4;322,208,331,322;,
  4;231,215,212,231;,
  4;232,331,328,232;,
  4;233,214,213,233;,
  4;323,329,330,323;,
  4;216,214,212,216;,
  4;217,217,324,217;,
  4;218,218,327,218;,
  4;332,332,332,332;,
  4;219,215,213,219;,
  4;220,213,209,220;,
  4;221,326,211,221;,
  4;333,211,215,333;,
  4;334,334,334,334;,
  4;335,335,335,335;,
  4;336,336,336,336;,
  4;337,337,337,337;,
  4;338,338,338,338;,
  4;339,339,339,339;;
 }
 MeshTextureCoords {
  274;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;
  0.000000;0.000000;;
 }
}