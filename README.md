# SotfwareRasterizer

A program that emulates the 3d processing rendering from scratch in the CPU with C++ maded for fun

It uses assimp to import some 3d objects files with random colors

Here's a preview

![Sem título](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/8a22a62c-6332-48ac-ba7d-be76ea5db629)


# What is implemented ?

- Perspective projection (world, camera and screen space ...)
- Naive triangle "clipping"
- Camera implementation with translation (with front, right and up vectors) and rotation (based on pitch and yaw)
- Basic triangle scan line using triangle bounding box
- Triangle interpolation for vertex attributes with z correction
- Per pixel light, uv mapping, wireframe, depth testing and more
- Everything is writed in an array of pixels (Pixel buffer) and sended to GPU to draw as a simple texture
- GPU is not used at all (only to show the result)
- Face culling (recent)

# Menu options

- CHange framebuffer resolution
- Draw mode (wireframe, light, normals, positions, uvs, patterns, depth)
- Camera movement and rotation speed
- Fov, Aspect Ratio
- Pattern scalar
- ZFar and ZNear planes
- Use Face culling

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/08e85a14-454d-4bc3-a368-284ccf76c60f)

# Funny Results

- Here is some print of the results with the best angle

### Bunny 1920x1080

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/0ba32859-3119-4d8d-b651-56ac571d973b)

### Scene

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/5a81c101-a7dc-4d6d-85ab-5256295b15bb)

### TeaPot

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/2efe4320-dbb4-4765-b860-08e2f69c6895)

### Scene 2

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/bd2f4cd0-7e1a-4546-84d8-34ffc5137386)

### Normals

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/f82c72cf-513f-4dd6-97c4-fa0d467da364)

### Depth

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/d8ca9dc2-41ab-4283-a25c-22dfa94251af)

### Low Resolution 400x400

![image](https://github.com/RodrigoPAml/SotfwareRasterizer/assets/41243039/c554af21-ee0d-4cd5-b259-580999713028)

