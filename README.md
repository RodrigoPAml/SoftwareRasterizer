# SotfwareRasterizer

A program that emulates the 3d processing rendering from scratch in the CPU with C++

Using assimp to import some 3d object file

# How

- Computing perspective projection
- Apply camera transformations
- Transform to screen space
- Apply a triangle scanline
- Apply a per pixel interpolation with barycentric coordinates (z corrected)
- Write everything in an array of pixels and send to GPU to draw as a simple texture
- GPU is not used at all (only to show the result)

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/08e85a14-454d-4bc3-a368-284ccf76c60f)

# Some Results

### Bunny 1920x1080

![Sem título](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/be00e964-f436-4f57-a6f4-e5f2542d4f2f)

### Suzzy Scene 1920x1080 

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/54946c67-67d4-4928-8043-4f5e389bacb5)

### Wire framed Dragon

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/0ba5edec-4484-493c-a597-3e1b902f9477)

## Todo

- Advanced clipping
- Perfect pixel triangles
- Textures
