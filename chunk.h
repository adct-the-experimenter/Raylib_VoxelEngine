#ifndef G_CHUNK_H
#define G_CHUNK_H

#include "blockfacehelper.h"
#include "raylib.h"
#include "chunkmesh.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_SIZE (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)


typedef struct Chunk{
    ChunkMesh *mesh;
    int loaded;
    Vector3 position;
    int data[CHUNK_SIZE]; //16x16x16
} Chunk;


//Initialize a chunk.
void Chunk_Init(Chunk *chunk, Vector3 pos);
//Allocate memory for a mesh.
void Chunk_AllocateMeshData(ChunkMesh *mesh, int triangleCount);
//Reallocate memory for a mesh.
void Chunk_ReAllocateMeshData(ChunkMesh *mesh, int triangleCount);
//Unload a chunk.
void Chunk_Unload(Chunk *chunk);

//Build/Refresh a chunk's mesh.
void Chunk_BuildMesh(Chunk *chunk);
void Chunk_AddCube(Chunk *chunk, ChunkMesh *mesh, Vector3 pos, Vector3 worldPos, int blockID);
void Chunk_AddFace(Chunk *chunk, ChunkMesh *mesh, Vector3 pos, Vector3 worldPos, BlockFace face, int blockID);

void Chunk_GetBorderingChunks(Chunk *chunk, Vector3 pos, Chunk *(*dest)[3]);

//Set a block in a chunk and refresh mesh.
void Chunk_SetBlock(Chunk *chunk, Vector3 pos, int blockID);

//Get a block ID in a chunk.
int Chunk_GetBlock(Chunk *chunk, Vector3 pos);

//Check if block position is valid in chunk.
int Chunk_IsValidPos(Vector3 pos);

//Convert block position to index.
int Chunk_PosToIndex(Vector3 pos);

//convert index to block position.
Vector3 Chunk_IndexToPos(int index);

#endif