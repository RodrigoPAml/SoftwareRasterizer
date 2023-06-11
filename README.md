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

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/2a24ff91-87ae-48b7-942a-c63636ecb08d)

# Some Results

### Bunny 1920x1080

![Sem título](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/9fe84d9f-f5e2-46fd-838d-b9601603e047)

### Suzzy Scene 1920x1080 

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/b512cee9-934e-402d-8bb2-d8afe7904b8f)

### Wire framed Dragon

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/9d6e528e-4d4f-41c7-bbf4-b60af068e741)

## Todo

- Advanced clipping
- Perfect pixel triangles
- Textures
