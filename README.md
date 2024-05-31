# SoftwareRasterizer

A program that emulates the 3d processing rendering from scratch in the CPU with C++ maded for fun

It uses assimp to import some 3d objects files with materials

Here's a preview

![245426484-8a22a62c-6332-48ac-ba7d-be76ea5db629](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/bf4f6ff5-3029-439f-a41e-f891bf68d838)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/a28a3295-090c-48ad-a84e-c46ec5c8c234)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/f3af5c15-140e-4ca4-8b3f-8ddff05bd48e)

![4](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/cd625875-4e9a-4dce-87b7-2bf3ec6491ea)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/49207de6-e8d5-4155-84e2-95e3d37d5e2a)

# What is implemented ?

- Perspective projection (world, camera and screen space ...)
- Naive triangle "clipping"
- Camera implementation with translation (with front, right and up vectors) and rotation (based on pitch and yaw)
- Basic triangle scan line using triangle bounding box
- Triangle interpolation for vertex attributes with z correction
- Per pixel light, uv mapping with textures, wireframe, depth testing and more
- Everything is writed in an array of pixels (Pixel buffer) and sended to GPU to draw as a simple texture
- GPU is not used at all (only to show the result)
- Face culling based on camera front vector (recent)

# Menu options

- Change framebuffer resolution
- Draw mode (wireframe, light, normals, positions, uvs, patterns, depth)
- Camera movement and rotation speed
- Fov, Aspect Ratio
- Pattern scalar
- ZFar and ZNear planes

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/08e85a14-454d-4bc3-a368-284ccf76c60f)

# Funny Results

- Here is some print of the results with the best angle

### Sponza

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/5c68e27f-e5c2-498a-a22a-4fae21904cee)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/12651576-52e0-4b0f-b350-6789de0dd92e)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/3dff7220-b8ff-472e-b943-06df2e7d8dca)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/c1980673-85c2-4098-9140-6134deef5ff0)

### Fortress

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/ccfb1f60-9832-45e3-a50d-9b9e75fa3480)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/650f7733-2f99-46e1-9a55-162dbc9ee8a0)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/671c9b31-4476-45b1-87d1-4e741845317c)

### Vilinha (made by AlpacaDS)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/eb91aef7-4a7e-4592-9c58-0d3eb32495c7)

### Default Scene

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/64c5f42e-cc18-49bf-aa4a-7c7bb6e584b9)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/f4f4606f-325b-435a-8743-c22f9d3d0cd2)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/c487afb0-3b07-4797-aa6c-b8716f30446f)

![image](https://github.com/RodrigoPAml/SoftwareRasterizer/assets/41243039/0fce884a-18d9-420a-a378-3a5051ec5155)
