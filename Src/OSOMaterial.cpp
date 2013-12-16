#include "OSOMaterial.h"

namespace OSO
{
    static FbxDouble3 GetMaterialProperty(const FbxSurfaceMaterial * pMaterial, const char * pPropertyName,const char * pFactorPropertyName )
    {
        FbxDouble3 lResult(0, 0, 0);
        const FbxProperty lProperty = pMaterial->FindProperty(pPropertyName);
        const FbxProperty lFactorProperty = pMaterial->FindProperty(pFactorPropertyName);
        if (lProperty.IsValid() && lFactorProperty.IsValid())
        {
            lResult = lProperty.Get<FbxDouble3>();
            double lFactor = lFactorProperty.Get<FbxDouble>();
            if (lFactor != 1)
            {
                lResult[0] *= lFactor;
                lResult[1] *= lFactor;
                lResult[2] *= lFactor;
            }
        }

        return lResult;
    }


    void Material::Initialize(const FbxSurfaceMaterial * pMaterial)
    {
        const FbxDouble3 lEmissive = GetMaterialProperty(pMaterial, FbxSurfaceMaterial::sEmissive, FbxSurfaceMaterial::sEmissiveFactor);
        emissive.r = static_cast<float>(lEmissive[0]);
        emissive.g = static_cast<float>(lEmissive[1]);
        emissive.b = static_cast<float>(lEmissive[2]);
        emissive.a = 1.0f;

        const FbxDouble3 lAmbient = GetMaterialProperty(pMaterial, FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor);
        ambient.r = static_cast<float>(lAmbient[0]);
        ambient.g = static_cast<float>(lAmbient[1]);
        ambient.b = static_cast<float>(lAmbient[2]);
        ambient.a = 1.0f;

        const FbxDouble3 lDiffuse = GetMaterialProperty(pMaterial, FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor);
        diffuse.r = static_cast<float>(lDiffuse[0]);
        diffuse.g = static_cast<float>(lDiffuse[1]);
        diffuse.b = static_cast<float>(lDiffuse[2]);
        diffuse.a = 1.0f;

        const FbxDouble3 lSpecular = GetMaterialProperty(pMaterial, FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor);
        specular.r = static_cast<float>(lSpecular[0]);
        specular.g = static_cast<float>(lSpecular[1]);
        specular.b = static_cast<float>(lSpecular[2]);
        specular.a = 1.0f;

        FbxProperty lShininessProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sShininess);
        if (lShininessProperty.IsValid())
        {
            double lShininess = lShininessProperty.Get<FbxDouble>();
            shiness = static_cast<float>(lShininess);
        }
    }
}