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
 150;
 13.83410;-21.42150;11.74040;,
 17.34280;-21.42150;6.33180;,
 11.79390;-10.93110;10.21300;,
 14.66170;-10.93110;5.19210;,
 18.45880;-21.42150;0.02160;,
 15.69290;-10.93110;0.18390;,
 16.30430;-30.15360;5.86120;,
 17.42480;-26.58160;6.40730;,
 13.02820;-30.15360;10.86120;,
 13.90970;-26.58160;11.88150;,
 17.33560;-30.15360;0.02780;,
 18.53800;-26.58160;0.02060;,
 5.12400;-34.66030;6.92580;,
 5.16790;-35.24540;3.37820;,
 8.70900;-34.20510;6.21560;,
 9.79890;-34.66030;3.38410;,
 0.00000;-34.66030;7.51470;,
 0.00000;-35.24540;3.66090;,
 5.45350;-35.24540;0.06040;,
 10.39870;-34.66030;0.06030;,
 7.77220;-21.42150;15.29130;,
 7.81720;-26.58160;15.47560;,
 0.00000;-21.42150;16.60240;,
 0.00000;-26.58160;16.80250;,
 0.00000;-30.15360;15.35590;,
 7.32520;-30.15360;14.14380;,
 6.57210;-10.93110;12.50930;,
 0.00000;-10.93110;13.58010;,
 7.77220;-21.42150;-15.08460;,
 6.60160;-10.93110;-12.23290;,
 13.83410;-21.42150;-11.56090;,
 11.85650;-10.93110;-9.94030;,
 0.00000;-21.42150;-16.39560;,
 0.00000;-10.93110;-13.31060;,
 13.02820;-30.15360;-10.67960;,
 7.32520;-30.15360;-13.93710;,
 13.90970;-26.58160;-11.70240;,
 7.81720;-26.58160;-15.26880;,
 0.00000;-30.15360;-15.14910;,
 0.00000;-26.58160;-16.59580;,
 8.70900;-34.20510;-6.03440;,
 5.12400;-34.66030;-6.73340;,
 10.90720;-32.90480;-8.19150;,
 6.13530;-32.90480;-10.69740;,
 0.00000;-34.66030;-7.32350;,
 0.00000;-32.90480;-11.62970;,
 6.13530;-32.90480;10.90410;,
 10.90720;-32.90480;8.37890;,
 0.00000;-32.90480;11.83650;,
 13.63670;-32.90480;4.53260;,
 14.49090;-32.90480;0.04520;,
 10.39870;-34.66030;0.06030;,
 5.45350;-35.24540;0.06040;,
 9.79890;-34.66030;-3.23480;,
 5.16790;-35.24540;-3.22880;,
 0.00000;-35.24540;-3.51640;,
 14.49090;-32.90480;0.04520;,
 13.63670;-32.90480;-4.40340;,
 17.33560;-30.15360;0.02780;,
 16.30430;-30.15360;-5.75520;,
 18.45880;-21.42150;0.02160;,
 18.53800;-26.58160;0.02060;,
 17.34280;-21.42150;-6.23400;,
 17.42480;-26.58160;-6.31090;,
 15.69290;-10.93110;0.18390;,
 14.74340;-10.93110;-4.95800;,
 6.93010;-4.97060;10.02310;,
 11.22690;-3.91050;6.18890;,
 13.53150;-4.05870;0.02860;,
 13.53150;-4.05870;0.02860;,
 11.59840;-3.46160;-4.93350;,
 6.81950;-3.97000;-8.30920;,
 0.00000;-4.26210;-11.06360;,
 7.35080;-2.12420;-5.68820;,
 0.00000;-1.30650;-5.68820;,
 7.35080;-0.99200;0.02860;,
 0.00000;-0.08600;0.02860;,
 7.35080;-2.58210;5.79530;,
 7.35080;-0.99200;0.02860;,
 0.00000;-1.39300;5.79530;,
 0.00000;-0.08600;0.02860;,
 0.00000;-5.14550;10.73800;,
 13.08410;-3.65680;0.02860;,
 13.08410;-3.65680;0.02860;,
 0.00000;-35.24540;0.06040;,
 0.00000;-35.24540;0.06040;,
 -13.83410;-21.42150;11.74040;,
 -11.79390;-10.93110;10.21300;,
 -17.34280;-21.42150;6.33180;,
 -14.66170;-10.93110;5.19210;,
 -18.45880;-21.42150;0.02160;,
 -15.69290;-10.93110;0.18390;,
 -16.30430;-30.15360;5.86120;,
 -13.02820;-30.15360;10.86120;,
 -17.42480;-26.58160;6.40730;,
 -13.90970;-26.58160;11.88150;,
 -17.33560;-30.15360;0.02780;,
 -18.53800;-26.58160;0.02060;,
 -5.12400;-34.66030;6.92580;,
 -8.70900;-34.20510;6.21560;,
 -5.16790;-35.24540;3.37820;,
 -9.79890;-34.66030;3.38410;,
 -5.45350;-35.24540;0.06040;,
 -10.39870;-34.66030;0.06030;,
 -7.77220;-21.42150;15.29130;,
 -7.81720;-26.58160;15.47560;,
 -7.32520;-30.15360;14.14380;,
 -6.57210;-10.93110;12.50930;,
 -7.77220;-21.42150;-15.08460;,
 -13.83410;-21.42150;-11.56090;,
 -6.60160;-10.93110;-12.23290;,
 -11.85650;-10.93110;-9.94030;,
 -13.02820;-30.15360;-10.67960;,
 -13.90970;-26.58160;-11.70240;,
 -7.32520;-30.15360;-13.93710;,
 -7.81720;-26.58160;-15.26880;,
 -8.70900;-34.20510;-6.03440;,
 -10.90720;-32.90480;-8.19150;,
 -5.12400;-34.66030;-6.73340;,
 -6.13530;-32.90480;-10.69740;,
 -6.13530;-32.90480;10.90410;,
 -10.90720;-32.90480;8.37890;,
 -13.63670;-32.90480;4.53260;,
 -14.49090;-32.90480;0.04520;,
 -10.39870;-34.66030;0.06030;,
 -9.79890;-34.66030;-3.23480;,
 -5.45350;-35.24540;0.06040;,
 -5.16790;-35.24540;-3.22880;,
 -14.49090;-32.90480;0.04520;,
 -17.33560;-30.15360;0.02780;,
 -13.63670;-32.90480;-4.40340;,
 -16.30430;-30.15360;-5.75520;,
 -18.45880;-21.42150;0.02160;,
 -17.34280;-21.42150;-6.23400;,
 -18.53800;-26.58160;0.02060;,
 -17.42480;-26.58160;-6.31090;,
 -15.69290;-10.93110;0.18390;,
 -14.74340;-10.93110;-4.95800;,
 -6.93010;-4.97060;10.02310;,
 -11.22690;-5.05170;6.18890;,
 -13.53150;-4.05870;0.02860;,
 -13.53150;-4.05870;0.02860;,
 -11.59840;-3.46160;-4.93350;,
 -6.81950;-3.97000;-8.30920;,
 -7.35080;-2.12420;-5.68820;,
 -7.35080;-0.99200;0.02860;,
 -7.35080;-2.58210;5.79530;,
 -7.35080;-0.99200;0.02860;,
 -13.08410;-3.65680;0.02860;,
 -13.08410;-3.65680;0.02860;;
 
 252;
 3;0,1,2;,
 3;2,1,3;,
 3;1,4,3;,
 3;3,4,5;,
 3;6,7,8;,
 3;8,7,9;,
 3;10,11,6;,
 3;6,11,7;,
 3;7,11,1;,
 3;1,11,4;,
 3;9,7,0;,
 3;0,7,1;,
 3;12,13,14;,
 3;14,13,15;,
 3;16,17,12;,
 3;12,17,13;,
 3;13,18,15;,
 3;15,18,19;,
 3;0,20,9;,
 3;9,20,21;,
 3;20,22,21;,
 3;21,22,23;,
 3;23,24,21;,
 3;21,24,25;,
 3;21,25,9;,
 3;9,25,8;,
 3;26,27,20;,
 3;20,27,22;,
 3;2,26,0;,
 3;0,26,20;,
 3;28,29,30;,
 3;30,29,31;,
 3;32,33,28;,
 3;28,33,29;,
 3;34,35,36;,
 3;36,35,37;,
 3;35,38,37;,
 3;37,38,39;,
 3;39,32,37;,
 3;37,32,28;,
 3;37,28,36;,
 3;36,28,30;,
 3;40,41,42;,
 3;42,41,43;,
 3;41,44,43;,
 3;43,44,45;,
 3;43,45,35;,
 3;35,45,38;,
 3;42,43,34;,
 3;34,43,35;,
 3;25,46,8;,
 3;8,46,47;,
 3;24,48,25;,
 3;25,48,46;,
 3;48,16,46;,
 3;46,16,12;,
 3;46,12,47;,
 3;47,12,14;,
 3;15,49,14;,
 3;14,49,47;,
 3;19,50,15;,
 3;15,50,49;,
 3;50,10,49;,
 3;49,10,6;,
 3;49,6,47;,
 3;47,6,8;,
 3;51,52,53;,
 3;53,52,54;,
 3;54,55,41;,
 3;41,55,44;,
 3;53,54,40;,
 3;40,54,41;,
 3;56,57,58;,
 3;58,57,59;,
 3;51,53,56;,
 3;56,53,57;,
 3;53,40,57;,
 3;57,40,42;,
 3;57,42,59;,
 3;59,42,34;,
 3;60,61,62;,
 3;62,61,63;,
 3;58,59,61;,
 3;61,59,63;,
 3;59,34,63;,
 3;63,34,36;,
 3;62,63,30;,
 3;30,63,36;,
 3;64,60,65;,
 3;65,60,62;,
 3;65,62,31;,
 3;31,62,30;,
 3;2,66,26;,
 3;3,67,2;,
 3;5,68,3;,
 3;65,69,64;,
 3;31,70,65;,
 3;29,71,31;,
 3;33,72,29;,
 3;29,72,71;,
 3;71,72,73;,
 3;73,72,74;,
 3;73,74,75;,
 3;75,74,76;,
 3;77,78,79;,
 3;79,78,80;,
 3;77,79,66;,
 3;66,79,81;,
 3;66,81,26;,
 3;26,81,27;,
 3;70,71,73;,
 3;82,70,75;,
 3;75,70,73;,
 3;83,78,67;,
 3;67,78,77;,
 3;66,67,77;,
 3;65,70,69;,
 3;69,70,82;,
 3;3,68,67;,
 3;52,84,54;,
 3;54,84,55;,
 3;17,85,13;,
 3;13,85,18;,
 3;31,71,70;,
 3;2,67,66;,
 3;67,68,83;,
 3;86,87,88;,
 3;87,89,88;,
 3;88,89,90;,
 3;89,91,90;,
 3;92,93,94;,
 3;93,95,94;,
 3;96,92,97;,
 3;92,94,97;,
 3;94,88,97;,
 3;88,90,97;,
 3;95,86,94;,
 3;86,88,94;,
 3;98,99,100;,
 3;99,101,100;,
 3;16,98,17;,
 3;98,100,17;,
 3;100,101,102;,
 3;101,103,102;,
 3;86,95,104;,
 3;95,105,104;,
 3;104,105,22;,
 3;105,23,22;,
 3;23,105,24;,
 3;105,106,24;,
 3;105,95,106;,
 3;95,93,106;,
 3;107,104,27;,
 3;104,22,27;,
 3;87,86,107;,
 3;86,104,107;,
 3;108,109,110;,
 3;109,111,110;,
 3;32,108,33;,
 3;108,110,33;,
 3;112,113,114;,
 3;113,115,114;,
 3;114,115,38;,
 3;115,39,38;,
 3;39,115,32;,
 3;115,108,32;,
 3;115,113,108;,
 3;113,109,108;,
 3;116,117,118;,
 3;117,119,118;,
 3;118,119,44;,
 3;119,45,44;,
 3;119,114,45;,
 3;114,38,45;,
 3;117,112,119;,
 3;112,114,119;,
 3;106,93,120;,
 3;93,121,120;,
 3;24,106,48;,
 3;106,120,48;,
 3;48,120,16;,
 3;120,98,16;,
 3;120,121,98;,
 3;121,99,98;,
 3;101,99,122;,
 3;99,121,122;,
 3;103,101,123;,
 3;101,122,123;,
 3;123,122,96;,
 3;122,92,96;,
 3;122,121,92;,
 3;121,93,92;,
 3;124,125,126;,
 3;125,127,126;,
 3;127,118,55;,
 3;118,44,55;,
 3;125,116,127;,
 3;116,118,127;,
 3;128,129,130;,
 3;129,131,130;,
 3;124,128,125;,
 3;128,130,125;,
 3;125,130,116;,
 3;130,117,116;,
 3;130,131,117;,
 3;131,112,117;,
 3;132,133,134;,
 3;133,135,134;,
 3;129,134,131;,
 3;134,135,131;,
 3;131,135,112;,
 3;135,113,112;,
 3;133,109,135;,
 3;109,113,135;,
 3;136,137,132;,
 3;137,133,132;,
 3;137,111,133;,
 3;111,109,133;,
 3;87,107,138;,
 3;89,87,139;,
 3;91,89,140;,
 3;137,136,141;,
 3;111,137,142;,
 3;110,111,143;,
 3;33,110,72;,
 3;110,143,72;,
 3;143,144,72;,
 3;144,74,72;,
 3;144,145,74;,
 3;145,76,74;,
 3;146,79,147;,
 3;79,80,147;,
 3;146,138,79;,
 3;138,81,79;,
 3;138,107,81;,
 3;107,27,81;,
 3;142,144,143;,
 3;148,145,142;,
 3;145,144,142;,
 3;149,139,147;,
 3;139,146,147;,
 3;138,146,139;,
 3;137,141,142;,
 3;141,148,142;,
 3;89,139,140;,
 3;126,127,84;,
 3;127,55,84;,
 3;17,100,85;,
 3;100,102,85;,
 3;111,142,143;,
 3;87,138,139;,
 3;139,149,140;;
 
 MeshMaterialList {
  1;
  252;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "player000.png";
   }
  }
 }
 MeshNormals {
  128;
  0.223952;-0.942328;-0.248723;,
  0.224942;-0.942638;0.246648;,
  0.668232;0.139703;-0.730718;,
  0.672023;0.138122;0.727535;,
  0.000000;-0.950670;-0.310204;,
  -0.000000;-0.951116;0.308833;,
  -0.000000;0.118417;0.992964;,
  0.000000;0.120232;-0.992746;,
  0.563248;-0.581189;-0.587342;,
  -0.000000;-0.527148;-0.849773;,
  0.000000;-0.527149;0.849773;,
  0.566584;-0.580734;0.584577;,
  0.258373;-0.966045;-0.000182;,
  0.796958;-0.604035;-0.000559;,
  0.983889;0.178760;0.002836;,
  0.337921;0.157254;0.927944;,
  0.279727;-0.595492;0.753088;,
  0.336315;0.159762;-0.928099;,
  0.638828;0.350409;-0.684918;,
  0.278371;-0.595478;-0.753602;,
  0.620624;-0.167030;-0.766112;,
  0.101258;-0.958030;-0.268189;,
  0.000000;-0.838610;-0.544732;,
  0.356908;-0.849048;-0.389530;,
  0.000000;-0.838838;0.544380;,
  0.359157;-0.849017;0.387527;,
  0.502326;-0.864678;-0.000351;,
  0.000000;-0.994381;-0.105858;,
  0.250610;-0.961636;-0.111585;,
  0.775500;-0.553418;-0.303856;,
  0.923780;0.138934;-0.356830;,
  0.000000;0.293394;-0.955992;,
  0.000000;0.331507;0.943453;,
  -0.000000;-0.994514;0.104599;,
  0.925116;0.139708;0.353047;,
  0.960653;0.277577;0.009811;,
  0.654764;0.318216;0.685582;,
  -0.000000;-0.172365;-0.985033;,
  0.000000;-0.172363;0.985033;,
  0.777398;-0.552308;0.301013;,
  0.988020;-0.154326;-0.000726;,
  0.624109;-0.166879;0.763308;,
  0.101441;-0.958465;0.266560;,
  0.081074;-0.996708;-0.000046;,
  0.251128;-0.961616;0.110585;,
  0.903055;0.301135;0.306282;,
  0.892949;-0.158377;0.421377;,
  0.069197;-0.993492;0.090480;,
  0.280190;-0.170790;0.944629;,
  0.278175;0.322299;0.904844;,
  0.313071;0.336162;-0.888246;,
  0.279139;-0.170771;-0.944944;,
  0.169245;-0.857073;-0.486603;,
  0.169996;-0.857370;0.485817;,
  0.507739;-0.835897;0.208511;,
  0.069207;-0.993395;-0.091527;,
  0.506102;-0.836444;-0.210290;,
  0.890699;-0.158822;-0.425946;,
  0.905736;0.300633;-0.298767;,
  0.000000;0.555209;0.831711;,
  0.000000;0.914205;0.405253;,
  -0.000000;0.999980;0.006277;,
  0.000000;0.954552;-0.298045;,
  -0.000000;0.649830;-0.760080;,
  0.341805;0.597568;-0.725315;,
  0.220120;0.881465;-0.417811;,
  0.251337;0.967469;0.028888;,
  0.206864;0.900948;0.381444;,
  0.248569;0.644978;0.722646;,
  0.600853;0.697722;-0.390075;,
  0.549905;0.834564;0.033269;,
  0.586769;0.700286;0.406573;,
  0.869593;0.493488;0.016674;,
  0.000000;-1.000000;-0.000000;,
  -0.223952;-0.942328;-0.248723;,
  -0.224942;-0.942638;0.246648;,
  -0.668232;0.139703;-0.730718;,
  -0.672023;0.138122;0.727535;,
  -0.563248;-0.581189;-0.587342;,
  -0.566584;-0.580734;0.584577;,
  -0.258373;-0.966045;-0.000182;,
  -0.796958;-0.604035;-0.000559;,
  -0.983889;0.178760;0.002836;,
  -0.337921;0.157254;0.927944;,
  -0.279727;-0.595492;0.753088;,
  -0.336315;0.159762;-0.928099;,
  -0.638828;0.350409;-0.684918;,
  -0.278371;-0.595478;-0.753602;,
  -0.620624;-0.167030;-0.766112;,
  -0.101258;-0.958030;-0.268189;,
  -0.356908;-0.849048;-0.389530;,
  -0.359157;-0.849017;0.387527;,
  -0.502326;-0.864678;-0.000351;,
  -0.250610;-0.961636;-0.111585;,
  -0.775500;-0.553418;-0.303856;,
  -0.923780;0.138934;-0.356830;,
  -0.925116;0.139708;0.353047;,
  -0.960653;0.277577;0.009811;,
  -0.661260;0.335361;0.671021;,
  -0.777398;-0.552308;0.301013;,
  -0.988020;-0.154326;-0.000726;,
  -0.624109;-0.166879;0.763308;,
  -0.101441;-0.958465;0.266560;,
  -0.081074;-0.996708;-0.000046;,
  -0.251128;-0.961616;0.110585;,
  -0.894288;0.317582;0.315262;,
  -0.892949;-0.158377;0.421377;,
  -0.069197;-0.993492;0.090480;,
  -0.280190;-0.170790;0.944629;,
  -0.278175;0.322299;0.904844;,
  -0.313071;0.336162;-0.888246;,
  -0.279139;-0.170771;-0.944944;,
  -0.169245;-0.857073;-0.486603;,
  -0.169996;-0.857370;0.485817;,
  -0.507739;-0.835897;0.208511;,
  -0.069207;-0.993395;-0.091527;,
  -0.506102;-0.836444;-0.210290;,
  -0.890699;-0.158822;-0.425946;,
  -0.905736;0.300633;-0.298767;,
  -0.341805;0.597568;-0.725315;,
  -0.220120;0.881465;-0.417811;,
  -0.279365;0.959095;0.045743;,
  -0.316705;0.871308;0.374860;,
  -0.294793;0.641685;0.708052;,
  -0.600853;0.697722;-0.390075;,
  -0.547207;0.830389;0.104969;,
  -0.620218;0.661386;0.421781;,
  -0.864855;0.499619;0.049060;;
  252;
  3;3,34,36;,
  3;36,34,45;,
  3;34,14,45;,
  3;45,14,35;,
  3;39,46,11;,
  3;11,46,41;,
  3;13,40,39;,
  3;39,40,46;,
  3;46,40,34;,
  3;34,40,14;,
  3;41,46,3;,
  3;3,46,34;,
  3;42,47,1;,
  3;1,47,44;,
  3;5,33,42;,
  3;42,33,47;,
  3;47,43,44;,
  3;44,43,12;,
  3;3,15,41;,
  3;41,15,48;,
  3;15,6,48;,
  3;48,6,38;,
  3;38,10,48;,
  3;48,10,16;,
  3;48,16,41;,
  3;41,16,11;,
  3;49,32,15;,
  3;15,32,6;,
  3;36,49,3;,
  3;3,49,15;,
  3;17,50,2;,
  3;2,50,18;,
  3;7,31,17;,
  3;17,31,50;,
  3;8,19,20;,
  3;20,19,51;,
  3;19,9,51;,
  3;51,9,37;,
  3;37,7,51;,
  3;51,7,17;,
  3;51,17,20;,
  3;20,17,2;,
  3;0,21,23;,
  3;23,21,52;,
  3;21,4,52;,
  3;52,4,22;,
  3;52,22,19;,
  3;19,22,9;,
  3;23,52,8;,
  3;8,52,19;,
  3;16,53,11;,
  3;11,53,25;,
  3;10,24,16;,
  3;16,24,53;,
  3;24,5,53;,
  3;53,5,42;,
  3;53,42,25;,
  3;25,42,1;,
  3;44,54,1;,
  3;1,54,25;,
  3;12,26,44;,
  3;44,26,54;,
  3;26,13,54;,
  3;54,13,39;,
  3;54,39,25;,
  3;25,39,11;,
  3;12,43,28;,
  3;28,43,55;,
  3;55,27,21;,
  3;21,27,4;,
  3;28,55,0;,
  3;0,55,21;,
  3;26,56,13;,
  3;13,56,29;,
  3;12,28,26;,
  3;26,28,56;,
  3;28,0,56;,
  3;56,0,23;,
  3;56,23,29;,
  3;29,23,8;,
  3;14,40,30;,
  3;30,40,57;,
  3;13,29,40;,
  3;40,29,57;,
  3;29,8,57;,
  3;57,8,20;,
  3;30,57,2;,
  3;2,57,20;,
  3;35,14,58;,
  3;58,14,30;,
  3;58,30,18;,
  3;18,30,2;,
  3;36,68,49;,
  3;45,71,36;,
  3;35,72,45;,
  3;58,72,35;,
  3;18,69,58;,
  3;50,64,18;,
  3;31,63,50;,
  3;50,63,64;,
  3;64,63,65;,
  3;65,63,62;,
  3;65,62,66;,
  3;66,62,61;,
  3;67,66,60;,
  3;60,66,61;,
  3;67,60,68;,
  3;68,60,59;,
  3;68,59,49;,
  3;49,59,32;,
  3;69,64,65;,
  3;70,69,66;,
  3;66,69,65;,
  3;70,66,71;,
  3;71,66,67;,
  3;68,71,67;,
  3;58,69,72;,
  3;72,69,70;,
  3;45,72,71;,
  3;43,73,55;,
  3;55,73,27;,
  3;33,73,47;,
  3;47,73,43;,
  3;18,64,69;,
  3;36,71,68;,
  3;71,72,70;,
  3;77,98,96;,
  3;98,105,96;,
  3;96,105,82;,
  3;105,97,82;,
  3;99,79,106;,
  3;79,101,106;,
  3;81,99,100;,
  3;99,106,100;,
  3;106,96,100;,
  3;96,82,100;,
  3;101,77,106;,
  3;77,96,106;,
  3;102,75,107;,
  3;75,104,107;,
  3;5,102,33;,
  3;102,107,33;,
  3;107,104,103;,
  3;104,80,103;,
  3;77,101,83;,
  3;101,108,83;,
  3;83,108,6;,
  3;108,38,6;,
  3;38,108,10;,
  3;108,84,10;,
  3;108,101,84;,
  3;101,79,84;,
  3;109,83,32;,
  3;83,6,32;,
  3;98,77,109;,
  3;77,83,109;,
  3;85,76,110;,
  3;76,86,110;,
  3;7,85,31;,
  3;85,110,31;,
  3;78,88,87;,
  3;88,111,87;,
  3;87,111,9;,
  3;111,37,9;,
  3;37,111,7;,
  3;111,85,7;,
  3;111,88,85;,
  3;88,76,85;,
  3;74,90,89;,
  3;90,112,89;,
  3;89,112,4;,
  3;112,22,4;,
  3;112,87,22;,
  3;87,9,22;,
  3;90,78,112;,
  3;78,87,112;,
  3;84,79,113;,
  3;79,91,113;,
  3;10,84,24;,
  3;84,113,24;,
  3;24,113,5;,
  3;113,102,5;,
  3;113,91,102;,
  3;91,75,102;,
  3;104,75,114;,
  3;75,91,114;,
  3;80,104,92;,
  3;104,114,92;,
  3;92,114,81;,
  3;114,99,81;,
  3;114,91,99;,
  3;91,79,99;,
  3;80,93,103;,
  3;93,115,103;,
  3;115,89,27;,
  3;89,4,27;,
  3;93,74,115;,
  3;74,89,115;,
  3;92,81,116;,
  3;81,94,116;,
  3;80,92,93;,
  3;92,116,93;,
  3;93,116,74;,
  3;116,90,74;,
  3;116,94,90;,
  3;94,78,90;,
  3;82,95,100;,
  3;95,117,100;,
  3;81,100,94;,
  3;100,117,94;,
  3;94,117,78;,
  3;117,88,78;,
  3;95,76,117;,
  3;76,88,117;,
  3;97,118,82;,
  3;118,95,82;,
  3;118,86,95;,
  3;86,76,95;,
  3;98,109,123;,
  3;105,98,126;,
  3;97,105,127;,
  3;118,97,127;,
  3;86,118,124;,
  3;110,86,119;,
  3;31,110,63;,
  3;110,119,63;,
  3;119,120,63;,
  3;120,62,63;,
  3;120,121,62;,
  3;121,61,62;,
  3;122,60,121;,
  3;60,61,121;,
  3;122,123,60;,
  3;123,59,60;,
  3;123,109,59;,
  3;109,32,59;,
  3;124,120,119;,
  3;125,121,124;,
  3;121,120,124;,
  3;125,126,121;,
  3;126,122,121;,
  3;123,122,126;,
  3;118,127,124;,
  3;127,125,124;,
  3;105,126,127;,
  3;103,115,73;,
  3;115,27,73;,
  3;33,107,73;,
  3;107,103,73;,
  3;86,124,119;,
  3;98,123,126;,
  3;126,125,127;;
 }
 MeshTextureCoords {
  150;
  0.942060;0.185530;,
  0.954690;0.183590;,
  0.936700;0.163600;,
  0.946550;0.159190;,
  0.968760;0.179720;,
  0.956500;0.153560;,
  0.956030;0.203860;,
  0.955990;0.194840;,
  0.942000;0.201850;,
  0.942380;0.194810;,
  0.973340;0.206070;,
  0.972800;0.193680;,
  0.927860;0.220330;,
  0.931060;0.232590;,
  0.935650;0.216800;,
  0.950960;0.230470;,
  0.917490;0.219940;,
  0.917490;0.231090;,
  0.934480;0.245910;,
  0.959020;0.238490;,
  0.929770;0.186600;,
  0.929810;0.195040;,
  0.917490;0.187060;,
  0.917490;0.195150;,
  0.917490;0.201410;,
  0.929530;0.201550;,
  0.927320;0.165450;,
  0.917490;0.166550;,
  0.716390;0.706230;,
  0.721610;0.598530;,
  0.654150;0.704430;,
  0.672290;0.591710;,
  0.795270;0.705300;,
  0.795270;0.600340;,
  0.656610;0.781050;,
  0.721310;0.781680;,
  0.654730;0.749190;,
  0.718360;0.748710;,
  0.795270;0.778930;,
  0.795270;0.746700;,
  0.695830;0.900530;,
  0.739330;0.891650;,
  0.659740;0.814210;,
  0.727790;0.825620;,
  0.795270;0.875990;,
  0.795270;0.821220;,
  0.928660;0.209900;,
  0.940390;0.210340;,
  0.917490;0.209540;,
  0.955000;0.215070;,
  0.969910;0.220840;,
  0.616800;0.964730;,
  0.720970;0.998340;,
  0.658540;0.920690;,
  0.733150;0.941410;,
  0.795270;0.928210;,
  0.546150;0.892790;,
  0.610780;0.852230;,
  0.515970;0.823630;,
  0.596280;0.799620;,
  0.520200;0.688900;,
  0.509060;0.761700;,
  0.591680;0.700540;,
  0.590990;0.756320;,
  0.566280;0.549520;,
  0.620730;0.573680;,
  0.927880;0.158920;,
  0.938880;0.153400;,
  0.949800;0.145770;,
  0.598240;0.508430;,
  0.650880;0.535800;,
  0.717510;0.569980;,
  0.795270;0.557450;,
  0.704360;0.520520;,
  0.795270;0.510770;,
  0.689680;0.460180;,
  0.795270;0.448840;,
  0.929510;0.149940;,
  0.931690;0.137930;,
  0.917490;0.149100;,
  0.917490;0.136930;,
  0.917490;0.158770;,
  0.621750;0.488540;,
  0.945460;0.142550;,
  0.795270;0.985940;,
  0.917490;0.243540;,
  0.942060;0.185530;,
  0.936700;0.163600;,
  0.954690;0.183590;,
  0.946550;0.159190;,
  0.968760;0.179720;,
  0.956500;0.153560;,
  0.956030;0.203860;,
  0.942000;0.201850;,
  0.955990;0.194840;,
  0.942380;0.194810;,
  0.973340;0.206070;,
  0.972800;0.193680;,
  0.927860;0.220330;,
  0.935650;0.216800;,
  0.931060;0.232590;,
  0.950960;0.230470;,
  0.934480;0.245910;,
  0.959020;0.238490;,
  0.929770;0.186600;,
  0.929810;0.195040;,
  0.929530;0.201550;,
  0.927320;0.165450;,
  0.716390;0.706230;,
  0.654150;0.704430;,
  0.721610;0.598530;,
  0.672290;0.591710;,
  0.656610;0.781050;,
  0.654730;0.749190;,
  0.721310;0.781680;,
  0.718360;0.748710;,
  0.695830;0.900530;,
  0.659740;0.814210;,
  0.739330;0.891650;,
  0.727790;0.825620;,
  0.928660;0.209900;,
  0.940390;0.210340;,
  0.955000;0.215070;,
  0.969910;0.220840;,
  0.616800;0.964730;,
  0.658540;0.920690;,
  0.720970;0.998340;,
  0.733150;0.941410;,
  0.546150;0.892790;,
  0.515970;0.823630;,
  0.610780;0.852230;,
  0.596280;0.799620;,
  0.520200;0.688900;,
  0.591680;0.700540;,
  0.509060;0.761700;,
  0.590990;0.756320;,
  0.566280;0.549520;,
  0.620730;0.573680;,
  0.927880;0.158920;,
  0.938880;0.153400;,
  0.949800;0.145770;,
  0.598240;0.508430;,
  0.650880;0.535800;,
  0.717510;0.569980;,
  0.704360;0.520520;,
  0.689680;0.460180;,
  0.929510;0.149940;,
  0.931690;0.137930;,
  0.621750;0.488540;,
  0.945460;0.142550;;
 }
}