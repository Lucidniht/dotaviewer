#pragma once

#include <fbxsdk.h>
#include "OSOTypes.h"

namespace OSO
{
    struct ColorElement
    {
        float r, g, b, a;
    };

    class Material
    {
    public:
        void Initialize(const FbxSurfaceMaterial * pMaterial);

    public:
        ColorElement ambient;
        ColorElement diffuse;
        ColorElement specular;
        ColorElement emissive;
        
        float shiness;
    };

}