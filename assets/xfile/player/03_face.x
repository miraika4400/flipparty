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
 25;
 0.84872;0.55224;-0.86664;,
 0.49109;0.43167;-0.99932;,
 0.56926;0.78063;-1.32986;,
 1.04456;0.81907;-1.04907;,
 0.00000;0.36163;-1.07101;,
 0.00000;0.74218;-1.42437;,
 0.00000;1.24212;-1.56749;,
 0.63420;1.24212;-1.46417;,
 1.16315;1.24212;-1.15558;,
 -0.49109;0.43167;-0.99932;,
 -0.56926;0.78063;-1.32986;,
 -0.84872;0.55224;-0.86664;,
 -1.04456;0.81907;-1.04907;,
 -1.16315;1.24212;-1.15558;,
 -0.63420;1.24212;-1.46417;,
 -0.56926;1.81320;-1.32986;,
 0.00000;1.85165;-1.42437;,
 -1.04456;1.77476;-1.04907;,
 -0.84872;2.16336;-0.86664;,
 -0.49109;2.32655;-0.99932;,
 0.00000;2.39658;-1.07101;,
 0.56926;1.81320;-1.32986;,
 1.04456;1.77476;-1.04907;,
 0.49109;2.32655;-0.99932;,
 0.84872;2.16336;-0.86664;;
 
 16;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;2,5,6,7;,
 4;3,2,7,8;,
 4;4,9,10,5;,
 4;9,11,12,10;,
 4;10,12,13,14;,
 4;5,10,14,6;,
 4;6,14,15,16;,
 4;14,13,17,15;,
 4;15,17,18,19;,
 4;16,15,19,20;,
 4;8,7,21,22;,
 4;7,6,16,21;,
 4;21,16,20,23;,
 4;22,21,23,24;;
 
 MeshMaterialList {
  1;
  16;
  0,
  0,
  0,
  0,
  0,
  0,
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
  25;
  0.425568;-0.683087;-0.593536;,
  -0.425568;-0.683087;-0.593536;,
  0.475861;0.539313;-0.694765;,
  -0.475861;0.539313;-0.694765;,
  0.000000;-0.693860;-0.720110;,
  -0.514774;-0.030909;-0.856769;,
  0.000000;0.552140;-0.833752;,
  0.514774;-0.030909;-0.856769;,
  0.000000;-0.026002;-0.999662;,
  0.306326;-0.689003;-0.656841;,
  0.000000;-0.504517;-0.863402;,
  0.347775;-0.028740;-0.937137;,
  0.467781;-0.514321;-0.718787;,
  -0.306326;-0.689003;-0.656841;,
  -0.467781;-0.514321;-0.718787;,
  -0.347775;-0.028740;-0.937137;,
  -0.491785;0.405883;-0.770329;,
  -0.334395;0.547912;-0.766793;,
  0.000000;0.400389;-0.916345;,
  0.334395;0.547912;-0.766793;,
  0.491785;0.405883;-0.770329;,
  0.327324;-0.511952;-0.794206;,
  -0.327324;-0.511952;-0.794206;,
  -0.339770;0.405912;-0.848406;,
  0.339770;0.405912;-0.848406;;
  16;
  4;0,9,21,12;,
  4;9,4,10,21;,
  4;21,10,8,11;,
  4;12,21,11,7;,
  4;4,13,22,10;,
  4;13,1,14,22;,
  4;22,14,5,15;,
  4;10,22,15,8;,
  4;8,15,23,18;,
  4;15,5,16,23;,
  4;23,16,3,17;,
  4;18,23,17,6;,
  4;7,11,24,20;,
  4;11,8,18,24;,
  4;24,18,6,19;,
  4;20,24,19,2;;
 }
 MeshTextureCoords {
  25;
  0.000129;0.340694;,
  0.083152;0.340694;,
  0.083152;0.257671;,
  0.000129;0.257671;,
  0.166176;0.340694;,
  0.166176;0.257671;,
  0.166176;0.174647;,
  0.083152;0.174647;,
  0.000129;0.174647;,
  0.249199;0.340694;,
  0.249199;0.257671;,
  0.332223;0.340694;,
  0.332223;0.257671;,
  0.332223;0.174647;,
  0.249199;0.174647;,
  0.249199;0.091624;,
  0.166176;0.091624;,
  0.332223;0.091624;,
  0.332223;0.008600;,
  0.249199;0.008600;,
  0.166176;0.008600;,
  0.083152;0.091624;,
  0.000129;0.091624;,
  0.083152;0.008600;,
  0.000129;0.008600;;
 }
}
